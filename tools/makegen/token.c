
// a tokening system which allows replacing of certain "variables"
// by their values.

// used to handle configuration of different compiler systems.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "makegen.h"

static void addtoken(token **last, token *t);
static uchar GetVarType(char *vname);


// splits up a line into tokens and returns the first token.
// this return value can then be passed to assemble_token().
token *tokenize(char *line)
{
int len = strlen(line);
int asize = len + 1;
token *firsttoken, *lasttoken;
token *t;
int i, j;
uchar ch;
char *ptr;

	//printf("tokenize: '%s'\n", line);
		
	if (!(t = malloc(sizeof(token))))
	{
		printf("tokenize: out of memory!\n");
		return NULL;
	}
	
	if (!(t->str = malloc(asize)))
	{
		printf("tokenize: out of memory(2)!\n");
		free(t);
		return NULL;
	}
	
	t->type = TKN_STRING;	
	firsttoken = lasttoken = t;
	
	for(i=j=0;i<len;i++)
	{
topofloop:

		ch = line[i];
		
		if (ch=='%')
		{
			if (line[i+1]=='%')		// %% is delimiter for %
			{
				t->str[j++] = '%';
			}
			else		// it's a variable!!
			{
				// end the current string token
				t->str[j] = 0; j = 0;
				
				addtoken(&lasttoken, t);
				// retrieve the variable name
				if (!(ptr = strchr(&line[++i], '%')))
				{
					printf("tokenize: odd number of '%%' on '%s'\n", line);
					goto failure;
				}
				
				*ptr = 0;
				//printf("varname: '%s'\n", &line[i]);
				
				// create a variable token and add it
				if (!(t = malloc(sizeof(token)))) goto allocfail;
				t->type = GetVarType(&line[i]);
				if (!t->type) goto failure;
				addtoken(&lasttoken, t);
				
				i += (ptr - &line[i]) + 1;
				//printf("rest of str: '%s'\n", &line[i]);
				
				// create a new string token and we'll continue parsing
				if (line[i])
				{
					if (!(t = malloc(sizeof(token)))) goto allocfail;
					if (!(t->str = malloc(asize))) goto allocfail;
					t->type = TKN_STRING;
					goto topofloop;
				}
			}
		}
		else
		{
			t->str[j++] = ch;
		}
	}
	
	
	if (j || !len)
	{
		t->str[j] = 0;
		addtoken(&lasttoken, t);
	}

	return firsttoken;
	
allocfail:
	printf("tokenize: Memory allocation failure!\n");
failure:
	// we failed--free up everything we created before exiting
	printf("tokenize: operation failed; on string beginning with:\n'%s'\n", line);
	token_cleanup(firsttoken);
	return NULL;
}


// tokenize a const char * without segfaulting
token *tokenize_const(const char *line)
{
char *tempbuf;
token *t = NULL;
	
	tempbuf = strdup(line);
	if (!tempbuf)
	{
		printf("tokenize_const: memory allocation error");
		return NULL;
	}

	t = tokenize(tempbuf);
	free(tempbuf);
	
	return t;
}

// creates a string from a tokenlist previously created by tokenize(),
// with the variables replaced by their current values.
// returns nonzero on error.
char assemble_token(token *firsttoken, char *str, ml_header *header, int src)
{
token *t;
int i;
char *catstr;

	i = str[0] = 0;
	
	t = firsttoken;
	while(t)
	{
		switch(t->type)
		{
			case TKN_STRING:
				catstr = t->str;
			break;
			
			case TKN_SRCFILE:
				if (src==-1) goto badvar;
				catstr = sources[src].name;
			break;

			case TKN_MODULE:
				if (src==-1) goto badvar;
				catstr = sources[src].modulename;
			break;

			case TKN_EXE:
				catstr = header->defsec->exe;
			break;

			case TKN_OUTPUT:
				catstr = header->defsec->exemodule;
			break;
			
			case TKN_CMDFILE:
				catstr = curcmdfilename;
			break;

			case TKN_OBJ_EXT: catstr = sources[src].hdrsec->obj_ext; break;
			case TKN_H_EXT: catstr = h_ext; break;
			case TKN_FDH_EXT: catstr = fdh_ext; break;
			case TKN_MLNAME: catstr = mlname; break;
			case TKN_MAKEFILE: catstr = makefile; break;
			
			default:
				printf("assemble_token: bad token type %d\n", t->type);
				return 1;
		}

		strcpy(&str[i], catstr);
		i += strlen(catstr);
		t = t->next;
	}
	
	return 0;

badvar:
	printf("assemble_token: specified variable makes no sense in this context!\n");
	printf("line up to now: '%s'\n", str);
	return 1;
}

// deallocate a tokenlist
void token_cleanup(token *firsttoken)
{
token *t, *next;

	t = firsttoken;
	while(t)
	{
		next = t->next;
		free(t);
		t = next;
	}
}

static void addtoken(token **last, token *t)
{
	/*printf("adding token %d",t->type);
	if (!t->type) printf(" str '%s'", t->str);
	printf("\n");*/
	
	(*last)->next = t;
	t->next = NULL;
	*last = t;
}

// returns a Token Type from a varname, or 0.
static uchar GetVarType(char *vname)
{
	if (!stricmp(vname, "SRCFILE")) return TKN_SRCFILE;
	if (!stricmp(vname, "MODULE")) return TKN_MODULE;
	if (!stricmp(vname, "OUTPUT")) return TKN_OUTPUT;
	if (!stricmp(vname, "EXEFILE")) return TKN_EXE;
	if (!stricmp(vname, "CMDFILE")) return TKN_CMDFILE;
	if (!stricmp(vname, "OBJ_EXT")) return TKN_OBJ_EXT;
	if (!stricmp(vname, "H_EXT")) return TKN_H_EXT;
	if (!stricmp(vname, "FDH_EXT")) return TKN_FDH_EXT;
	if (!stricmp(vname, "MLNAME")) return TKN_MLNAME;
	if (!stricmp(vname, "MAKEFILE")) return TKN_MAKEFILE;
	
	printf(" ** unknown token variable '%s'\n", vname);
	return 0;
}

