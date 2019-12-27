
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>			// so we can use tolower()

#include "makegen.h"

uchar unacceptable_parenchars[256];
uchar alphanumericals[256];

void fdh_init(void)
{
int i;

	memset(unacceptable_parenchars, 0, sizeof(unacceptable_parenchars));
	unacceptable_parenchars[';'] = 1;
	unacceptable_parenchars['='] = 1;
	unacceptable_parenchars['+'] = 1;
	unacceptable_parenchars['-'] = 1;
	unacceptable_parenchars['/'] = 1;
	unacceptable_parenchars['!'] = 1;

	memset(alphanumericals, 0, sizeof(alphanumericals));
	for(i='A';i<='Z';i++) alphanumericals[i] = 1;
	for(i='a';i<='z';i++) alphanumericals[i] = 1;
	for(i='0';i<='9';i++) alphanumericals[i] = 1;
	alphanumericals['_'] = 1;
}


char is_function_definition(uchar *line, uint linelen)
// return true if "line" is a function definition (like int main(void))
{
uchar foundspace, closeparens;
uchar *args, *ptr;

	// function defines usually have these things in common that
	// distinguishes them from code:

	// * they are (almost, we'll pretend always) never indented
	// (at this point trim comments, ltrim, crop just before { if present,
	//  and then rtrim)
	// * they do not end in a semicolon, but they do end with )
	// * they are not a blank line
	// * they do not start with # or }
	// * they contain at least one space, followed by exactly one '(',
	//   followed by one ')'.
	// * either they contain at least one space between '(' and the ')',
	//	 or the function is void.
	// * in between '(' and ')' there is no:
	//   ';', '=', '+', '-', '/', '!' (this helps cull for loops),
	//	 and finally, no function can be named:
	//	if, for, while, switch, or sizeof.

	// cull preprocessor directives and some other crap that's easy and fast
	if (linelen > 0 && line[linelen-1] == ';') return 0;		// since most C code ends in ';'
	if (line[0]=='#') return 0;
	if (line[0]=='}') return 0;
	// this is a pretty common keyword so cull it out now
	if (line[0]=='i' && line[1]=='f' && line[2]==' ') return 0;
	// for some compatibility with C++ code
	if (strchr(line, ':')) return 0;

	// knock off the '{' if it's got one on the same line
	if ((ptr = strchr(line, '{')))
	{
		*ptr = 0;
		--ptr;
		while(ptr >= line)
		{
			if (*ptr==' ' || *ptr==9)
			{
				*ptr = 0;
				ptr--;
			}
			else break;
		}

		linelen = strlen(line);
	}

	// cull anything ending with a semicolon and not ending with ')'
	if (linelen > 0 && line[linelen-1] != ')') return 0;

	// nearly everything that gets through here is a function define.
	// let's do a few more in-depth tests to make sure.

	// make sure there is at least one space before the open paren
	args = strchr(line, '(');
	if (!args)
	{	// no open paren
		//printf("no open paren, cull\n");
		return 0;
	}

	// make sure the parameter list is valid
	// (unless it's doesn't take any; like foo(void))
	if (args[1] != 'v' || \
		args[2] != 'o' || \
		args[3] != 'i' || \
		args[4] != 'd' || \
		args[5] != ')' || \
		args[6] != 0)
	{
		if (args[1] != ')')
		{
			//  must contain at least one space, but no
			//  ';', '=', '+', '-', '/', '!'
			foundspace = closeparens = 0;
			while(*(++args))
			{
				if (unacceptable_parenchars[*args])
				{
					//printf("unacceptable parenchar: %c\n", line[i]);
					return 0;
				}
				else if (*args==' ') foundspace = 1;
				else if (*args==')') closeparens = 1;
			}

			return (foundspace && closeparens);
		}
	}

	return 1;
}


#define ROL(I)	( (I << 1) | (I >> 31) )		// rolls bits to left

