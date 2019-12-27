SDLPATH=/d/Development/SDL-1.2.15
SDLCONFIG=$(SDLPATH)/bin/sdl-config --prefix=$(SDLPATH)

all: keen

keen:  main.o sanity.o game.o gamedo.o \
	 gamepdo.o gamepdo_wm.o editor/editor.o editor/autolight.o console.o \
	 fileio.o maploader.o map.o graphics.o palette.o \
	 fonts.o misc.o misc_ui.o graphicmaker.o ini.o \
	 intro.o menumanager.o menu_options.o menu_keysetup.o menu_savegames.o \
	 menu_custommap.o editor/menu_editor.o customepisode.o savegame.o twirly.o \
	 sgrle.o lprintf.o vgatiles.o latch.o lz.o \
	 message.o cinematics/seqcommon.o cinematics/e1ending.o cinematics/e3ending.o cinematics/blowupworld.o \
	 cinematics/mortimer.o cinematics/TBC.o FinaleScreenLoader.o globals.o ai/yorp.o \
	 ai/garg.o ai/vort.o ai/butler.o ai/tank.o ai/door.o \
	 ai/ray.o ai/icecannon.o ai/teleport.o ai/rope.o ai/walker.o \
	 ai/tankep2.o ai/platform.o ai/platvert.o ai/vortelite.o ai/se.o \
	 ai/baby.o ai/earth.o ai/foob.o ai/ninja.o ai/meep.o \
	 ai/sndwave.o ai/mother.o ai/fireball.o ai/balljack.o ai/nessie.o \
	 ai/autoray.o ai/gotpoints.o sdl/keydrv.o sdl/snddrv.o sdl/timedrv.o \
	 sdl/viddrv.o scale2x/scalebit.o scale2x/scale2x.o scale2x/scale3x.o scale2x/pixel.o \
	 platform.o
	gcc -o keen \
	 main.o sanity.o game.o gamedo.o \
	 gamepdo.o gamepdo_wm.o editor/editor.o editor/autolight.o console.o \
	 fileio.o maploader.o map.o graphics.o palette.o \
	 fonts.o misc.o misc_ui.o graphicmaker.o ini.o \
	 intro.o menumanager.o menu_options.o menu_keysetup.o menu_savegames.o \
	 menu_custommap.o editor/menu_editor.o customepisode.o savegame.o twirly.o \
	 sgrle.o lprintf.o vgatiles.o latch.o lz.o \
	 message.o cinematics/seqcommon.o cinematics/e1ending.o cinematics/e3ending.o cinematics/blowupworld.o \
	 cinematics/mortimer.o cinematics/TBC.o FinaleScreenLoader.o globals.o ai/yorp.o \
	 ai/garg.o ai/vort.o ai/butler.o ai/tank.o ai/door.o \
	 ai/ray.o ai/icecannon.o ai/teleport.o ai/rope.o ai/walker.o \
	 ai/tankep2.o ai/platform.o ai/platvert.o ai/vortelite.o ai/se.o \
	 ai/baby.o ai/earth.o ai/foob.o ai/ninja.o ai/meep.o \
	 ai/sndwave.o ai/mother.o ai/fireball.o ai/balljack.o ai/nessie.o \
	 ai/autoray.o ai/gotpoints.o sdl/keydrv.o sdl/snddrv.o sdl/timedrv.o \
	 sdl/viddrv.o scale2x/scalebit.o scale2x/scale2x.o scale2x/scale3x.o scale2x/pixel.o \
	 platform.o \
	 `$(SDLCONFIG) --libs` -lstdc++

main.o:	../../src/main.c ../../src/main.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/main.c -o main.o

sanity.o:	../../src/sanity.c ../../src/sanity.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/sanity.c -o sanity.o

game.o:	../../src/game.c ../../src/game.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/game.c -o game.o

gamedo.o:	../../src/gamedo.c ../../src/gamedo.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/gamedo.c -o gamedo.o

gamepdo.o:	../../src/gamepdo.c ../../src/gamepdo.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/gamepdo.c -o gamepdo.o

gamepdo_wm.o:	../../src/gamepdo_wm.c ../../src/gamepdo_wm.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/gamepdo_wm.c -o gamepdo_wm.o

