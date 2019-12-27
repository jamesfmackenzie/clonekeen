/*
	MAKEGEN
	(c)Caitlin Shaw 2007-2009

	Source code released under GNU General Public License v3
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>			// so we can use tolower()

#include "constants.h"		// <-- see this for basic setup
#include "makegen.h"

#define REVISION			"makegen III patch 2 r07.16.09"
/* if you modify this program and want your name in the about,
   put something here */
//#define MODDEDBY			"Jeffrey Sinclair"		// <-- example


int nLinesParsed, nFilesParsed;

char curcmdfilename[MAXFNAMELEN];
int cmdfileno;

uchar makefile[MAXFNAMELEN];
uchar mlname[MAXFNAMELEN];
uchar h_ext[MAXFNAMELEN];
uchar fdh_ext_dot[MAXFNAMELEN];
uchar *fdh_ext;

stSrcFile sources[MAX_FILES];
int nsources;


//void bp(void) {}


#include "getline.c"


void CollapsePath(char *path)
// given a path, collapses all '.' and '..''s, in other words, removes '.''s
// and causes '..''s to cancel out the directory before them, thus finding
// the simplest way to express the given path.
{
int i,j;
int ndirs;
struct
{
	char name[MAXLEN];
	char skip;
} dirs[256];

	//printf("CollapsePath: job \"%s\"\n", path);
	
	// split the path into each directory
	ndirs = 0;
	for(i=j=0;i<=strlen(path);i++)
	{
		if (path[i]=='/' || path[i]=='\\' || path[i]==0)
		{
			dirs[ndirs].name[j] = 0;
			dirs[ndirs].skip = 0;
			//printf("dir '%s'\n", dirs[ndirs].name);
			
			ndirs++;
			j = 0;
		}
		else dirs[ndirs].name[j++] = path[i];
	}
	
	// now collapse .'s and ..'s
	for(i=0;i<ndirs;i++)
	{
		//printf("collapse: %s\n", dirs[i].name);
		if (!strcmp(dirs[i].name, "."))		// skip '.''s entirely
		{
			dirs[i].skip = 1;;
		}
		else if (!strcmp(dirs[i].name, ".."))
		{
			//printf("found .. at index %d\n", i);
			if (i != 0)
			{
				//printf("  i != 0, previous dir = '%s'\n", dirs[i-1].name);
				if (strcmp(dirs[i-1].name, ".."))	// allow '../..'
				{
					//printf("    collapsing\n");
					dirs[i-1].skip = 1;
					dirs[i].skip = 1;
				}
			}
		}
	}

	// piece the path back together
	path[0] = 0;
	for(i=0;i<ndirs;i++)
	{
		//printf("pathpart: '%s'\n", dirs[i].name);
		if (!dirs[i].skip)
		{
			if (path[0]) strcat(path, "/");
			strcat(path, dirs[i].name);
		}
	}
}

void GetPath(char *fname, char *path)
// retrieves the path portion of filename fname, if any,
// and copies it into path.
{
int len = strlen(fname);
int i;

	// find last '/' seperator
	for(i=len-1;i>=0;i--)
	{
		if (fname[i]=='/' || fname[i]=='\\')
		{
			// copy the rest of the string into path.
			path[i+1] = 0;
			for(;i>=0;i--)
			{
				path[i] = fname[i];
			}
			return;
		}
	}
	// there is no path
	path[0] = 0;
	return;
}

char HaveSourceFile(char *file)
{
int i;
	for(i=0;i<nsources;i++)
	{
		if (!stricmp(sources[i].name, file))
			return i;
	}
	return -1;
}

int AddSourceFile(char *name)
// adds a file to the sources list
{
char *dot;

	strcpy(sources[nsources].name, name);
	// compute module name (filename without the '.')
	strcpy(sources[nsources].modulename, name);
	if ((dot = strrchr(sources[nsources].modulename, '.')))
		*dot = 0;
	
	sources[nsources].nDepends = 0;
	sources[nsources].nParents = 0;
	sources[nsources].firstfunc = NULL;
	sources[nsources].lastfunc = NULL;
	sources[nsources].hdrsec = NULL;		// default to no special compile cmd
	sources[nsources].fromcache = 0;
	memset(sources[nsources].stats, 0, sizeof(sources[nsources].stats));
	//printf("Adding source file '%s' (%d)\n", name, nsources);
	
	return (nsources++);
}


