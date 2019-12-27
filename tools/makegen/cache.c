
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>			// so we can use tolower()

#include "makegen.h"

typedef struct
{
	char name[MAXFNAMELEN];				// name of the source file
	unsigned int tstampl, tstamph;		// last-modified timestamp of version in cache
	unsigned int offset;				// offset of cached data in cache file
} stCacheHeader;

stCacheHeader cachehdr[MAX_FILES];

typedef struct stStatTableEntry
{
	char name[MAXFNAMELEN];
	int stats[NUM_STATS];
	struct stStatTableEntry *next, *prev;
} stStatTableEntry;

stStatTableEntry *stattbl_firstentry, *stattbl_lastentry;

char CacheFilename[MAXFNAMELEN];
FILE *cfp = NULL;						// cache file handle

static char load_offs_table(void);
static char load_stats_table(void);
static void FreeCacheList(stCacheEntry *first);


void GetCacheFileName(void)
{
char *extptr;
	// generate name of cache file
	strcpy(CacheFilename, mlname);
	if ((extptr = strrchr(CacheFilename, '.'))) *extptr = 0;
	strcat(CacheFilename, CACHEFILEEXT);
}

char LoadCacheHeader(void)
{
	GetCacheFileName();
	
	cfp = fopen(CacheFilename, "rb");
	if (!cfp)
	{
		printf(": no cache file, will create\n");
		return 0;
	}
	
	if (fgetc(cfp) != CACHEFILEVER)
	{
		printf(": wrong version cache file, will recreate\n");
		fclose(cfp); cfp = NULL;
		return 0;
	}
	
	// read in the offset table. this shows us what's available
	// in the cache and where to find it's info in the cachefile.
	if (load_offs_table()) return 1;
	
	// now load the statistics area, which contains all non- top-level
	// files and their associated statistics
	if (load_stats_table()) return 1;
	
	return 0;
}


static char load_offs_table(void)
// loads the offset table. this shows us what's available
// in the cache and where to find it's info in the cachefile.
{
int i;
unsigned int curtimelow, curtimehigh;
char misses = 0;

	i = 0;
	while(1)
	{
		if (feof(cfp))
		{
			printf("loadcache: unexpected end of file\n");
			fclose(cfp); cfp = NULL;
			return 0;
		}
		
		freadstring(cfp, cachehdr[i].name, sizeof(cachehdr[i].name));
		if (!cachehdr[i].name[0]) break;
		
		//printf("loading info on '%s' into cache header table\n", cachehdr[i].name);
		
		cachehdr[i].tstampl = fgetl(cfp);
		cachehdr[i].tstamph = fgetl(cfp);
		cachehdr[i].offset = fgetl(cfp);
		//printf("tstamp low %08x tstamp high %08x   offset %04x\n", cachehdr[i].tstampl,cachehdr[i].tstamph,cachehdr[i].offset);
		
		// if the file has not been modified since the entry
		// was last put in the cache, add it to the list of
		// available cached files
		if (!getfiletime(cachehdr[i].name, &curtimelow, &curtimehigh))
		{
			if (cachehdr[i].tstampl==curtimelow && cachehdr[i].tstamph==curtimehigh)
			{
				QSAddStringInt(cachehdr[i].name, QSKEY_CACHE, i, 0);
				i++;
			}
			else
			{
				if (options.verbose) printf("%s has been modified; excluding from cache\n", cachehdr[i].name);
				misses++;
			}
		}
		else
		{
			printf(": unable to open %s; excluding from cache\n", cachehdr[i].name);
			misses++;
		}
	}
	if (options.verbose) printf("cache: hits:%d  misses:%d\n", i, misses);
	return 0;
}



static char load_stats_table(void)
// now load the statistics table, which contains all non- top-level
// files and their associated statistics
{
int i;
char ch;
stStatTableEntry *entry;

	stattbl_firstentry = stattbl_lastentry = NULL;

	if (options.verbose) printf("loading statistics table from cache: ");	
	while(1)
	{
		ch = fgetc(cfp);
		if (!ch)	// end of list
		{
			break;
		}
		
		entry = malloc(sizeof(stStatTableEntry));
		if (!entry)
		{
			printf("\nloadcacheheader: out of memory loading stat table!\n");
			return 1;
		}
		
		entry->name[0] = ch;
		freadstring(cfp, &entry->name[1], sizeof(entry->name)-1);
		//printf("'%s'\n", entry->name);
		
		for(i=0;i<NUM_STATS;i++)
		{
			entry->stats[i] = fgetl(cfp);
		}

		QSAddString(entry->name, QSKEY_CACHE_SUB, (void *)0xaa, entry);
		

		if (stattbl_lastentry)
			stattbl_lastentry->next = entry;
		else
			stattbl_firstentry = entry;
		
		entry->next = NULL;
		entry->prev = stattbl_lastentry;
		stattbl_lastentry = entry;
	}
	
	if (options.verbose) printf("done.\n");
	return 0;
}


