
char QSInit(int numkeys);
void QSClose(void);
void *QSLookup(uchar *text, uchar key, void **answer2);
char QSAddString(char *text, uchar key, void *answer, void *answer2);
void QSDelete(unsigned char *text, uchar key);
char QSAddStringInt(char *text, uchar key, uint answer, uint answer2);
uint QSLookupInt(uchar *text, uchar key, uint*answer2);
