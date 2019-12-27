
char *strippath(char *in);
void splitext(char *filein, char *fileout, char *ext);
void validate_ext(char *V);

char *RemoveQuotes(char *str);
char *StringStartsWith(char *haystack, char *needle);
void fgetline(FILE *fp, char *str, int maxlen);
uint LTrimAt(uchar *line, uchar atwhat, uint linelen);
int RTrim(char *line, int linelen);
uint RTrimAt(uchar *line, uchar ch, uint linelen);

int fgeti(FILE *fp);
void fputi(uint word, FILE *fp);
unsigned int fgetl(FILE *fp);
void fputl(unsigned int word, FILE *fp);
void freadstring(FILE *fp, char *buf, int max);
void fputstring(char *buf, FILE *fp);