int updatehash(uint curhash, uchar *line)
// update curhash with information in line and return the new hash.
// function hashes are a hash of all the function definitions in a file
// and are used to quickly determine if any of the definitions have changed
// so we can regenerate the .fdh file.
{
int i;
	for(i=0;line[i];i++)
	{
		curhash ^= line[i];
		curhash = ROL(curhash);
	}
	curhash ^= 0xAA5555AA;
	return curhash;
}

void writehashline(uint hash, FILE *fp)
{
	fprintf(fp, "//hash:%08x\n", (unsigned int)hash);
}

char doesfdhneedupdate(uchar *fdhfile, unsigned long hash)
// This is so we don't update the fdh files every single time and
// cause 'make' to constantly recompile things that haven't really changed.
// Checks that fdhfile exists and that all of it's entries match the
// function list of source file index; if that is true returns 0,
// otherwise it returns nonzero.
// If the file does not exist returns 2.
{
FILE *fp;
uchar hashline[MAXLEN];
unsigned long oldhash;

	// open up the file and grab the hash off the first line
	fp = fopen(fdhfile, "rb");
	if (!fp)
	{
		printf(": Creating %s\n", fdhfile);
		return 2;
	}

	fgetline(fp, hashline, MAXLEN);
	fclose(fp);

	// "//hash=abcd1234"
	if (strlen(hashline) != 15) return 1;
	oldhash = strtoll(&hashline[7], NULL, 16);

	if (oldhash != hash)
	{
		//printf("file %s needs update: old %08x new %08x\n", fdhfile, oldhash, hash);
		if (!options.silent) printf(": Updating %s\n", fdhfile);
		return 1;
	}
	return 0;
}

#ifndef CDHMAKER

char getfuncname(uchar *line, uint linelen, uchar *funcname)
// extracts the name of a function from it's definition
{
int i;
int lastspacepos, parenpos, bytestocopy;
char foundalphanumeric;
uchar *ptr;

	// find index of first (
	ptr = strchr(line, '(');
	if (!ptr)
	{
		printf("getfuncname: no open paren:\n%s\n", line);
		return 1;
	}
	parenpos = (ptr - line);

	// now go backwards from the paren, finding the first space
	// after the first alphanumeric character
	foundalphanumeric = 0;
	lastspacepos = 0;
	for(i=parenpos;i>=0;i--)
	{
		if (!foundalphanumeric)
		{
			if (alphanumericals[line[i]]) foundalphanumeric = 1;
		}
		else
		{
			if (line[i]==' ') { lastspacepos = i+1; break; }
		}
	}

	bytestocopy = (parenpos - lastspacepos);

	memcpy(funcname, &line[lastspacepos], bytestocopy);
	funcname[bytestocopy] = 0;

	bytestocopy = RTrim(funcname, bytestocopy);
	LTrimAt(funcname, '*', bytestocopy);

	return 0;
}

char is_reserved_keyword(char *str)
{
	if (str[0] == 'i' && str[1] == 'f' && str[2] == 0) return 1;
	if (!strcmp(str, "for")) return 1;
	if (!strcmp(str, "while")) return 1;
	if (!strcmp(str, "case")) return 1;
	if (!strcmp(str, "switch")) return 1;
	if (!strcmp(str, "do")) return 1;
	if (!strcmp(str, "sizeof")) return 1;
	if (!strcmp(str, "catch")) return 1;
	if (!strcmp(str, "new")) return 1;
	if (!strcmp(str, "delete")) return 1;
	// don't include function "main" in fdh's
	if (!strcmp(str, "main")) return 1;

	// functions never start with a number so rule those out
	// done backwards like this so the first comp rules out ASCII letters.
	// it's a MINISCULE optimization.
	return (str[0] <= '9' && str[0] >= '0');
}

void FuncStripAtParen(uchar *line)
// strip a line at the last )
{
char *ptr = strrchr(line, ')');
	if (ptr) { ptr++; *ptr = 0; }
}

char AddReferencedFunction(uint index, uchar *funcname)
// adds a record that source file no 'index' calls function 'funcname'
{
stFuncReference *fr;

	if (!(fr = malloc(sizeof(stFuncReference)))) goto OOM;
	if (!(fr->funcname = strdup(funcname))) goto OOM;

	if (sources[index].lastfunc)
		sources[index].lastfunc->next = fr;
	else
		sources[index].firstfunc = fr;

	fr->prev = sources[index].lastfunc;
	fr->next = NULL;
	sources[index].lastfunc = fr;
	return 0;

OOM: ;
	printf("AddReferencedFunction: out of memory on func '%s'\n", funcname);
	return 1;
}