int parsefile(uchar *file, int parent, int recursion)
// add a ".c" or ".h" source file, processing all sub-included source files.
// returns the index in sources[] the file was added at.
// returns SRC_ERROR on error.
// returns SRC_FILE_ALREADY_PARSED if the file has already been added.
// returns SRC_FILE_IGNORED if the file should not be parsed.
{
uchar line[MAXLEN];
int linelen;
FILE *fp;
int index;
uchar *ext;
uchar filepath[MAXLEN];
char path_known;
int lineno;
char *incfile;
char hfile;

	//printf("parsefile: '%s', parent=%d, recursion=%d\n", file, parent, recursion);
	
	if (nsources >= MAX_FILES)
	{
		printf("Too many files in project (max set at %d)\n", MAX_FILES);
		return 1;
	}

	// has this file already been parsed? if so just make our
	// parent depend on us and that's all we have to do.
	if ((index = HaveSourceFile(file)) != -1)
	{
		if (parent != -1) AddDependency(parent, index);
		return SRC_FILE_ALREADY_PARSED;
	}
	
	// no, we'll add it //
	
	// get extension of file
	if (!(ext = strrchr(file, '.')))
		ext = "";
	else
		ext++;
	
	// check for file extensions we'll want to know about
	if (!stricmp(ext, h_ext))				// .h
	{
		hfile = 1;
	}
	else
	{
		if (!stricmp(ext, fdh_ext))			// .fdh
		{
			return SRC_FILE_IGNORED;
		}
		else
		{
			hfile = 0;
		}
	}

	// add the source to the list
	index = AddSourceFile(file);
	sources[index].is_hfile = hfile;

	// handle tree-mode display of files as they're parsed
	if (options.tree)
	{
		int len = (recursion + recursion) + 1;
		uchar levelstr[MAXLEN];
		uchar *parentname;
		
		if (parent == -1)
			parentname = "top level";
		else
			parentname = sources[parent].name;
		
		memset(levelstr, ' ', len); levelstr[len] = 0;
		printf("%s==: %s  (from %s)\n", levelstr, file, parentname);
	}
		
	
	// if this is a top-level file check to see if we can just get
	// dependency data out of the cache instead of reprocessing
	if (options.use_cache)
	{
		if (parent == -1)
		{
			int chandle, crap;
			if ((chandle = QSLookupInt(file, QSKEY_CACHE, &crap)) != -1)
			{
				if (!LoadSourceFromCache(chandle, index))
				{
					return index;
				}
				else return SRC_ERROR;
			}
		}
		else
		{		// not top level-- make ourselves a dependency of our parent
			AddDependency(parent, index);
			// notify the cache system that we're going to process this file,
			// it will remove it from the list of sub-level files which were
			// not processed because they were only included by a cached file.
			CacheRemoveSublevel(index);
		}
	}
	else
	{
		if (parent != -1) AddDependency(parent, index);
	}
	
	fp = fopen(file, "rb");
	if (!fp)
	{
		printf("makegen: error: source file %s could not be opened!\n", file);
		return SRC_ERROR;
	}
	
	//printf("parsefile: actually parsing (not using cache): %s\n", file);
	nFilesParsed++;
	
	// parse the file. look for:
	// * function definitions - for fdh's
	// * include files - to calc dependencies
	// * referenced functions (function calls) - for fdh's
	path_known = lineno = 0;
	while(!feof(fp))
	{
		linelen = mgetline(fp, line, sizeof(line));		
		lineno++;
		if (!linelen) continue;

		sources[index].stats[STAT_LINES]++;
		nLinesParsed++;

		// handle #include directives
		if (line[0]==PREPROCESSOR_CHAR && \
			(incfile = StringStartsWith(&line[1], INCLUDE_DIRECTIVE)))
		{
			if (incfile[0]==LOCALQUOTE)		// skip e.g. <stdio.h>
			{					
				char incfilefullpath[MAXLEN];
				
				if (!(incfile = RemoveQuotes(incfile)))
				{
					printf("RemoveQuotes failed: %s near line %d\n", file, lineno);
					fclose(fp);
					return SRC_ERROR;
				}
				
				// get path of the current source file we're in
				// so we can apply it to the included file
				if (!path_known)
				{
					GetPath(file, filepath);
					path_known = 1;
				}
				strcpy(incfilefullpath, filepath);
				strcat(incfilefullpath, incfile);
				CollapsePath(incfilefullpath);
				
				if (parsefile(incfilefullpath, index, recursion+1)==SRC_ERROR)
				{
					printf("parsefile failed: %s near line %d\n", file, lineno);
					fclose(fp);
					return SRC_ERROR;
				}					
			}
		}
		else if (!sources[index].is_hfile && !options.no_fdh)
		{
			// detect functions headers (void foo(void)) for fdh generation
			if (is_function_definition(line, linelen))
			{				
				if (addfunction(index, line))
				{
					printf("addfunction failed(): %s near line %d\n", file, lineno);
					fclose(fp);
					return SRC_ERROR;
				}
			}
			else
			{					
				// detect function calls (foo()) so we know which prototypes are needed
				if (detectfunctioncalls(line, linelen, index))
				{
					printf("detectfunctioncalls failed: %s near line %d\n", file, lineno);
					return SRC_ERROR;
				}
			}
		}
	}	
	
	// file parsed ok
	fclose(fp);
	return index;
}


