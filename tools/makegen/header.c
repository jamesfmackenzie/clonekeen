
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "makegen.h"

static ml_header_section *addsection(char *name, ml_header *hdr);
static char AssignValue(char *assign, char *value, ml_header_section *h);
static char AssignGlobalValue(char *assign, char *value, ml_header_section *h);
static char FinishSection(ml_header_section *h, ml_header *hdr);
static char try_assign(token **dest, char *assignlook, char *assign, char *value);


// reads the header of a .ml file and returns a header struct
ml_header *ML_ReadHeader(FILE *fp)
{
ml_header *hdr;
ml_header_section *cursec;
char line[MAXLEN];
char ok;

	//printf("\n\nreading header.\n");
	
	hdr = malloc(sizeof(ml_header));
	if (!hdr)
	{
		printf("ML_ReadHeader: out of memory!");
		return NULL;
	}
	
	hdr->firstsec = NULL;
	hdr->defsec = cursec = addsection("DEFAULT", hdr);
	if (!cursec) goto error;

	h_ext[0] = 0;
	fdh_ext_dot[0] = 0;

	while(1)
	{
		if (feof(fp))
		{
			printf("ML_ReadHeader: unexpected end of file while parsing header.\n");
			goto error;
		}
		
		fgetline(fp, line, sizeof(line));
		if (!line[0]) continue;
		
		//printf("'%s': '%s'\n", cursec->name, line);
		
		
		if (line[0]=='<')			// start of new header section
		{
			if (!(cursec = Hdr_FindSection(hdr, &line[1])))
			{
				cursec = addsection(&line[1], hdr);
				if (!cursec) goto error;
			}
		}
		else if (line[0]=='>')		// end of header
		{
			break;
		}
		else
		{	// split up assignment at '=' sign
			char *assign, *valptr, *value;
			
			valptr = strchr(line, '=');
			if (!valptr)
			{
				printf("header parse error: no '=' on line '%s'\n", line);
				goto error;
			}
			
			*valptr = 0; valptr++;
			assign = line;
			
			if (!(value = RemoveQuotes(valptr))) goto error;
			
			
			if ((ok = AssignValue(assign, value, cursec)) != 1)
			{
				if (ok==-1) goto error;
				
				if ((ok = AssignGlobalValue(assign, value, cursec)) != 1)
				{
					if (ok==-1) goto error;
					printf(" ** unknown header assignment '%s' = '%s' in file '%s'\n", assign, value, mlname);
					goto error;
				}
				else if (cursec != hdr->defsec)
				{
					printf(" ** header variable '%s' has no effect outside default section\n", assign);
					goto error;
				}
			}
		}
	}
	
	// assign defaults to values that didn't get set
	if (hdr->defsec->Link_Usefiles && !hdr->defsec->LinkInvoke)
	{
		printf(" * error: LINK_USEFILES=1 but no LINK_INVOKE string\n");
		goto error;
	}

	if (!hdr->defsec->LinkPrefix)
	{
		if (!(hdr->defsec->LinkPrefix = tokenize_const("gcc -o %EXEFILE%"))) goto error;
	}
	
	if (!hdr->defsec->Compile)
	{
		if (!(hdr->defsec->Compile = tokenize_const("gcc -c %SRCFILE% -o %MODULE%%OBJ_EXT%"))) goto error;
	}

	if (hdr->defsec->Compile_Usefiles==-1) hdr->defsec->Compile_Usefiles = 0;

	if (!hdr->defsec->exe[0]) strcpy(hdr->defsec->exe, "OUTPUT");

        if (!hdr->defsec->obj_ext[0]) strcpy(hdr->defsec->obj_ext, "o");
	if (!h_ext[0]) strcpy(h_ext, "h");

	if (!fdh_ext_dot[0])
	{
		strcpy(fdh_ext_dot, ".fdh");
	}
	
	fdh_ext = &fdh_ext_dot[1];

	// do finishing processing on all sections
	cursec = hdr->firstsec;
	while(cursec)
	{
		if (FinishSection(cursec, hdr)) goto error;
		cursec = cursec->next;
	}
	
	return hdr;

error: ;
	printf("ML_ReadHeader: operation failed\n");
	ML_FreeHeader(hdr);
	return NULL;
}



