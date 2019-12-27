
#ifndef __MAKEGEN_H
#define __MAKEGEN_H

#include <string.h>
#include "types.h"
#include "constants.h"
#include "token.h"
#include "string.h"
#include "quicksearch.h"
#include "fdh.h"
#include "cache.h"
#include "summary.h"
#include "dependency.h"
#include "header.h"

#define	stricmp		strcasecmp

// return values of addsrcfile()
#define SRC_ERROR				-1
#define SRC_FILE_ALREADY_PARSED	-2
#define SRC_FILE_IGNORED		-3

// stuff for quicksearch module
#define QS_NUM_KEYS			4
#define QSKEY_PROTOTYPE		0	// used by fdh generator
#define QSKEY_SOURCES		1	// used by HaveSourceFile
#define QSKEY_CACHE			2	// used by cache system
#define QSKEY_CACHE_SUB		3	// non-processed dependencies of cached files, used for statistics display

struct
{
	char nosummary;
	char tree;
	char no_fdh;
	char dump_fdh;
	char use_cache, recache;
	char silent, verbose;
	char fimport;
} options;

typedef struct stFuncReference
{
	uchar *funcname;
	struct stFuncReference *next, *prev;
} stFuncReference;


typedef struct stCacheEntry
{
	char dependname[MAXFNAMELEN];
	struct stCacheEntry *next;
} stCacheEntry;


// source statistics
#define NUM_STATS			4
#define STAT_LINES			0
#define STAT_NUM_FUNCS		1
#define STAT_GLOBAL_FUNCS	2
#define STAT_STATIC_FUNCS	3

typedef struct
{
	uchar name[MAXFNAMELEN];		// source file name
	uchar modulename[MAXFNAMELEN];	// filename without extension
	uchar ext[MAXFNAMELEN];			// the file extension

	ml_header_section *hdrsec;		// which header section this file uses
	
	char is_hfile;					// 1 if this file is an include file (not exectuable code)
	
	// if != NULL the file hasn't been modified, and so, it wasn't
	// really processed, it's dependencies were just loaded from cache.
	// if this is so, this is a pointer to the first cached filename.
	stCacheEntry *cache;
	unsigned int stampl, stamph;	// file's last-modified timestamp
	char fromcache;					// 1 if info is from cache
	
	int nDepends;
	int depends[MAX_FILES];			// indexes of all dependencies
	
	// number of files which have this file as a dependency
	int nParents;
	int parents[MAX_FILES];

	int stats[NUM_STATS];
	
	// a list of all functions in the source file
	// (only if the source file is executable--for .h files this is n/a).
	struct
	{
		uchar *name;				// function name
		uchar *prototype;			// function's prototype
		// has to do with preventing duplicate entries of the same
		// function in a single .fdh file
		uint lastrefdby;
	} functions[MAX_FUNCTIONS];
	
	// a list of all functions this source file references, some of them
	// may be crap like atol(), printf() but that's ok, they'll get
	// filtered out when the final fdh is written.
	stFuncReference *firstfunc, *lastfunc;
} stSrcFile;



#include "token_func.h"

extern char curcmdfilename[MAXFNAMELEN];
extern int cmdfileno;

extern uchar makefile[MAXFNAMELEN];
extern uchar mlname[MAXFNAMELEN];
extern uchar h_ext[MAXFNAMELEN];
extern uchar fdh_ext_dot[MAXFNAMELEN];
extern uchar *fdh_ext;

extern stSrcFile sources[MAX_FILES];
extern int nsources;


char detectfunctioncalls(uchar *line, uint linelen, uint fileindex);
uint TrimComment(uchar *line, uint linelen);
uint LTrim(uchar **line, uint linelen);
int RTrim(char *line, int linelen);
uint LTrimAt(uchar *line, uchar atwhat, uint linelen);
uint RTrimAt(uchar *line, uchar atwhat, uint linelen);
char RTrimCR(uchar *line);
int mgetline(FILE *fp, uchar *line, int maxlen);
char *StringStartsWith(char *haystack, char *needle);
void AddDependency(uchar index, uchar dependson);
void CollapsePath(char *path);
void GetPath(char *fname, char *path);
char HaveSourceFile(char *file);
int AddSourceFile(char *name);
void stripext(char *filein, char *fileout, char *ext);
int parsefile(uchar *file, int parent, int recursion);
void ListSrcFiles(void);
void DumpTopLevel(FILE *fp, char cr);
void DumpDepends(FILE *fp, int i);
ml_header *process_makelist(uchar *listfilename);
char genmakefile(uchar *listfilename, uchar *makefilename);
char *RemoveQuotes(char *str);

#endif
