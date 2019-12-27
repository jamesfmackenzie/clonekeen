
#include <stdio.h>
#include <strings.h>

int fix_file(char *prefix);
void copyfile(const char *from, const char *to);


int main(int argc, char **argv)
{
int i;
int cr_rem;

	if (argc <= 1)
	{
		printf("usage: crlf [file1] [file2] ...\n");
		return;
	}
	
	for(i=1;i<argc;i++)
	{
		cr_rem = fix_file(argv[i]);
		if (cr_rem == -1) return 1;
		
		printf("%s.c: %d CR's removed\n", argv[i], cr_rem);
	}
	
	return 0;
}


int fix_file(char *input_file)
{
static const char *output_file = "crlf.tmp";
FILE *fpi, *fpo;
char ch;
int cr_rem = 0;

	fpi = fopen(input_file, "rb");
	if (!fpi)
	{
		printf("failed to open input file %s\n", input_file);
		return -1;
	}
	
	fpo = fopen(output_file, "wb");
	if (!fpo)
	{
		printf("failed to open output file %s\n", output_file);
		fclose(fpi);
		return -1;
	}
	
	while(!feof(fpi))
	{
		char ch = fgetc(fpi);
		if (ch == -1) break;
		
		if (ch != '\r')
		{
			fputc(ch, fpo);
		}
		else
		{
			cr_rem++;
		}
	}
	
	fclose(fpi);
	fclose(fpo);
	copyfile(output_file, input_file);
	remove(output_file);
	return cr_rem;
}

void copyfile(const char *from, const char *to)
{
FILE *fpi, *fpo;

	fpi = fopen(from, "rb");
	if (!fpi)
	{
		printf("copyfile: could not open source '%s'", from);
		return;
	}
	
	fpo = fopen(to, "wb");
	if (!fpo)
	{
		printf("copyfile: could not open destination '%s'", to);
		return;
	}
	
	for(;;)
	{
		char ch = fgetc(fpi);
		if (ch == -1) break;
		
		fputc(ch, fpo);
	}
	
	fclose(fpi);
	fclose(fpo);
}