FILE *OpenNextCmdFile(void)
{
FILE *fp;
	sprintf(curcmdfilename, "mgbuild%03d.dat", cmdfileno++);
	fp = fopen(curcmdfilename, "wb");
	if (!fp)
	{
		printf("failed opening command file %s\n", curcmdfilename);
		return NULL;
	}
	return fp;
}

void DumpTopLevel(FILE *fp, char cr)
// dump the compiled object names of all top level sources files
// (files without parents) to fp, and if show is 1 display their C file names
{
int i;
char count;
	
	count = 0;
	for(i=0;i<nsources;i++)
	{
		if (sources[i].nParents==0)
		{
			if (cr && ++count >= 5)
			{
				fprintf(fp, " \\\n\t");
				count = 0;
			}
			
			fprintf(fp, " %s.%s", sources[i].modulename, sources[i].hdrsec->obj_ext);
		}
	}
}

ml_header *process_makelist(uchar *listfilename)
{
FILE *fp;
uchar line[MAXLEN], srcfile[MAXLEN];
//uchar pathprefix[MAXFNAMELEN];
int fno;
ml_header *header;
ml_header_section *section;
char *specialsec;

	if (options.verbose) printf("** processing makelist %s\n", listfilename);
	
	fp = fopen(listfilename, "rb");
	if (!fp)
	{
		printf("process_makelist: CAN'T OPEN %s\n", listfilename);
		return NULL;
	}
	
	// get the path to the makelist which we will prefix to all
	// the files included as a result of this makelist
	//GetPath(listfilename, pathprefix);
	
	if (!(header = ML_ReadHeader(fp)))
		{ fclose(fp); return NULL; }
	
	if (options.verbose)
	{
		printf("Output executable will be \"%s\".\n", header->defsec->exe);
	}
	
	if (options.verbose || options.tree)
		printf("\n--- building '%s' dependency tree ---\n", listfilename);
	
	// read in the list of files in the makelist and process each one.
	while(1)
	{
		fgetline(fp, line, sizeof(line));

		// check for EOF
		if (feof(fp) || line[0]=='<')
		{
			if (options.verbose) printf("reached end of makelist: %s\n", listfilename);
			break;
		}

		// ignore blank lines and comments
		if (line[0]==0 || line[0]=='#' || line[0]=='/')
			continue;

		// read any special compile commands just for this file
		if ((specialsec = strstr(line, " : ")))
		{
			*specialsec = 0; specialsec += 3;
			
			//printf("found compile str: '%s'\n", specialsec);
			if (!(section = Hdr_FindSection(header, specialsec)))
			{
				printf(" * unknown header section '%s' associated with file '%s'\n", specialsec, line);
				return NULL;
			}
		}
		else
		{
			section = header->defsec;
		}

		/// hack, fixme
		strcpy(srcfile, line);

		if (!section->noparse)
		{	// go down into the source file and parse it
			fno = parsefile(srcfile, -1, 0);
		}
		else
		{	// file is a resource script, etc. just add it to sources list
			fno = AddSourceFile(srcfile);
			if (options.verbose) printf("not parsing '%s' but added it as source no %d\n", srcfile, fno);
		}

		if (fno==SRC_ERROR)
		{
			return NULL;
		}
		else if (fno==SRC_FILE_ALREADY_PARSED)
		{
			printf("** WARNING: top-level file %s is also #included by another source file.\n", srcfile);
		}
		else
		{	// save which header section it used
			sources[fno].hdrsec = section;
		}
	}
	fclose(fp);

	return header;
}