char detectfunctioncalls(uchar *line, uint linelen, uint index)
// detects all possible function calls on line line and squirrels them
// away for later inspection.
{
uchar func[MAXLEN];
int i, j;
int topindex;

	//printf("detectfunctioncalls: '%s'\n", line);

	// starting at the beginning of the line, save each contiguous string
	// of alphanumeric characters which are terminated with a (.
	j = 0;
	for(i=0;i<linelen;i++)
	{
		if (line[i]==34)
		{	// open quote?
			// skip everything until the close quote
			for(i++;i<linelen;i++)
			{
				if (line[i]=='\\') { i++; continue; }
				if (line[i]==34) break;
			}
			continue;
		}

		if (alphanumericals[line[i]])
		{
			func[j++] = line[i];
		}
		else if (line[i] == ' ')
		{
			// hit a space, see if there are any other chars
			// besides whitespace between here and the next paren.
			// if so what we have is not a function, but if not,
			// then we can skip over the spaces and add it as a
			// function.
			for(i++;i<linelen;i++)
			{
				if (line[i]=='(') goto space_eliminated;
				if (!IS_WHITESPACE(line[i]))
				{
					if (alphanumericals[line[i]])
					{
						func[0] = line[i];
						j = 1;
					}
					else j = 0;
					break;
				}
			}
		}
		else
		{
			if (line[i]=='(')
			{
space_eliminated: ;
				if (j)
				{
					func[j] = 0;
					// we found a function call and it's in func!
					// but make sure it's not a reserved keyword like
					// if for or while
					if (!is_reserved_keyword(func))
					{
						//printf("found funccall: '%s'\n", func);
						if ((topindex = seek_to_top(index)) == -1) return 1;
						if (AddReferencedFunction(topindex, func)) return 1;
					}
				}
			}
			j = 0;
		}


	}

	return 0;
}



char addfunction(int index, uchar *line)
// add a function to source file "index", "line" specifies the raw
// line that was detected as containing a function define.
{
uchar funcname[MAXLEN];
int nfuncs;

	// get the name of the function.
	if (getfuncname(line, strlen(line), funcname))
		return 1;

	//printf("'%s' => '%s'\n", line, funcname);
	// no function can be named a reserved keyword (no 'void if()').
	if (is_reserved_keyword(funcname))
	{
		//printf("addfunction: not adding reserved keyword %s\n", funcname);
		return 0;
	}

	// strip at )
	FuncStripAtParen(line);
	if (!line[0]) return 0;

	// if a .c file includes a .c file, then the definition should go into the
	// .fdh for the top-level file, not the current .c file.
	if ((index = seek_to_top(index)) == -1) return 1;

	nfuncs = sources[index].stats[STAT_NUM_FUNCS];
	//printf("addfunction: adding '%s' to file %d [%s] as func #%d\n", funcname, index, sources[index].name, nfuncs);

	// add the function name
	sources[index].functions[nfuncs].name = strdup(funcname);
	if (!sources[index].functions[nfuncs].name)
	{
		printf("addfunction: out of memory, storing function name:\n");
		printf("\"%s\"\n\n", funcname);
		return 1;
	}

	// add the function prototype
	sources[index].functions[nfuncs].prototype = strdup(line);
	if (!sources[index].functions[nfuncs].prototype)
	{
		printf("addfunction: out of memory, storing function definition:\n");
		printf("\"%s\"\n\n", line);
		return 1;
	}

	// add a quicksearch node so we can rapidly discover later
	// that this function exists and what file it's in
	if (QSAddStringInt(funcname, QSKEY_PROTOTYPE, index, nfuncs)) return 1;

	// function has never been used in a .fdh so far
	sources[index].functions[nfuncs].lastrefdby = -1;

	// keep track of function counts
	if (strstr(line, "static "))
	{
		sources[index].stats[STAT_STATIC_FUNCS]++;
	}
	else
	{
		sources[index].stats[STAT_GLOBAL_FUNCS]++;
	}
	sources[index].stats[STAT_NUM_FUNCS]++;

	return 0;
}