static char AssignValue(char *assign, char *value, ml_header_section *h)
{	
char ok;

	ok = try_assign(&h->Compile, "COMPILE", assign, value);
	if (ok) return ok;

	ok = try_assign(&h->CompileInvoke, "COMPILE_INVOKE", assign, value);
	if (ok) return ok;

	
	if (!stricmp(assign, "COMPILE_USEFILES"))
	{
		h->Compile_Usefiles = (value[0] != '0') ? 1:0;
	}
	else if (!stricmp(assign, "NOPARSE"))
	{
		h->noparse = (value[0] != '0') ? 1:0;
	}
	else if (!stricmp(assign, "obj_ext"))
	{
		validate_ext(value);
		strcpy(h->obj_ext, &value[1]);		// do NOT include the dot
	}
	else
	{
		return 0;
	}
	
	return 1;
}


static char AssignGlobalValue(char *assign, char *value, ml_header_section *h)
{
char ok;

	ok = try_assign(&h->LinkPrefix, "LPREFIX", assign, value);
	if (ok) return ok;

	ok = try_assign(&h->LinkSuffix, "LSUFFIX", assign, value);
	if (ok) return ok;
	
	ok = try_assign(&h->LinkInvoke, "LINK_INVOKE", assign, value);
	if (ok) return ok;
	
	
	if (!h->exe[0] && !stricmp(assign, "OUTPUT"))
	{
		char *ptr;
		strcpy(h->exe, value);
		if ((ptr = strrchr(value, '.')))	// strip .exe extension if present
		{
			*ptr = 0;
		}
		strcpy(h->exemodule, value);
	}
	else if (!stricmp(assign, "LINK_USEFILES"))
	{
		h->Link_Usefiles = (value[0] != '0') ? 1:0;
	}
/*	else if (!stricmp(assign, "IGNOREFILEPATHS"))
	{
		h->IgnoreFilePaths = (value[0] != '0') ? 1:0;
	}*/
	else if (!stricmp(assign, "INCLUDE_EXT"))
	{
		validate_ext(value);
		strcpy(h_ext, &value[1]);		// h_ext does NOT include a dot
	}
	else if (!stricmp(assign, "fdh_ext_dot"))
	{
		validate_ext(value);
		strcpy(fdh_ext_dot, value);
	}
	else
	{
		return 0;
	}
	
	return 1;
}


static char try_assign(token **dest, char *assignlook, char *assign, char *value)
{
	if (!*dest && !stricmp(assign, assignlook))
	{
		*dest = tokenize(value);
		if (!*dest) return -1;
		return 1;
	}
	return 0;
}


ml_header_section *addsection(char *name, ml_header *hdr)
{
ml_header_section *h;

	h = malloc(sizeof(ml_header_section));
	if (!h)
	{
		printf("addsection: out of memory adding header section '%s'!\n", name);
		return NULL;
	}
	
	strcpy(h->name, name);
	
	h->Compile_Usefiles = -1;
	h->Link_Usefiles = 0;
	//h->IgnoreFilePaths = 0;
	h->noparse = 0;

	h->exe[0] = 0;
	h->obj_ext[0] = 0;

	h->Compile = NULL;
	h->CompileInvoke = NULL;
	h->LinkPrefix = NULL;
	h->LinkSuffix = NULL;
	
	h->next = hdr->firstsec;
	hdr->firstsec = h;
	return h;
}


static char FinishSection(ml_header_section *h, ml_header *hdr)
{
	//printf("Finishing '%s'\n", h->name);
	
	// inherit unset values from default
	if (!h->Compile) h->Compile = hdr->defsec->Compile;
	if (!h->CompileInvoke) h->CompileInvoke = hdr->defsec->CompileInvoke;
	
	if (h->Compile_Usefiles==-1)
		h->Compile_Usefiles = hdr->defsec->Compile_Usefiles;
	
	if (!h->obj_ext[0])
		strcpy(h->obj_ext, hdr->defsec->obj_ext);

	if (h->Compile_Usefiles && !h->CompileInvoke)
	{
		printf(" * error: COMPILE_USEFILES=1 but no COMPILE_INVOKE string\n");
		return 1;
	}
	
	return 0;
}


void ML_FreeHeader(ml_header *hdr)
{
ml_header_section *h = hdr->firstsec;
ml_header_section *next;

	while(h)
	{
		next = h->next;
		free(h);
		h = next;
	}
	free(hdr);
}


ml_header_section *Hdr_FindSection(ml_header *hdr, char *name)
{
ml_header_section *h = hdr->firstsec;

	while(h)
	{
		if (!stricmp(h->name, name)) break;
		h = h->next;
	}
	return h;
}

