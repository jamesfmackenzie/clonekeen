#!/bin/sh

cp -r ../../bin/* .
cp -r ../../data/GAMEDATA/KEEN1/* data
cp lib/SDL.dll .
mkdir -p ai
mkdir -p cinematics
mkdir -p editor
mkdir -p scale2x
mkdir -p sdl
mkdir -p bin

if [ -z "$SDLCONFIGBIN" ]; then
    export SDLCONFIGBIN=sdl-config
fi

#NOTE: The following has been tested with an archive of SDL 2.0.1 ready for
#mingw-w64. It seems to work since we don't recompile the libraries for now...
if [ "$1" = "" ]; then
	echo
	echo "Usage:"
	echo "./build_mingw32.sh /path/to/SDL-1.2-mingw"
	echo
	echo "Example:"
	echo "./build_mingw32.sh /d/Development/SDL-1.2.15"
	echo
else
	SDL_PATH=$1
	shift 1
	make BINPREFIX=i686-w64-mingw32- SDLCONFIG="$SDL_PATH/bin/$SDLCONFIGBIN --prefix=$SDL_PATH"
fi