struct
{
	uint file_no, func_no;
	uint reffrom;
} include_these[MAX_FUNCTIONS];
uint nFuncsToInclude;
unsigned int current_hash;

void fdh_build(int index, int toplevelindex)
// add all valid functions which were referenced by file 'index'
// into the include_these array.
{
int i;
int file_no, func_no;
stFuncReference *fr, *next;
char used_it;

	//printf("fdh_build %d (%s) _--groupi=%d---------------------------------\n", index, sources[index].name, groupi);

	//first add all the functions that are IN this file to the list of
	//funcs to include in the .fdh.
	//printf("source %s has %d funcs defined in it\n",sources[index].name,sources[index].stats[STAT_NUM_FUNCS]);
	for(i=0;i<sources[index].stats[STAT_NUM_FUNCS];i++)
	{
		include_these[nFuncsToInclude].file_no = index;
		include_these[nFuncsToInclude].func_no = i;
		include_these[nFuncsToInclude].reffrom = index;
		sources[index].functions[i].lastrefdby = toplevelindex;
		current_hash = updatehash(current_hash, sources[index].functions[i].prototype);
		nFuncsToInclude++;
	}

	// now add "imported" functions which are used in this module:

	// look at all the functions referenced by this module, find out
	// if any of them match actual functions defined somewhere in the
	// project, and add them to the fdh file.
	fr = sources[index].firstfunc;
	while(fr)
	{
		file_no = QSLookupInt(fr->funcname, QSKEY_PROTOTYPE, &func_no);

		used_it = 0;
		if (file_no != -1 && func_no != -1)
		{
			// don't add duplicate functions
			if (sources[file_no].functions[func_no].lastrefdby != toplevelindex)
			{
				sources[file_no].functions[func_no].lastrefdby = toplevelindex;

				current_hash = updatehash(current_hash, sources[file_no].functions[func_no].prototype);

				// add the function to the list of functions to put
				// in the .fdh file
				include_these[nFuncsToInclude].file_no = file_no;
				include_these[nFuncsToInclude].func_no = func_no;
				include_these[nFuncsToInclude].reffrom = index;
				nFuncsToInclude++;
				used_it = 1;
				//printf("source %s calls func: '%s'\n", sources[index].name, fr->funcname);
			}
		}

		next = fr->next;

		if (!used_it)
		{
			// remove it from the list so it doesn't clutter up the
			// cache when we write it.
			//printf("%s:crap: '%s'\n", sources[index].name, fr->funcname);
			if (fr->prev) fr->prev->next = next;
			if (next) next->prev = fr->prev;
			if (fr==sources[index].firstfunc) sources[index].firstfunc = next;
			free(fr);
		}
		/*else
		{
			printf("%s:good: '%s'\n", sources[index].name, fr->funcname);
		}*/

		fr = next;
	}

	// now add all functions referenced by every file it included,
	// like macros in .h files or sub-.c files
	/*for(i=0;i<sources[index].nDepends;i++)
	{
		fdh_build(sources[index].depends[i], toplevelindex);
	}*/
}