editor/editor.o:	../../src/editor/editor.c ../../src/editor/editor.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/editor/buttons.c ../../src/editor/ghosting.c \
		../../src/editor/autoblock.c
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/editor/editor.c -o editor/editor.o

editor/autolight.o:	../../src/editor/autolight.c ../../src/editor/autolight.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/editor/autolight.c -o editor/autolight.o

console.o:	../../src/console.c ../../src/console.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/console.c -o console.o

fileio.o:	../../src/fileio.c ../../src/fileio.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/fileio.c -o fileio.o

maploader.o:	../../src/maploader.c ../../src/maploader.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/maploader.c -o maploader.o

map.o:	../../src/map.c ../../src/map.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/map.c -o map.o

graphics.o:	../../src/graphics.c ../../src/graphics.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/graphics.c -o graphics.o

palette.o:	../../src/palette.c ../../src/palette.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/palette.c -o palette.o

fonts.o:	../../src/fonts.c ../../src/fonts.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/fonts.c -o fonts.o

misc.o:	../../src/misc.c ../../src/misc.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/misc.c -o misc.o

misc_ui.o:	../../src/misc_ui.c ../../src/misc_ui.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/misc_ui.c -o misc_ui.o

graphicmaker.o:	../../src/graphicmaker.c ../../src/graphicmaker.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/ai/vort.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/graphicmaker.c -o graphicmaker.o

ini.o:	../../src/ini.c ../../src/ini.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ini.c -o ini.o

intro.o:	../../src/intro.c ../../src/intro.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/pressf10.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/intro.c -o intro.o

menumanager.o:	../../src/menumanager.c ../../src/menumanager.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/menumanager.c -o menumanager.o

menu_options.o:	../../src/menu_options.c ../../src/menu_options.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/menu_options.c -o menu_options.o

menu_keysetup.o:	../../src/menu_keysetup.c ../../src/menu_keysetup.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/menu_keysetup.c -o menu_keysetup.o

menu_savegames.o:	../../src/menu_savegames.c ../../src/menu_savegames.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/menu_savegames.c -o menu_savegames.o

menu_custommap.o:	../../src/menu_custommap.c ../../src/menu_custommap.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/menu_custommap.c -o menu_custommap.o

editor/menu_editor.o:	../../src/editor/menu_editor.c ../../src/editor/menu_editor.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/editor/menu_editor.c -o editor/menu_editor.o

customepisode.o:	../../src/customepisode.c ../../src/customepisode.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/customepisode.c -o customepisode.o

savegame.o:	../../src/savegame.c ../../src/savegame.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/savegame.c -o savegame.o

twirly.o:	../../src/twirly.c ../../src/twirly.fdh
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/twirly.c -o twirly.o

sgrle.o:	../../src/sgrle.c ../../src/sgrle.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/sgrle.c -o sgrle.o

lprintf.o:	../../src/lprintf.c ../../src/lprintf.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/lprintf.c -o lprintf.o

vgatiles.o:	../../src/vgatiles.c ../../src/vgatiles.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/tga.c ../../src/tga.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/vgatiles.c -o vgatiles.o

latch.o:	../../src/latch.c ../../src/latch.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/latch.c -o latch.o

lz.o:	../../src/lz.c ../../src/lz.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/lz.c -o lz.o

message.o:	../../src/message.c ../../src/message.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/message.c -o message.o

cinematics/seqcommon.o:	../../src/cinematics/seqcommon.c ../../src/cinematics/seqcommon.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/cinematics/seqcommon.c -o cinematics/seqcommon.o

cinematics/e1ending.o:	../../src/cinematics/e1ending.c ../../src/cinematics/e1ending.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/cinematics/e1ending.c -o cinematics/e1ending.o

cinematics/e3ending.o:	../../src/cinematics/e3ending.c ../../src/cinematics/e3ending.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/cinematics/e3ending.c -o cinematics/e3ending.o

cinematics/blowupworld.o:	../../src/cinematics/blowupworld.c ../../src/cinematics/blowupworld.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/cinematics/blowupworld.c -o cinematics/blowupworld.o

cinematics/mortimer.o:	../../src/cinematics/mortimer.c ../../src/cinematics/mortimer.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/cinematics/mortimer.c -o cinematics/mortimer.o

cinematics/TBC.o:	../../src/cinematics/TBC.c ../../src/cinematics/TBC.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/cinematics/TBC.c -o cinematics/TBC.o

