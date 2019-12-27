
#include "filetime.h"

char LoadCacheHeader(void);
char LoadSourceFromCache(int cno, int s);
void CacheRemoveSublevel(int index);
void CacheAddSubfilesToSummary(void);
int CacheSumSubStats(int *stats);
void CacheFreeSubStats(void);
void GetCacheFileName(void);
char gencache(void);

// debug only
void CacheDumpSublevel(void);