#ifdef DEBUG
void CacheDumpSublevel(void)
{
stStatTableEntry *entry = stattbl_firstentry;
	printf("------------ sublevel dump: ------------\n");
	while(entry)
	{
		printf(" '%s'\n", entry->name);
		entry = entry->next;
	}
	printf("----------------- end ------------------\n");
}
#endif


// remove the given source no from the list of sub-level files which
// were not processed because they were only included by a cached file.
void CacheRemoveSublevel(int index)
{
stStatTableEntry *entry;
void *pointer;
int result;

	//printf("CacheRemoveSublevel: %s\n", sources[index].name);
	result = (int)QSLookup(sources[index].name, QSKEY_CACHE_SUB, &pointer);
	if (result != -1)
	{	// file is currently in the list
		//printf("located at address %08x result %02x\n", pointer, result);
		entry = (stStatTableEntry *)pointer;
		//printf("CacheRemoveSublevel: removing: %s\n", sources[index].name);
		
		if (entry->prev) entry->prev->next = entry->next;
		if (entry->next) entry->next->prev = entry->prev;
		if (entry==stattbl_firstentry) stattbl_firstentry = entry->next;
		free(entry);
		QSDelete(sources[index].name, QSKEY_CACHE_SUB);
	}
}


// add the stats of all files left in the sub-level list to stats array.
// returns the number of files that were added.
int CacheSumSubStats(int *stats)
{
stStatTableEntry *entry;
int j;
int count = 0;

	entry = stattbl_firstentry;
	while(entry)
	{
		for(j=0;j<NUM_STATS;j++)
		{
			stats[j] += entry->stats[j];
		}
		
		count++;
		entry = entry->next;
	}
	
	return count;
}


void CacheAddSubfilesToSummary(void)
{
stStatTableEntry *entry;
char *ext;

	entry = stattbl_firstentry;
	while(entry)
	{
		//printf("CacheAddSubfilesToSummary: '%s'\n", entry->name);
		// don't include ".h" files
		ext = strrchr(entry->name, '.');
		if (ext)
		{
			ext++;
			if (!strcmp(ext, h_ext)) goto skip;
		}
		
		// no files in the list are top-level so we always pass 0
		AddFileToSummary(entry->name, 0, &entry->stats[0]);
		
skip: ;
		entry = entry->next;
	}
}


void CacheFreeSubStats(void)
{
stStatTableEntry *entry, *next;

	//printf("CacheFreeSubStats: freeing substats table\n");
	
	entry = stattbl_firstentry;
	while(entry)
	{
		next = entry->next;
		free(entry);
		entry = next;
	}
}


// tries to loads cache handle cno into sources slot s
// returns nonzero on failure.
char LoadSourceFromCache(int cno, int s)
{
stCacheEntry *entry, *last;
uchar ch;
uchar func[MAXLEN];

	//printf("LoadCache: load cache entry %d (%s) -> sources slot %d\n", cno, cachehdr[cno].name, s);
	if (!cfp) return 1;					// ensure cache file is open

	// seek to the position in the cache file where
	// info on this file is stored
	fseek(cfp, cachehdr[cno].offset, SEEK_SET);
	
	// read statistics
	sources[s].stats[STAT_LINES] = fgeti(cfp);
	sources[s].nDepends = fgeti(cfp);
	//printf("lines = %d depends = %d\n", sources[s].stats[STAT_LINES],sources[s].nDepends);
	
	// now load all the dependencies from cache
	//printf("LoadCache: loading dependencies for '%s' from cache.\n", sources[s].name);
	sources[s].cache = NULL;
	last = NULL;
	while(1)
	{
		ch = fgetc(cfp);
		if (!ch)	// end of list
		{
			break;
		}
		
		entry = malloc(sizeof(stCacheEntry));
		if (!entry)
		{
			printf("LoadCache: out of memory!\n");
			FreeCacheList(sources[s].cache);
			return 1;
		}
		
		entry->dependname[0] = ch;
		freadstring(cfp, &entry->dependname[1], sizeof(entry->dependname)-1);
		
		if (last) last->next = entry; else sources[s].cache = entry;
		entry->next = NULL;
		last = entry;
	}
	
	//printf("LoadCache: loading functions for '%s' from cache.\n", sources[s].name);
	// load functions declared by this module
	sources[s].stats[STAT_NUM_FUNCS] = 0;
	sources[s].stats[STAT_STATIC_FUNCS] = 0;
	sources[s].stats[STAT_GLOBAL_FUNCS] = 0;
	while(1)
	{
		freadstring(cfp, func, sizeof(func));
		if (!func[0]) break;
		
		addfunction(s, func);
	}

	// load functions called by this module
	while(1)
	{
		freadstring(cfp, func, sizeof(func));
		if (!func[0]) break;
		
		AddReferencedFunction(s, func);
	}
	
	sources[s].fromcache = 1;
	return 0;
}

