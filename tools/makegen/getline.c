

int mgetline(FILE *fp, uchar *line, int maxlen)
// read a line from file 'fp', trim whitespace on both sides,
// and remove comments.
// returns the length of the fully-processed line.
{
char ch = -1;
int i = 0;
char in_cmt = 0;
char inquote = 0;
uchar lastch;

	#define READ_TO_EOL	{	\
		char k;				\
		do { k = fgetc(fp); } while(k!=LF && k!=-1);	\
	}
	
	
readnextline: ;
	// do ltrim
	do
	{
		ch = fgetc(fp);
		if (!IS_WHITESPACE(ch)) break;
		
	} while(!feof(fp));
	
	// read in the line
	for(;;)
	{
		if (ch==-1)		// end of file
		{
			line[i] = 0;
			if (in_cmt)
			{
				printf("warning: '/*' without '*/': '%s'\n", line);
			}
			break;
		}
		
		if (!in_cmt)
		{
			// handle special chars...
			if (!inquote)
			{
				if (ch==34)
				{
					inquote = 1;
				}
				else if (ch=='/')
				{
					if (i && line[i-1]=='/')		// C99 '//' cmt
					{	// drop rest of line
						line[--i] = 0;
						READ_TO_EOL;
						break;
					}
				}
				else if (ch=='*')			// multiline '/*' cmt pair
				{
					if (i && line[i-1]=='/')
					{
						line[--i] = 0;		// erase the '/'
						in_cmt = 1;
						lastch = -1;
						goto nextchar;
					}
				}
			}
			else	// inside a string quote
			{
				if (ch==34) inquote = 0;
			}
			
			// add text to buffer...
			if (ch != CR)	// ignore CR, we only care about LF
			{
				if (ch==LF)
				{	// reached end of line
					if (line[i-1]=='\\')		// concat C line extensions
					{
						--i;		// remove the '\'
						// read next line
						goto readnextline;
					}
					else
					{
						line[i] = 0;
						break;
					}
				}
				else
				{
					if (i < maxlen)
					{
						line[i++] = ch;
					}
					else
					{
						line[i-1] = 0;
						printf("mgetline: warning: max length of %d exceeded on line:\n", maxlen);
						printf("'%s'\n", line);
						// drop chars to end of line and abort
						READ_TO_EOL;
						return maxlen-1;
					}
				}
			}
		}
		else			// inside /*  */ comments
		{
			if (lastch=='*' && ch=='/')		// '*/' cmt pair
			{
				in_cmt = 0;
				goto readnextline;
			}
			else lastch = ch;
		}
		
nextchar: ;
		ch = fgetc(fp);
	}	// end of main read loop

	// rtrim whitespace
	while(i > 0)
	{
		--i;
		if (!IS_WHITESPACE(line[i]))
		{
			line[++i] = 0;
			
			return i;
		}
	}
	// if we reach here, then whole line was whitespace
	// normally we'd set line[0] = 0 but we don't have to
	// because we know it was already ltrim'd.
	return 0;
}
