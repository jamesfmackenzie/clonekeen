
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>

char getfiletime(char *filename, unsigned int *msb, unsigned int *lsb)
{
struct stat fileinfo;

	printf("asked to 'stat': %s\n", filename);
	
	if (stat(filename, &fileinfo))
	{
		printf("stat failed: %s\n", filename);
		return 1;
	}
	
//	#if (sizeof(time_t) <= sizeof(unsigned int))
		*msb = 0;
		*lsb = fileinfo.st_mtime;
//	#else
//		#error "getfiletime fixme: time_t > 32 bits";
//	#endif
	
	return 0;
}

/*
#include <windows.h>
#include <stdio.h>
#include "filetime.h"

// function for retrieving a file's last-modified timestamp.
// since this is platform-specific it's split off into a seperate module.

// retrieve fname's last-modified stamp and put the result in msb
// and lsb. it does not matter what format this timestamp is in,
// just that it will change when the file is updated.
// returns nonzero on failure.
char getfiletime(char *fname, unsigned int *msb, unsigned int *lsb)
{
WIN32_FILE_ATTRIBUTE_DATA fad;

	if (!GetFileAttributesEx(fname, GetFileExInfoStandard, &fad))
	{
		printf("getfiletime: failed to stat file %s\n", fname);
		return 1;
	}
	
	*lsb = fad.ftLastWriteTime.dwLowDateTime;
	*msb = fad.ftLastWriteTime.dwHighDateTime;
	return 0;
}
*/
