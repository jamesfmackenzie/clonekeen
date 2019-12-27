// this module implements an algorithm for quickly determining if
// a string is in a list of other strings, and associating a number
// to each string, which can be looked up with minimal computation.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

#define MAX_BRANCHES		128		// set 256 if you want full ASCII set
typedef struct SNode
{
	void *answer;
	void *answer2;
	struct SNode *branch[MAX_BRANCHES];
} SNode;

SNode basenode;


void initnode(SNode *node)
{
	memset(node->branch, 0, sizeof(node->branch));
	node->answer = node->answer2 = (void *)-1;
}

char QSAddString(char *text, uchar key, void *answer, void *answer2)
{
SNode *node;
int i;
unsigned char b;
	
	// enter the key...
	node = basenode.branch[key];
	
	// add a branch for each letter in the text...
	for(i=0;i<strlen(text);i++)
	{
		b = text[i] & 0x7f;
		if (!node->branch[b])
		{
			//printf("branching off '%c'\n", b);
			node->branch[b] = malloc(sizeof(SNode));
			if (!node->branch[b])
			{
				printf("QSAddString: out of memory branching off '%c'\n", b);
				return 1;
			}
			initnode(node->branch[b]);
			node = node->branch[b];
		}
		else
		{
			//printf("branch '%c' previously existing...\n", b);
			node = node->branch[b];
		}
	}
	// add the answer to the last branch we ended up at
	/*if (node->answer!=-1)
	{
		printf("QSAddString: WARNING: overwriting previous node pairing '%s' = %u with new answer %u\n", text, node->answer, answer);
	}*/
	node->answer = answer;
	node->answer2 = answer2;
	
	return 0;
}

char QSAddStringInt(char *text, uchar key, uint answer, uint answer2)
{
	return QSAddString(text, key, (void *)answer, (void *)answer2);
}

void *QSLookup(uchar *text, uchar key, void **answer2)
{
SNode *curnode;
int i;
uint searchlen = strlen(text);

	// set the key...
	curnode = basenode.branch[key];	

	// go jump jump jump hoppity hop-- follow the tree all the way
	for(i=0;i<searchlen;i++)
	{
		if ((curnode = curnode->branch[text[i]&0x7f])==NULL)
		{
			return (void *)-1;
		}
	}

	if (curnode->answer != (void *)-1)
		*answer2 = curnode->answer2;

	return curnode->answer;
}

uint QSLookupInt(uchar *text, uchar key, uint *answer2)
{
void *temp_answer, *temp_answer2;
	temp_answer = QSLookup(text, key, &temp_answer2);
	if (answer2) *answer2 = (uint)temp_answer2;
	return (uint)temp_answer;
}

// remove an answer from the database
void QSDelete(unsigned char *text, uchar key)
{
	QSAddString(text, key, (void *)-1, 0);
}


// initilize the system and create numkeys base keys
char QSInit(int numkeys)
{
int i;

	initnode(&basenode);

	// initilize all keys of basenode
	for(i=0;i<numkeys;i++)
	{
		basenode.branch[i] = malloc(sizeof(SNode));
		if (!basenode.branch[i])
		{
			printf("QSInit: out of memory creating key %d\n", i);
			return 1;
		}
		initnode(basenode.branch[i]);
	}
	
	return 0;
}


static void CloseAllBranches(SNode *node)
{
int i;
	for(i=0;i<MAX_BRANCHES;i++)
	{
		if (node->branch[i])
		{
			CloseAllBranches(node->branch[i]);
		}
	}
	if (node != &basenode) free(node);
}


void QSClose(void)
{
	CloseAllBranches(&basenode);
}