FinaleScreenLoader.o:	../../src/FinaleScreenLoader.c ../../src/FinaleScreenLoader.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/FinaleScreenLoader.c -o FinaleScreenLoader.o

globals.o:	../../src/globals.c ../../src/globals.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/globals.c -o globals.o

ai/yorp.o:	../../src/ai/yorp.c ../../src/ai/yorp.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/yorp.c -o ai/yorp.o

ai/garg.o:	../../src/ai/garg.c ../../src/ai/garg.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/garg.c -o ai/garg.o

ai/vort.o:	../../src/ai/vort.c ../../src/ai/vort.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/ai/vort.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/vort.c -o ai/vort.o

ai/butler.o:	../../src/ai/butler.c ../../src/ai/butler.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/butler.c -o ai/butler.o

ai/tank.o:	../../src/ai/tank.c ../../src/ai/tank.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/tank.c -o ai/tank.o

ai/door.o:	../../src/ai/door.c ../../src/ai/door.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/door.c -o ai/door.o

ai/ray.o:	../../src/ai/ray.c ../../src/ai/ray.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/ai/ray.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/ray.c -o ai/ray.o

ai/icecannon.o:	../../src/ai/icecannon.c ../../src/ai/icecannon.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/icecannon.c -o ai/icecannon.o

ai/teleport.o:	../../src/ai/teleport.c ../../src/ai/teleport.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/teleport.c -o ai/teleport.o

ai/rope.o:	../../src/ai/rope.c ../../src/ai/rope.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/ai/vort.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/rope.c -o ai/rope.o

ai/walker.o:	../../src/ai/walker.c ../../src/ai/walker.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/walker.c -o ai/walker.o

ai/tankep2.o:	../../src/ai/tankep2.c ../../src/ai/tankep2.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/tankep2.c -o ai/tankep2.o

ai/platform.o:	../../src/ai/platform.c ../../src/ai/platform.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/platform.c -o ai/platform.o

ai/platvert.o:	../../src/ai/platvert.c ../../src/ai/platvert.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/platvert.c -o ai/platvert.o

ai/vortelite.o:	../../src/ai/vortelite.c ../../src/ai/vortelite.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/vortelite.c -o ai/vortelite.o

ai/se.o:	../../src/ai/se.c ../../src/ai/se.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/ai/ray.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/se.c -o ai/se.o

ai/baby.o:	../../src/ai/baby.c ../../src/ai/baby.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/baby.c -o ai/baby.o

ai/earth.o:	../../src/ai/earth.c ../../src/ai/earth.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/earth.c -o ai/earth.o

ai/foob.o:	../../src/ai/foob.c ../../src/ai/foob.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/foob.c -o ai/foob.o

ai/ninja.o:	../../src/ai/ninja.c ../../src/ai/ninja.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/ninja.c -o ai/ninja.o

ai/meep.o:	../../src/ai/meep.c ../../src/ai/meep.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/meep.c -o ai/meep.o

ai/sndwave.o:	../../src/ai/sndwave.c ../../src/ai/sndwave.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/sndwave.c -o ai/sndwave.o

ai/mother.o:	../../src/ai/mother.c ../../src/ai/mother.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/mother.c -o ai/mother.o

ai/fireball.o:	../../src/ai/fireball.c ../../src/ai/fireball.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/ai/ray.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/fireball.c -o ai/fireball.o

ai/balljack.o:	../../src/ai/balljack.c ../../src/ai/balljack.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/balljack.c -o ai/balljack.o

ai/nessie.o:	../../src/ai/nessie.c ../../src/ai/nessie.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/nessie.c -o ai/nessie.o

ai/autoray.o:	../../src/ai/autoray.c ../../src/ai/autoray.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/autoray.c -o ai/autoray.o

ai/gotpoints.o:	../../src/ai/gotpoints.c ../../src/ai/gotpoints.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/ai/gotpoints.c -o ai/gotpoints.o

sdl/keydrv.o:	../../src/sdl/keydrv.c ../../src/sdl/keydrv.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/sdl/keydrv.c -o sdl/keydrv.o

sdl/snddrv.o:	../../src/sdl/snddrv.c ../../src/sdl/snddrv.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h ../../src/sdl/snddrv.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/sdl/snddrv.c -o sdl/snddrv.o

