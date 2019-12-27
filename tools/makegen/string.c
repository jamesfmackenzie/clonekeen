

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "types.h"
#include "string.h"
#include "constants.h"


char *strippath(char *in)
// given a file containing a path name, returns a pointer
// to only the file name.
{
int i;
	for(i=strlen(in)-1;i>=0;i--)
	{
		if (in[i]=='/' || in[i]=='\\')
		{
			return &in[i+1];
		}
	}
	return in;
}

/*void splitext(char *filename, char *file, char *ext)
// split filename into 'file' and 'ext'
// 'autoexec.bat' becomes 'autoexec' and 'bat'
{
char *ptr;

	strcpy(file, filename);
	
	ptr = strrchr(file, '.');
	if (ptr)
	{
		*ptr++ = 0;
		if (ext) strcpy(ext, ptr);
	}
	else
	{
		if (ext) ext[0] = 0;
	}
}*/

void validate_ext(char *V)
// V points to a file extension.
// Adds the dot to the extension if it's missing.
{
int i;
	if (V[0] != '.')
	{
		for(i=strlen(V);i>=0;i--)
		{
			V[i+1] = V[i];
		}
		V[0] = '.';
	}
}


char *RemoveQuotes(char *str)
// trims " " quotes from str, and returns a pointer to
// the quoteless string. The original string gets slightly mangled.
{
int l;
	if (str[0]==34)
	{
		str++;
		l = strlen(str)-1;
		if (str[l]==34) str[l] = 0;
		else
		{
			printf("RemoveQuotes: mismatched quotes:\n'%s'\n", str);
			return NULL;
		}
	}
	return str;
}


char *StringStartsWith(char *haystack, char *needle)
// determines if string haystack starts with string needle.
// if so, returns a pointer to the character after the last char scanned.
// else, returns NULL.
{
int i;

	for(i=0;needle[i];i++)
	{
		if (haystack[i] != needle[i])
		{
			return NULL;
		}
	}
	return &haystack[i];
}


// read data from a file until CR
void fgetline(FILE *fp, char *str, int maxlen)
{
int k;
	str[0] = 0;
	fgets(str, maxlen - 1, fp);
	
	// trim the CR/LF that fgets returns
	for(k=strlen(str)-1;k>=0;k--)
	{
		if (str[k] != 13 && str[k] != 10) break;
		str[k] = 0;
	}
}


uint LTrimAt(uchar *line, uchar atwhat, uint linelen)
{
int i;
	for(i=0;i<linelen;i++)
	{
		if (line[i] == atwhat)
		{
			strcpy(line, &line[i+1]);
			return strlen(line);
		}
	}
	return linelen;
}

int RTrim(char *line, int linelen)
// trim whitespace from the end of line line and return
// the new length of the line.
{
int i;
	for(i=linelen-1;i>=0;i--)
	{
		if (!IS_WHITESPACE(line[i]))
		{
			line[++i] = 0;
			return i;
		}
	}
	// no whitespace was removed
	return linelen;
}


uint RTrimAt(uchar *line, uchar ch, uint linelen)
{
int i;
	for(i=linelen-1;i>=0;i--)
	{
		if (line[i]==ch) { line[i] = 0; return i; }
	}
	return linelen;
}


int fgeti(FILE *fp)
{
int lsb, msb;
	msb = fgetc(fp);
	lsb = fgetc(fp);
	return (msb << 8) | lsb;
}

void fputi(uint word, FILE *fp)
{
	fputc(word>>8, fp);
	fputc(word&0xff, fp);
}

unsigned int fgetl(FILE *fp)
{
unsigned int temp1, temp2, temp3, temp4;
  temp1 = fgetc(fp);
  temp2 = fgetc(fp);
  temp3 = fgetc(fp);
  temp4 = fgetc(fp);
  return (temp1<<24) | (temp2<<16) | (temp3<<8) | temp4;
}

void fputl(unsigned int word, FILE *fp)
{
unsigned int a,b,c,d;
	a=b=c=d = word;
	a &= 0xFF000000; a >>= 24;
	b &= 0x00FF0000; b >>= 16;
	c &= 0x0000FF00; c >>= 8;
	d &= 0x000000FF;
	fputc(a, fp);
	fputc(b, fp);
	fputc(c, fp);
	fputc(d, fp);
}

// read a string from a file until a space is encountered
void freadstring(FILE *fp, char *buf, int max)
{
int i;
	if (buf != NULL)
	{
		for(i=0;i<max;i++)
		{
			buf[i] = fgetc(fp);
			if (!buf[i]) break;
		}
	}
	else
	{
		do
		{
			i = fgetc(fp);
		} while(i && i != -1);
	}
}

// write a string to a file and null-terminate it
void fputstring(char *buf, FILE *fp)
{
	if (buf[0]) fprintf(fp, "%s", buf);
	fputc(0, fp);
}