char genmakefile(uchar *listfilename, uchar *makefilename)
{
FILE *fp;
ml_header *h;
ml_header_section *sect;
int i;
char tstr[MAXLEN];

	nsources = 0;
	nFilesParsed = 0;
	
	// load the makelist and parse all files in it.
	// this call sets off most of makegen's work.
	if (!(h = process_makelist(listfilename))) return 1;
	

	if (options.tree) printf("\n");
	
	// write the '.fdh' files
	if (!options.no_fdh)
	{
		
		if (writefdhfiles()) return 1;
	}

	if (options.tree || options.verbose)
	{
		printf("--- generating %s ---\n", makefilename);
	}

	
	// >> Now generate the Makefile <<
		
	fp = fopen(makefilename, "wb");
	if (!fp)
	{
		printf("unable to open %s for writing\n", makefilename);
		return 1;
	}
	
	fprintf(fp, "\nall: %s\n\n", h->defsec->exe);

	
	// generate the linker directive  ///////////////////

	
	// dump the dependency line
	fprintf(fp, "%s: ", h->defsec->exe);
	DumpTopLevel(fp, 1);

	// linking command (shell line)
	if (!h->defsec->Link_Usefiles)		// normal
	{
		if (assemble_token(h->defsec->LinkPrefix, tstr, h, -1)) goto failure;
		fprintf(fp, "\n\t%s \\\n\t", tstr);
		DumpTopLevel(fp, 1);
		
		if (assemble_token(h->defsec->LinkSuffix, tstr, h, -1)) goto failure;
		fprintf(fp, " \\\n\t %s\n\n", tstr);
	}
	else	// args to linker passed in a tempfile
	{
		FILE *fpt = OpenNextCmdFile();
		if (!fpt) goto failure;
		
		if (assemble_token(h->defsec->LinkPrefix, tstr, h, -1)) goto failure;
		fputs(tstr, fpt);
		DumpTopLevel(fpt, 0);
		
		if (assemble_token(h->defsec->LinkSuffix, tstr, h, -1)) goto failure;
		fprintf(fpt, " %s\n", tstr);

		fclose(fpt);
		
		// generate the string the actually goes in the makefile
		if (assemble_token(h->defsec->LinkInvoke, tstr, h, -1)) goto failure;
		fprintf(fp, "\n\t%s\n\n", tstr);
	}
	
	// source file compilation instructions  ///////////////////

	// generate compile directives for all the top-level files.
	for(i=0;i<nsources;i++)
	{
		if (!sources[i].is_hfile && sources[i].nParents==0)
		{
	//printf("gen compile dir for %d: '%s'\n", i, sources[i].name);
			// get header section used by this file
			if (!(sect = sources[i].hdrsec))
			{
				printf("section not set on file %s (internal error)\n", sources[i].name);
				return 1;
			}

			// object file and it's dependencies (source & include files)
			if (i) fprintf(fp, "\n\n");
			fprintf(fp, "%s.%s:\t%s", sources[i].modulename, sect->obj_ext, sources[i].name);

			if (!options.no_fdh && !sect->noparse)
			{	// automatically make it depend on it's .fdh file
				fprintf(fp, " %s%s", sources[i].modulename, fdh_ext_dot);
			}
			
			// dump everything it's dependent on
//printf("starting dep dump\n");
			DumpDependencies(fp, i, 1);
			fputs("\n", fp);
//printf("depdump done\n");
			
			// output shell line
			if (assemble_token(sect->Compile, tstr, h, i)) goto failure;
			
			if (!sect->Compile_Usefiles)
			{	// normal (compile args are just passed on command line)
				fprintf(fp, "\t%s", tstr);
			}
			else
			{	// compile args are in an seperate "temp" file.
				// ok whatever, generate the file...
				FILE *fpt = OpenNextCmdFile();
				if (!fpt) goto failure;
				
				fprintf(fpt, "%s\n", tstr);
				fclose(fpt);

				// generate the line that'll go into the makefile
				if (assemble_token(sect->CompileInvoke, tstr, h, i)) goto failure;
				fprintf(fp, "\t%s", tstr);				
			}
		}
	}
	fprintf(fp, "\n");

	// generate 'make clean'
	fprintf(fp, "\n\nclean:\n");
	for(i=0;i<nsources;i++)
	{
		if (sources[i].nParents==0 && strcmp(sources[i].ext, h_ext))
			fprintf(fp, "\trm -f %s.%s\n", sources[i].modulename, sources[i].hdrsec->obj_ext);
	}

	if (!options.no_fdh)
	{
		fprintf(fp, "\ncleanfdh:\n");
		for(i=0;i<nsources;i++)
		{
			if (sources[i].nParents==0 && strcmp(sources[i].ext, h_ext))
				fprintf(fp, "\trm -f %s%s\n", sources[i].modulename, fdh_ext_dot);
		}
		fprintf(fp, "\ncleanall: clean cleanfdh\n\n");
	}
	else
	{
		fprintf(fp, "\ncleanall: clean\n\n");
	}

	fclose(fp);
	return 0;
failure:
	printf("genmakefile: operation failed\n");
	/// really should clean up tokens here
	fclose(fp);
	return 1;
}



