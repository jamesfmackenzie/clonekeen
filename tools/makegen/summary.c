
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "makegen.h"

typedef struct stSummary
{
	char text[MAXLEN];
	int len;
	struct stSummary *next;
} stSummary;

stSummary *first, *last;

stSummary *line_with_most_functions;
uchar mostfuncstr[MAXLEN];
int highestfunccount;

int maxlen;

extern int nFilesParsed, nLinesParsed;


void AddFileToSummary(char *name, char istoplevel, int *stats)
{
stSummary *line;


	if (!(line = malloc(sizeof(stSummary))))
	{
		printf("AddFileToSummary: out of memory adding '%s'\n", name);
		return;
	}
	
	if (options.no_fdh)
	{
		sprintf(line->text, "%s%s", istoplevel?"":"+", name);
	}
	else
	{
		sprintf(line->text, "%s%s(%d)", istoplevel?"":"+", \
					name, stats[STAT_NUM_FUNCS]);
				
		if (stats[STAT_STATIC_FUNCS] > 0)
		{
			sprintf(line->text, "%s(%d)", line->text, stats[STAT_STATIC_FUNCS]);
		}
	}
	
	line->len = strlen(line->text);
	if (line->len > maxlen) maxlen = line->len;
	
	if (stats[STAT_NUM_FUNCS] >= highestfunccount)
	{
		line_with_most_functions = line;
		highestfunccount = stats[STAT_NUM_FUNCS];
	}
	
	if (last) last->next = line; else first = line;
	line->next = NULL;
	last = line;
}


void ShowSummary(void)
// displays a summary-like table listing all source files
// in the project and some stats for each.
{
int i;
char nl;
uchar spacebuf[MAXFNAMELEN], x;
stSummary *entry, *next;

	maxlen = 0;
	first = last = NULL;
	highestfunccount = 1;	// don't show if no functions found at all
	line_with_most_functions = NULL;
	
	for(i=0;i<nsources;i++)
	{
		if (!sources[i].is_hfile)
		{
			AddFileToSummary(sources[i].name, (sources[i].nParents==0), &sources[i].stats[0]);
		}
	}
	
	// add files which aren't in the sources list because they're
	// only included by files which were cache hits.
	//AddFileToSummary("--cache start--", 0, &sources[0].stats[0]);
	CacheAddSubfilesToSummary();

	
	if (line_with_most_functions)
		sprintf(mostfuncstr, "  [[ %s ]]", line_with_most_functions->text);
	else
		mostfuncstr[0] = 0;
	
	
	printf("Project source files:\n");
	
	// print out a "ls"-style listing of all the source files
	maxlen += 2;	// min 2 spaces after each
	x = 0; nl = 0;
	spacebuf[maxlen] = 0;
	memset(spacebuf, ' ', maxlen);
	
	entry = first;
	while(entry)
	{
		next = entry->next;
		
		fputs(entry->text, stdout);
		fputs(&spacebuf[entry->len], stdout);
		
		x += maxlen;
		if (x > 79 - maxlen)
		{
			fputs("\n", stdout);
			x = 0;
			nl = 1;
		}
		else nl = 0;
		
		free(entry);
		entry = next;
	}
	
	if (!nl) printf("\n\n"); else printf("\n");
}


void ShowStatLine(void)
{
int i, j;
int stats[NUM_STATS];
int nTotalFiles;
char nlinestr[MAXLEN];

	if (options.nosummary) mostfuncstr[0] = 0;
	
	memset(stats, 0, sizeof(stats));
	nTotalFiles = nsources + CacheSumSubStats(&stats[0]);
	
	for(i=0;i<nsources;i++)
	{
		for(j=0;j<NUM_STATS;j++)
		{
			stats[j] += sources[i].stats[j];
		}
	}

	if (stats[STAT_LINES] != nLinesParsed)
	{
		sprintf(nlinestr, ", %u/%u lines\n", stats[STAT_LINES], nLinesParsed);
	}
	else
	{
		sprintf(nlinestr, ", %u lines\n", nLinesParsed);
	}
	
	if (options.no_fdh)
	{
		printf("makegen: %s done (%d/%dfile)%s\n", \
				mlname, nFilesParsed, nTotalFiles, nlinestr);
	}
	else
	{
		printf("makegen: %s done (%d/%dfile; %d/%dfunc)%s%s", \
				mlname, nFilesParsed, nTotalFiles,
				stats[STAT_GLOBAL_FUNCS], stats[STAT_NUM_FUNCS],
				mostfuncstr, nlinestr);
	}
}


