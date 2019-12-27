CFLAGS=-c -g -Wall
LFLAGS=
HFILES=Makefile makegen.h types.h constants.h token.h string.h quicksearch.h fdh.h cache.h summary.h filetime.h dependency.h header.h getline.c

all: makegen

clean:
	rm -f *.o
	rm -f makegen

makegen: makegen.o fdh.o quicksearch.o string.o token.o summary.o cache.o filetime.o dependency.o header.o
	  gcc -o makegen \
          makegen.o fdh.o quicksearch.o string.o token.o summary.o cache.o filetime.o dependency.o header.o \
          $(LFLAGS)

makegen.o:   makegen.c $(HFILES)
	gcc $(CFLAGS) makegen.c -o makegen.o

quicksearch.o:  quicksearch.c $(HFILES)
	gcc $(CFLAGS) quicksearch.c -o quicksearch.o

string.o:  string.c $(HFILES)
	gcc $(CFLAGS) string.c -o string.o

token.o:  token.c $(HFILES)
	gcc $(CFLAGS) token.c -o token.o

fdh.o:  fdh.c $(HFILES)
	gcc $(CFLAGS) fdh.c -o fdh.o

cache.o:	cache.c $(HFILES)
	gcc $(CFLAGS) cache.c -o cache.o

filetime.o:	filetime.c $(HFILES)
	gcc $(CFLAGS) filetime.c -o filetime.o

summary.o:	summary.c $(HFILES)
	gcc $(CFLAGS) summary.c -o summary.o

dependency.o:	dependency.c $(HFILES)
	gcc $(CFLAGS) dependency.c -o dependency.o

header.o:	header.c $(HFILES)
	gcc $(CFLAGS) header.c -o header.o