char procargs(int argc, char **argv)
{
int i;
char mode, val;
char *opt;
int fno;

	// set to defaults
	memset(&options, 0, sizeof(options));
	
	mlname[0] = 0; makefile[0] = 0;
	fno = 0;
	
	for(i=1;i<argc;i++)
	{
		mode = argv[i][0];
		if (mode=='+' || mode=='-' || mode=='/')
		{
			if (mode=='-') val = 0; else val = 1;
			opt = &argv[i][1];
			
			if (!stricmp(opt, "q")) options.silent = val;
			else if (!stricmp(opt, "v")) options.verbose = val;
			else if (!stricmp(opt, "k")) options.fimport = val;
			else if (!stricmp(opt, "tree")) options.tree = val;
			else if (!stricmp(opt, "summary")) options.nosummary = val^1;
			else if (!stricmp(opt, "no-fdh")) options.no_fdh = 1;
			else if (!stricmp(opt, "dump-fdh")) options.dump_fdh = 1;
			else if (!stricmp(opt, "usecache")) options.use_cache = 1;
			else if (!stricmp(opt, "use-cache")) options.use_cache = 1;
			else if (!stricmp(opt, "recache")) { options.recache = 1; GetCacheFileName(); }
			else if (!stricmp(opt, "no-cache"))
			{
				printf(" * Makegen: Ignoring deprecated option no-cache\n");
			}
			else if (opt[0]=='?') return 1;
			else
			{
				printf(" ** Unknown option '%s'\n", opt);
				return 1;
			}
		}
		else
		{
			switch(fno++)
			{
				case 0: strcpy(mlname, argv[i]); break;
				case 1: strcpy(makefile, argv[i]); break;
				
				default:
					printf(" ** Invalid options '%s'\n", argv[i]);
			}
		}
	}

	if (!mlname[0]) strcpy(mlname, MAKELIST_DEFAULT);
	if (!makefile[0]) strcpy(makefile, MAKEFILE_DEFAULT);
	
	if (options.silent)
	{
		options.verbose = 0;
		options.tree = options.dump_fdh = 0;
		options.nosummary = 1;
	}
	else if (options.tree)
	{	// tree will be wrong if any files are loaded from cache
		options.use_cache = 0;
	}
	return 0;
}

