
#include "keen.h"
#include "globals.fdh"

int whodied;  // crappy hack for passing which player died when a level is lost
int editor=0;		// map editor on/off
int last_editor=0;
char fading_to_leave_gameloop;
int highest_objslot;			// the highest object slot in use, +1

char episode_available[4];

uchar background[SCROLLBUF_XSIZE][SCROLLBUF_YSIZE];

// used to pass information when starting a newgame
int newgame_episode;
int newgame_number_of_players = 1;
char custom_path[MAXPATHLEN];

char window_is_fullscreen = 0;

int framebyframe = 0, framestorun = 0;

stString strings[MAX_STRINGS];
int numStrings;

char ScreenIsScrolling;
int gunfiretimer, gunfirefreq;

char loadslot;

stFadeControl fadecontrol;
stMap map;
unsigned int AnimTileInUse[ATILEINUSE_SIZEX][ATILEINUSE_SIZEY];
stTile tiles[MAX_TILES];
unsigned char tiledata[MAX_TILES][16][16];
stSprite sprites[MAX_SPRITES];
stBitmap bitmaps[MAX_BITMAPS];
stObject objects[MAX_OBJECTS];
char font[MAX_FONT][8][8];
char font_clear[MAX_FONT][8][8];
stAnimTile animtiles[MAX_ANIMTILES];
stPlayer player[MAX_PLAYERS];
int options[NUM_OPTIONS];
unsigned char *scrollbuf = NULL;
unsigned char *blitbuf = NULL;
char keytable[KEYTABLE_SIZE];
char last_keytable[KEYTABLE_SIZE];
unsigned int objdefsprites[LAST_OBJ_TYPE+1];
stLevelControl levelcontrol;
stOverlays overlay;

stDemo demo;

uchar primaryplayer;
uchar numplayers;

char crashflag;
int NessieObjectHandle;
char caitlin_isnt_awesome = 0;