static char updatefdh(uint index)
// check if the .fdh file for sourcefile index needs to be
// updated, and if it does, it updates it.
// Return 1 if the file was updated, 0 if not.
// Returns -1 on error.
{
int i;
FILE *funcdefsfp;
int file_no, func_no, reffrom;
uint sort_file, lastreffrom;
uchar first;
#define DSLEN			68
uchar tempbuf[MAXLEN], dsbuf[DSLEN+1]; int x,l;
uchar fdhname[MAXFNAMELEN];
char *prefix;

	// first, build a list of all the functions that need to be included
	// in the file's .fdh file and get the hash of that list.
	// also we will always include all the functions that are defined IN "index".
	// (main.fdh always includes all functions from main.c).

	// add all functions referenced in the file to it's .fdh
	nFuncsToInclude = 0;
	current_hash = 0;
	fdh_build(index, index);

	if (options.dump_fdh)
	{
		printf("Functions to be included in %s.fdh (node %d, hash %08x):\n", sources[index].modulename, index, current_hash);
		for(i=0;i<nFuncsToInclude;i++)
		{
			file_no = include_these[i].file_no;
			func_no = include_these[i].func_no;
			reffrom = include_these[i].reffrom;

			printf("  %s: %s\n", sources[reffrom].name, sources[file_no].functions[func_no].prototype);
		}
	}

	strcpy(fdhname, sources[index].modulename);
	strcat(fdhname, fdh_ext_dot);
	//printf("fdhname = %s\n", fdhname);
	if (doesfdhneedupdate(fdhname, current_hash))
	{
		prefix = options.fimport ? "fimport " : "";

		// write the new version of the fdh...
		funcdefsfp = fopen(fdhname, "wb");
		if (!funcdefsfp)
		{
			printf("writefdhfile: unable to open funcdefs file %s\n", fdhname);
			return -1;
		}

		writehashline(current_hash, funcdefsfp);
		fprintf(funcdefsfp, FUNCDEFS_HEADER);

		for(sort_file=0;sort_file<nsources;sort_file++)
		{
			first = 1;
			lastreffrom = -1;
			for(i=0;i<nFuncsToInclude;i++)
			{
				if (include_these[i].file_no != sort_file) continue;

				file_no = include_these[i].file_no;
				func_no = include_these[i].func_no;
				reffrom = include_these[i].reffrom;

				if (first)
				{
					fprintf(funcdefsfp, "\n/* located in %s */\n\n", sources[sort_file].name);
					first = 0;
				}

				if (reffrom != lastreffrom)
				{
					sprintf(tempbuf, "[referenced from %s]", sources[reffrom].name);
					memset(dsbuf, '-', DSLEN-1);
					dsbuf[DSLEN] = 0;
					tempbuf[DSLEN-2] = 0;
					l = strlen(tempbuf);
					x = (DSLEN/2) - (l/2);
					memcpy(&dsbuf[x], tempbuf, l);
					fprintf(funcdefsfp, "//%s//\n", dsbuf);
					lastreffrom = reffrom;
				}

				fprintf(funcdefsfp, "%s%s;\n", prefix, sources[file_no].functions[func_no].prototype);
			}

			if (!first) fprintf(funcdefsfp, "\n");
		}

		fclose(funcdefsfp);

		return 1;
	}

	return 0;
}

char writefdhfiles(void)
{
int i;

	if (options.verbose)
	{
		printf("--- writing fdhs ---\n");
	}

	for(i=0;i<nsources;i++)
	{
		// no ".h" file is ever a top-level source.
		if (sources[i].nParents==0 && /*!sources[i].is_hfile && */
			!sources[i].hdrsec->noparse)
		{
//                        printf("=> '%s'\n", sources[i].name);
			if (updatefdh(i)==-1) return 1;
		}
	}
	return 0;
}


int seek_to_top(int index)
{
int i;
	while(sources[index].nParents)
	{
		//printf("File %s(%d) has %d parents and first parent is %d\n", sources[index].name, index, sources[index].nParents, sources[index].parents[0]);

		if (sources[index].nParents > 1)
		{
			printf("seek_to_top: error: Non-.h file %s is included by multiple other files--don't know which to place the .fdh in!\n", sources[index].name);
			printf("List of parents:\n");
			for(i=0;i<sources[index].nParents;i++)
			{
				printf("\t %s\n", sources[sources[index].nParents].name);
			}
			return -1;
		}

		// change file to the upper-level file
		index = sources[index].parents[0];
		//printf("Seeked up to %d\n", index);
	}
	return index;
}


void fdh_cleanup(void)
{
stFuncReference *fr, *next;
int i;

	for(i=0;i<nsources;i++)
	{
		fr = sources[i].firstfunc;
		while(fr)
		{
			next = fr->next;
			free(fr);
			fr = next;
		}
	}
}

#endif