void usage(char *exepath)
{
uchar path[MAXFNAMELEN];
uchar *progname;
char *ptr;
int i;

	// get name of executable without the path or extension
	GetPath(exepath, path);
	progname = &exepath[strlen(path)];
	if ((ptr = strrchr(progname, '.'))) *ptr = 0;
	
	printf("usage: %s [makelist-name] [makefile-name] [+/-tree] [+/-summary]\n", progname);
	for(i=0;i<strlen(progname)+8;i++) printf(" ");
	printf("[+no-fdh] [+use-cache] [+recache] [+q] [+v]\n\n");

	printf("+/-tree:     Turn on/off displaying a tree showing the source file hierarchy.\n");
	printf("             Default OFF. Turning this on also disables the cache.\n\n");
	printf("+/-summary:  Turn on/off 'ls'-style source file listing and statistics.\n");
	printf("             Default ON.\n\n");
	printf("+no-fdh:     Do not generate any .fdh (function declaration) files.\n");
	printf("             Default OFF.\n\n");
	printf("+dump-fdh:   Dump information on .fdh file contents to console.\n\n");
	printf("+use-cache   Activate experimental caching function.\n\n");
	printf("+recache:    Ignore cache file if present, and generate a new one.\n\n");
	printf("+q:          Quiet. Display no messages at all.\n\n");
	printf("+v:          Verbose. Display tons of messages.\n\n");
	printf("+k:          Write K-compatible .fdh files using 'fimport'\n\n");
	
	printf("[makelist-name]: change the name of the input makelist. If omitted, it defaults\n");
	printf("                 to '%s'.\n\n", MAKELIST_DEFAULT);
	
	printf("[makefile-name]: specifies the name of the makefile to create. If omitted, it\n");
	printf("                 defaults to '%s'.\n\n", MAKEFILE_DEFAULT);
	
	printf("Listing formats: Stats in the summary listing are listed in the following\n");
	printf("format: [filename](#_functions)(#_static_functions).\n");
	printf("On the 'makelist.ml done' line, 1st number is the total GLOBAL functions in the\n");
	printf("project. 2nd number is total functions in project. File in '[[ ]]' shows which\n");
	printf("module exports the highest number of functions. This is followed by the total\n");
	printf("number of non-blank, non-comment lines in the project, and the number of lines\n");
	printf("which were re-parsed (not loaded from cache).\n");
	
	printf("\n%s; by Caitlin Shaw", REVISION);
	#ifdef MODDEDBY
		printf("; w/ revisions by %s.\n", MODDEDBY);
	#else
		printf(".\n");
	#endif
}

int main(int argc, char **argv)
{
	/*{
		char *f = "int LoadTile(char *fname, int t, int frame)";
		int ok = is_function_definition(f, strlen(f));
		printf("--%d\n", ok);
		
		return 0;
	}*/
	
	if (procargs(argc, argv))
	{
		usage(argv[0]);
		return 1;
	}

	if (QSInit(QS_NUM_KEYS)) return 1;
	fdh_init();
	
	nLinesParsed = 0;
	cmdfileno = 0;
	nsources = 0;
	
	if (options.tree || options.verbose)
	{
		printf("%s\n\ngenerating \"%s\" from makelist %s\n", REVISION, makefile, mlname);
	}

	// try to load the cache so we don't have to re-process
	// files that haven't changed
	if (options.use_cache && !options.recache)
	{
		if (LoadCacheHeader()) return 1;
	}
	
	if (genmakefile(mlname, makefile)) return 1;
	
	if (!options.nosummary) ShowSummary();
	else if (options.tree) printf("\n");

	// generate the cache
	if (options.use_cache)
	{
		if (gencache()) return 1;
	}
	
	if (!options.silent) ShowStatLine();

	if (options.use_cache) CacheFreeSubStats();
	fdh_cleanup();
	QSClose();
	return 0;
}