sdl/timedrv.o:	../../src/sdl/timedrv.c ../../src/sdl/timedrv.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/sdl/timedrv.c -o sdl/timedrv.o

sdl/viddrv.o:	../../src/sdl/viddrv.c ../../src/sdl/viddrv.fdh ../../src/keen.h ../../src/osparam.h \
		../../src/sounds.h ../../src/latch.h ../../src/game.h \
		../../src/keys.h ../../src/macros.h ../../src/ai/enemydata.h \
		../../src/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/sdl/viddrv.c -o sdl/viddrv.o

scale2x/scalebit.o:	../../src/scale2x/scalebit.c ../../src/scale2x/scalebit.fdh ../../src/scale2x/scale2x.h ../../src/scale2x/scale3x.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/scale2x/scalebit.c -o scale2x/scalebit.o

scale2x/scale2x.o:	../../src/scale2x/scale2x.c ../../src/scale2x/scale2x.fdh ../../src/scale2x/scale2x.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/scale2x/scale2x.c -o scale2x/scale2x.o

scale2x/scale3x.o:	../../src/scale2x/scale3x.c ../../src/scale2x/scale3x.fdh ../../src/scale2x/scale3x.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/scale2x/scale3x.c -o scale2x/scale3x.o

scale2x/pixel.o:	../../src/scale2x/pixel.c ../../src/scale2x/pixel.fdh ../../src/scale2x/pixel.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/scale2x/pixel.c -o scale2x/pixel.o

platform.o:	../../src/platform.cpp ../../src/platform.fdh ../../src/platform/haiku.cpp ../../src/platform/win32.cpp \
		../../src/platform/stub.cpp
	gcc -O2 -c `$(SDLCONFIG) --cflags` ../../src/platform.cpp -o platform.o


clean:
	rm -f main.o
	rm -f sanity.o
	rm -f game.o
	rm -f gamedo.o
	rm -f gamepdo.o
	rm -f gamepdo_wm.o
	rm -f editor/editor.o
	rm -f editor/autolight.o
	rm -f console.o
	rm -f fileio.o
	rm -f maploader.o
	rm -f map.o
	rm -f graphics.o
	rm -f palette.o
	rm -f fonts.o
	rm -f misc.o
	rm -f misc_ui.o
	rm -f graphicmaker.o
	rm -f ini.o
	rm -f intro.o
	rm -f menumanager.o
	rm -f menu_options.o
	rm -f menu_keysetup.o
	rm -f menu_savegames.o
	rm -f menu_custommap.o
	rm -f editor/menu_editor.o
	rm -f customepisode.o
	rm -f savegame.o
	rm -f twirly.o
	rm -f sgrle.o
	rm -f lprintf.o
	rm -f vgatiles.o
	rm -f latch.o
	rm -f lz.o
	rm -f message.o
	rm -f cinematics/seqcommon.o
	rm -f cinematics/e1ending.o
	rm -f cinematics/e3ending.o
	rm -f cinematics/blowupworld.o
	rm -f cinematics/mortimer.o
	rm -f cinematics/TBC.o
	rm -f FinaleScreenLoader.o
	rm -f globals.o
	rm -f ai/yorp.o
	rm -f ai/garg.o
	rm -f ai/vort.o
	rm -f ai/butler.o
	rm -f ai/tank.o
	rm -f ai/door.o
	rm -f ai/ray.o
	rm -f ai/icecannon.o
	rm -f ai/teleport.o
	rm -f ai/rope.o
	rm -f ai/walker.o
	rm -f ai/tankep2.o
	rm -f ai/platform.o
	rm -f ai/platvert.o
	rm -f ai/vortelite.o
	rm -f ai/se.o
	rm -f ai/baby.o
	rm -f ai/earth.o
	rm -f ai/foob.o
	rm -f ai/ninja.o
	rm -f ai/meep.o
	rm -f ai/sndwave.o
	rm -f ai/mother.o
	rm -f ai/fireball.o
	rm -f ai/balljack.o
	rm -f ai/nessie.o
	rm -f ai/autoray.o
	rm -f ai/gotpoints.o
	rm -f sdl/keydrv.o
	rm -f sdl/snddrv.o
	rm -f sdl/timedrv.o
	rm -f sdl/viddrv.o
	rm -f scale2x/scalebit.o
	rm -f scale2x/scale2x.o
	rm -f scale2x/scale3x.o
	rm -f scale2x/pixel.o
	rm -f platform.o

