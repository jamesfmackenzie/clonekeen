


#define FUNCDEFS_HEADER		"//automatically generated by Makegen\n"
// extension of ".ml" makelist files. files appearing in the makelist
// with this extension are included into the makelist as a sub-makelist.
#define ML_EXT				"ml"
// the preprocessor include directive used by source files.
#define PREPROCESSOR_CHAR	'#'
#define INCLUDE_DIRECTIVE	"include "
// the quote char that surrounds the filename of local include files.
// (eg #include "myfile.h" is processed but #include <stdio.h> is ignored)
#define LOCALQUOTE			'\"'
// makegen skips over source lines that contain this string. this lets you
// tell it that dependencies to certain files don't count, even if they appear
// to exist.
#define IGNORESTR			"MAKEGEN:IGNORE"

// name of file to store dependency caches in
#define CACHEFILEEXT		".cch"
#define CACHEFILEVER		1


#define MAKELIST_DEFAULT	"makelist.ml"
#define MAKEFILE_DEFAULT	"Makefile"

// maximum number of source files in a project
#define MAX_FILES		400
// longest possible line that could be encountered in the source files
#define MAXLEN			2000
// longest file name the OS supports (equiv to MAX_PATH on Windows)
#define MAXFNAMELEN		260
// max # of functions to expect per source file (dynamically allocated, so can be quite large)
#define MAX_FUNCTIONS	8000

#define IS_WHITESPACE(ch)	( ch==' ' || ch==9 )
#define CR					13
#define LF					10

#if MAXLEN < MAXFNAMELEN
	#error "It's probably a good idea that MAXLEN is bigger than MAXFNAMELEN; this is what I assumed in the code."
#endif

