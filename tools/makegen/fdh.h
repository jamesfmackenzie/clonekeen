
void fdh_init(void);
char is_function_definition(uchar *line, uint linelen);
char addfunction(int index, uchar *line);
char writefdhfiles(void);
void fdh_cleanup(void);

int seek_to_top(int index);

// used by cacher
char AddReferencedFunction(uint index, uchar *funcname);

// shared with cdhmaker
int updatehash(uint curhash, uchar *line);
char doesfdhneedupdate(uchar *fdhfile, unsigned long hash);