cleanfdh:
	rm -f ../../src/main.fdh
	rm -f ../../src/sanity.fdh
	rm -f ../../src/game.fdh
	rm -f ../../src/gamedo.fdh
	rm -f ../../src/gamepdo.fdh
	rm -f ../../src/gamepdo_wm.fdh
	rm -f ../../src/editor/editor.fdh
	rm -f ../../src/editor/autolight.fdh
	rm -f ../../src/console.fdh
	rm -f ../../src/fileio.fdh
	rm -f ../../src/maploader.fdh
	rm -f ../../src/map.fdh
	rm -f ../../src/graphics.fdh
	rm -f ../../src/palette.fdh
	rm -f ../../src/fonts.fdh
	rm -f ../../src/misc.fdh
	rm -f ../../src/misc_ui.fdh
	rm -f ../../src/graphicmaker.fdh
	rm -f ../../src/ini.fdh
	rm -f ../../src/intro.fdh
	rm -f ../../src/menumanager.fdh
	rm -f ../../src/menu_options.fdh
	rm -f ../../src/menu_keysetup.fdh
	rm -f ../../src/menu_savegames.fdh
	rm -f ../../src/menu_custommap.fdh
	rm -f ../../src/editor/menu_editor.fdh
	rm -f ../../src/customepisode.fdh
	rm -f ../../src/savegame.fdh
	rm -f ../../src/twirly.fdh
	rm -f ../../src/sgrle.fdh
	rm -f ../../src/lprintf.fdh
	rm -f ../../src/vgatiles.fdh
	rm -f ../../src/latch.fdh
	rm -f ../../src/lz.fdh
	rm -f ../../src/message.fdh
	rm -f ../../src/cinematics/seqcommon.fdh
	rm -f ../../src/cinematics/e1ending.fdh
	rm -f ../../src/cinematics/e3ending.fdh
	rm -f ../../src/cinematics/blowupworld.fdh
	rm -f ../../src/cinematics/mortimer.fdh
	rm -f ../../src/cinematics/TBC.fdh
	rm -f ../../src/FinaleScreenLoader.fdh
	rm -f ../../src/globals.fdh
	rm -f ../../src/ai/yorp.fdh
	rm -f ../../src/ai/garg.fdh
	rm -f ../../src/ai/vort.fdh
	rm -f ../../src/ai/butler.fdh
	rm -f ../../src/ai/tank.fdh
	rm -f ../../src/ai/door.fdh
	rm -f ../../src/ai/ray.fdh
	rm -f ../../src/ai/icecannon.fdh
	rm -f ../../src/ai/teleport.fdh
	rm -f ../../src/ai/rope.fdh
	rm -f ../../src/ai/walker.fdh
	rm -f ../../src/ai/tankep2.fdh
	rm -f ../../src/ai/platform.fdh
	rm -f ../../src/ai/platvert.fdh
	rm -f ../../src/ai/vortelite.fdh
	rm -f ../../src/ai/se.fdh
	rm -f ../../src/ai/baby.fdh
	rm -f ../../src/ai/earth.fdh
	rm -f ../../src/ai/foob.fdh
	rm -f ../../src/ai/ninja.fdh
	rm -f ../../src/ai/meep.fdh
	rm -f ../../src/ai/sndwave.fdh
	rm -f ../../src/ai/mother.fdh
	rm -f ../../src/ai/fireball.fdh
	rm -f ../../src/ai/balljack.fdh
	rm -f ../../src/ai/nessie.fdh
	rm -f ../../src/ai/autoray.fdh
	rm -f ../../src/ai/gotpoints.fdh
	rm -f ../../src/sdl/keydrv.fdh
	rm -f ../../src/sdl/snddrv.fdh
	rm -f ../../src/sdl/timedrv.fdh
	rm -f ../../src/sdl/viddrv.fdh
	rm -f ../../src/scale2x/scalebit.fdh
	rm -f ../../src/scale2x/scale2x.fdh
	rm -f ../../src/scale2x/scale3x.fdh
	rm -f ../../src/scale2x/pixel.fdh
	rm -f ../../src/platform.fdh

cleanall: clean cleanfdh

