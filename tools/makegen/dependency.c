
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#include "makegen.h"

static void dep_do_dump(FILE *fp, int i, char tabulate);
static void dumpdep(char *name, FILE *fp, char tabulate);
static void initdumpdep(void);
static void cleandumpdep(void);

typedef struct
{
	char *name;
} stDepOutputRec;
stDepOutputRec deps[MAX_FILES];

int ndeps;
int dcount;


void AddDependency(uchar index, uchar dependency)
// adds source file 'dependency' to 'index's dependency list
{
	//printf("Making source (%s)%d depend on %s(%d)\n", sources[index].name, index, sources[dependency].name, dependency);
	sources[index].depends[sources[index].nDepends++] = dependency;
	sources[dependency].parents[sources[dependency].nParents++] = index;
	//printf("AddDependency: %s now depends on %s\n", sources[index].name, sources[dependson].name);
	//printf(" - %s has %d dependencies now\n", sources[index].name, sources[index].nDepends);
	//printf(" - %s is depended on by %d files\n", sources[dependson].name, sources[dependson].nParents);
}


void DumpDependencies(FILE *fp, int i, char tabulate)
// dump dependencies of source i into file fp.
// used when generating the makefile and when writing the cache.
// pass tabulate=1 if making a Makefile,
// pass tabulate=0 if writing to the cache file
{
	initdumpdep();
	dep_do_dump(fp, i, tabulate);
	cleandumpdep();
}


// used internally by DumpDependencies
static void dumpdep(char *name, FILE *fp, char tabulate)
{
int i;
	// make sure this file hasn't already been added...
	for(i=0;i<ndeps;i++)
	{
		if (!stricmp(deps[i].name, name)) return;
	}
	// add it the list of files that've been added
	deps[ndeps++].name = strdup(name);
	
	if (tabulate)
	{
		if (++dcount >= 3)
		{
			fprintf(fp, " \\\n\t\t%s", name);
			dcount = 0;
		}
		else
		{
			fprintf(fp, " %s", name);
		}
	}
	else
	{
		fputstring(name, fp);
	}
}

static void initdumpdep(void)
{
	dcount = 0;
	ndeps = 0;
}

static void cleandumpdep(void)
{
int i;
	for(i=0;i<ndeps;i++)
	{
		free(deps[i].name);
	}
}


//int indent=1;
static void dep_do_dump(FILE *fp, int i, char tabulate)
// dump all dependencies of source file "sources[i]", including
// the dependencies of it's dependencies.
// before calling be sure to call initdumpdep()
{
int d;
//int k = indent;
	//while(k-->0) printf(" ");
//printf("dep_do_dump: #%d '%s'\n", i, sources[i].name);
//indent++;
	if (sources[i].fromcache)
	{
		stCacheEntry *c = sources[i].cache;
		while(c)
		{
			dumpdep(c->dependname, fp, tabulate);
			c = c->next;
		}
	}
	else
	{
		for(d=0;d<sources[i].nDepends;d++)
		{
			dumpdep(sources[sources[i].depends[d]].name, fp, tabulate);
			dep_do_dump(fp, sources[i].depends[d], tabulate);
		}
	}
	//indent--;
}