static void FreeCacheList(stCacheEntry *first)
{

}


// generate a cache file which next time can be used to look up
// dependencies on files which have not been modified.
char gencache(void)
{
FILE *fp;
int i, j;
int tablepos[MAX_FILES], offs[MAX_FILES];
stStatTableEntry *subentry;
stFuncReference *fr;

	fp = fopen(CacheFilename, "wb");
	if (!fp)
	{
		printf("unable to open %s\n", CacheFilename);
		return 1;
	}
	
	if (options.verbose)
	{
		printf("writing %s: ", CacheFilename);
		fflush(stdout);
	}

	fputc(CACHEFILEVER, fp);

	// write out a dummy template of the offset table
	//printf(" ** gencache: creating dummy template:\n");
	for(i=0;i<nsources;i++)
	{
		if (!sources[i].nParents)
		{
			unsigned int tlow, thigh;
			if (!getfiletime(sources[i].name, &tlow, &thigh))
			{
				fputstring(sources[i].name, fp);
				
				fputl(tlow, fp);
				fputl(thigh, fp);
				
				tablepos[i] = ftell(fp);
				fputl(0, fp);
			}
		}
	}
	fputc(0, fp);


	// dump all non- top-level files and their stats (line count etc)
	// this is needed for correct statistics display with cached files
	// as these files may be included by files in cache
	//printf(" ** gencache: dumping statistics table:\n");

	// dump stats for everything that was re-parsed //
	for(i=0;i<nsources;i++)
	{
		if (sources[i].nParents > 0)
		{
			fputstring(sources[i].name, fp);
			for(j=0;j<NUM_STATS;j++)
			{
				fputl(sources[i].stats[j], fp);
			}
		}
	}
	// dump stats on everything that was loaded from cache //
	subentry = stattbl_firstentry;
	while(subentry)
	{
		fputstring(subentry->name, fp);
		for(j=0;j<NUM_STATS;j++)
		{
			fputl(subentry->stats[j], fp);
		}
		
		subentry = subentry->next;
	}
	// null-terminate the stats table
	fputc(0, fp);


	// now write all the dependencies & function records
	// and remember their offsets
	//printf(" ** gencache: dumping dependency records...\n");
	for(i=0;i<nsources;i++)
	{
		if (!sources[i].nParents)
		{
			offs[i] = ftell(fp);
			
			// include stat information for summary screen
			fputi(sources[i].stats[STAT_LINES], fp);
			
			// note that the value of nDepends is NOT necessarily the
			// number of items in the list, as nDepends only refers
			// to the TOP LEVEL of dependencies--this file could include
			// files which include other files, and those other files
			// would not be included in the count.
			fputi(sources[i].nDepends, fp);
			DumpDependencies(fp, i, 0);
			fputc(0, fp);	// signal end of dep list
			
			// write function prototypes
			//printf("saving functions in '%s'\n", sources[i].name);
			for(j=0;j<sources[i].stats[STAT_NUM_FUNCS];j++)
			{
				fputstring(sources[i].functions[j].prototype, fp);
			}
			fputc(0, fp);	// signal end of func list
			
			// write functions that were used in this file
			fr = sources[i].firstfunc;
			while(fr)
			{
				fputstring(fr->funcname, fp);
				fr = fr->next;
			}
			fputc(0, fp);	// signal end of function-use list
		}
	}

	
	// go back and flesh out the offset table
	//printf(" ** gencache: finishing offset table...\n");
	for(i=0;i<nsources;i++)
	{
		if (!sources[i].nParents)
		{
			fseek(fp, tablepos[i], SEEK_SET);
			fputl(offs[i], fp);
		}
	}
	
	
	if (options.verbose) printf("done.\n");
	fclose(fp);
	return 0;
}

