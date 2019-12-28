SRC=../../src
SDLCONFIG=sdl-config

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
	 `$(SDLCONFIG) --libs` -lstdc++ -lm

main.o:	$(SRC)/main.c $(SRC)/main.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/main.c -o main.o

sanity.o:	$(SRC)/sanity.c $(SRC)/sanity.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/sanity.c -o sanity.o

game.o:	$(SRC)/game.c $(SRC)/game.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/game.c -o game.o

gamedo.o:	$(SRC)/gamedo.c $(SRC)/gamedo.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/gamedo.c -o gamedo.o

gamepdo.o:	$(SRC)/gamepdo.c $(SRC)/gamepdo.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/gamepdo.c -o gamepdo.o

gamepdo_wm.o:	$(SRC)/gamepdo_wm.c $(SRC)/gamepdo_wm.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/gamepdo_wm.c -o gamepdo_wm.o

editor/editor.o:	$(SRC)/editor/editor.c $(SRC)/editor/editor.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/editor/buttons.c $(SRC)/editor/ghosting.c \
		$(SRC)/editor/autoblock.c
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/editor/editor.c -o editor/editor.o

editor/autolight.o:	$(SRC)/editor/autolight.c $(SRC)/editor/autolight.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/editor/autolight.c -o editor/autolight.o

console.o:	$(SRC)/console.c $(SRC)/console.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/console.c -o console.o

fileio.o:	$(SRC)/fileio.c $(SRC)/fileio.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/fileio.c -o fileio.o

maploader.o:	$(SRC)/maploader.c $(SRC)/maploader.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/maploader.c -o maploader.o

map.o:	$(SRC)/map.c $(SRC)/map.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/map.c -o map.o

graphics.o:	$(SRC)/graphics.c $(SRC)/graphics.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/graphics.c -o graphics.o

palette.o:	$(SRC)/palette.c $(SRC)/palette.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/palette.c -o palette.o

fonts.o:	$(SRC)/fonts.c $(SRC)/fonts.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/fonts.c -o fonts.o

misc.o:	$(SRC)/misc.c $(SRC)/misc.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/misc.c -o misc.o

misc_ui.o:	$(SRC)/misc_ui.c $(SRC)/misc_ui.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/misc_ui.c -o misc_ui.o

graphicmaker.o:	$(SRC)/graphicmaker.c $(SRC)/graphicmaker.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/ai/vort.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/graphicmaker.c -o graphicmaker.o

ini.o:	$(SRC)/ini.c $(SRC)/ini.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ini.c -o ini.o

intro.o:	$(SRC)/intro.c $(SRC)/intro.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/pressf10.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/intro.c -o intro.o

menumanager.o:	$(SRC)/menumanager.c $(SRC)/menumanager.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/menumanager.c -o menumanager.o

menu_options.o:	$(SRC)/menu_options.c $(SRC)/menu_options.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/menu_options.c -o menu_options.o

menu_keysetup.o:	$(SRC)/menu_keysetup.c $(SRC)/menu_keysetup.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/menu_keysetup.c -o menu_keysetup.o

menu_savegames.o:	$(SRC)/menu_savegames.c $(SRC)/menu_savegames.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/menu_savegames.c -o menu_savegames.o

menu_custommap.o:	$(SRC)/menu_custommap.c $(SRC)/menu_custommap.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/menu_custommap.c -o menu_custommap.o

editor/menu_editor.o:	$(SRC)/editor/menu_editor.c $(SRC)/editor/menu_editor.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/menu.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/editor/menu_editor.c -o editor/menu_editor.o

customepisode.o:	$(SRC)/customepisode.c $(SRC)/customepisode.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/customepisode.c -o customepisode.o

savegame.o:	$(SRC)/savegame.c $(SRC)/savegame.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/savegame.c -o savegame.o

twirly.o:	$(SRC)/twirly.c $(SRC)/twirly.fdh
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/twirly.c -o twirly.o

sgrle.o:	$(SRC)/sgrle.c $(SRC)/sgrle.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/sgrle.c -o sgrle.o

lprintf.o:	$(SRC)/lprintf.c $(SRC)/lprintf.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/lprintf.c -o lprintf.o

vgatiles.o:	$(SRC)/vgatiles.c $(SRC)/vgatiles.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/tga.c $(SRC)/tga.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/vgatiles.c -o vgatiles.o

latch.o:	$(SRC)/latch.c $(SRC)/latch.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/latch.c -o latch.o

lz.o:	$(SRC)/lz.c $(SRC)/lz.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/lz.c -o lz.o

message.o:	$(SRC)/message.c $(SRC)/message.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/message.c -o message.o

cinematics/seqcommon.o:	$(SRC)/cinematics/seqcommon.c $(SRC)/cinematics/seqcommon.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/cinematics/seqcommon.c -o cinematics/seqcommon.o

cinematics/e1ending.o:	$(SRC)/cinematics/e1ending.c $(SRC)/cinematics/e1ending.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/cinematics/e1ending.c -o cinematics/e1ending.o

cinematics/e3ending.o:	$(SRC)/cinematics/e3ending.c $(SRC)/cinematics/e3ending.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/cinematics/e3ending.c -o cinematics/e3ending.o

cinematics/blowupworld.o:	$(SRC)/cinematics/blowupworld.c $(SRC)/cinematics/blowupworld.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/cinematics/blowupworld.c -o cinematics/blowupworld.o

cinematics/mortimer.o:	$(SRC)/cinematics/mortimer.c $(SRC)/cinematics/mortimer.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/cinematics/mortimer.c -o cinematics/mortimer.o

cinematics/TBC.o:	$(SRC)/cinematics/TBC.c $(SRC)/cinematics/TBC.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/cinematics/TBC.c -o cinematics/TBC.o

FinaleScreenLoader.o:	$(SRC)/FinaleScreenLoader.c $(SRC)/FinaleScreenLoader.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/FinaleScreenLoader.c -o FinaleScreenLoader.o

globals.o:	$(SRC)/globals.c $(SRC)/globals.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/globals.c -o globals.o

ai/yorp.o:	$(SRC)/ai/yorp.c $(SRC)/ai/yorp.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/yorp.c -o ai/yorp.o

ai/garg.o:	$(SRC)/ai/garg.c $(SRC)/ai/garg.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/garg.c -o ai/garg.o

ai/vort.o:	$(SRC)/ai/vort.c $(SRC)/ai/vort.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/ai/vort.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/vort.c -o ai/vort.o

ai/butler.o:	$(SRC)/ai/butler.c $(SRC)/ai/butler.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/butler.c -o ai/butler.o

ai/tank.o:	$(SRC)/ai/tank.c $(SRC)/ai/tank.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/tank.c -o ai/tank.o

ai/door.o:	$(SRC)/ai/door.c $(SRC)/ai/door.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/door.c -o ai/door.o

ai/ray.o:	$(SRC)/ai/ray.c $(SRC)/ai/ray.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/ai/ray.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/ray.c -o ai/ray.o

ai/icecannon.o:	$(SRC)/ai/icecannon.c $(SRC)/ai/icecannon.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/icecannon.c -o ai/icecannon.o

ai/teleport.o:	$(SRC)/ai/teleport.c $(SRC)/ai/teleport.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/teleport.c -o ai/teleport.o

ai/rope.o:	$(SRC)/ai/rope.c $(SRC)/ai/rope.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/ai/vort.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/rope.c -o ai/rope.o

ai/walker.o:	$(SRC)/ai/walker.c $(SRC)/ai/walker.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/walker.c -o ai/walker.o

ai/tankep2.o:	$(SRC)/ai/tankep2.c $(SRC)/ai/tankep2.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/tankep2.c -o ai/tankep2.o

ai/platform.o:	$(SRC)/ai/platform.c $(SRC)/ai/platform.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/platform.c -o ai/platform.o

ai/platvert.o:	$(SRC)/ai/platvert.c $(SRC)/ai/platvert.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/platvert.c -o ai/platvert.o

ai/vortelite.o:	$(SRC)/ai/vortelite.c $(SRC)/ai/vortelite.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/vortelite.c -o ai/vortelite.o

ai/se.o:	$(SRC)/ai/se.c $(SRC)/ai/se.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/ai/ray.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/se.c -o ai/se.o

ai/baby.o:	$(SRC)/ai/baby.c $(SRC)/ai/baby.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/baby.c -o ai/baby.o

ai/earth.o:	$(SRC)/ai/earth.c $(SRC)/ai/earth.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/earth.c -o ai/earth.o

ai/foob.o:	$(SRC)/ai/foob.c $(SRC)/ai/foob.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/foob.c -o ai/foob.o

ai/ninja.o:	$(SRC)/ai/ninja.c $(SRC)/ai/ninja.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/ninja.c -o ai/ninja.o

ai/meep.o:	$(SRC)/ai/meep.c $(SRC)/ai/meep.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/meep.c -o ai/meep.o

ai/sndwave.o:	$(SRC)/ai/sndwave.c $(SRC)/ai/sndwave.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/sndwave.c -o ai/sndwave.o

ai/mother.o:	$(SRC)/ai/mother.c $(SRC)/ai/mother.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/mother.c -o ai/mother.o

ai/fireball.o:	$(SRC)/ai/fireball.c $(SRC)/ai/fireball.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/ai/ray.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/fireball.c -o ai/fireball.o

ai/balljack.o:	$(SRC)/ai/balljack.c $(SRC)/ai/balljack.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/balljack.c -o ai/balljack.o

ai/nessie.o:	$(SRC)/ai/nessie.c $(SRC)/ai/nessie.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/nessie.c -o ai/nessie.o

ai/autoray.o:	$(SRC)/ai/autoray.c $(SRC)/ai/autoray.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/autoray.c -o ai/autoray.o

ai/gotpoints.o:	$(SRC)/ai/gotpoints.c $(SRC)/ai/gotpoints.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/ai/gotpoints.c -o ai/gotpoints.o

sdl/keydrv.o:	$(SRC)/sdl/keydrv.c $(SRC)/sdl/keydrv.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/sdl/keydrv.c -o sdl/keydrv.o

sdl/snddrv.o:	$(SRC)/sdl/snddrv.c $(SRC)/sdl/snddrv.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h $(SRC)/sdl/snddrv.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/sdl/snddrv.c -o sdl/snddrv.o

sdl/timedrv.o:	$(SRC)/sdl/timedrv.c $(SRC)/sdl/timedrv.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/sdl/timedrv.c -o sdl/timedrv.o

sdl/viddrv.o:	$(SRC)/sdl/viddrv.c $(SRC)/sdl/viddrv.fdh $(SRC)/keen.h $(SRC)/osparam.h \
		$(SRC)/sounds.h $(SRC)/latch.h $(SRC)/game.h \
		$(SRC)/keys.h $(SRC)/macros.h $(SRC)/ai/enemydata.h \
		$(SRC)/globals.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/sdl/viddrv.c -o sdl/viddrv.o

scale2x/scalebit.o:	$(SRC)/scale2x/scalebit.c $(SRC)/scale2x/scalebit.fdh $(SRC)/scale2x/scale2x.h $(SRC)/scale2x/scale3x.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/scale2x/scalebit.c -o scale2x/scalebit.o

scale2x/scale2x.o:	$(SRC)/scale2x/scale2x.c $(SRC)/scale2x/scale2x.fdh $(SRC)/scale2x/scale2x.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/scale2x/scale2x.c -o scale2x/scale2x.o

scale2x/scale3x.o:	$(SRC)/scale2x/scale3x.c $(SRC)/scale2x/scale3x.fdh $(SRC)/scale2x/scale3x.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/scale2x/scale3x.c -o scale2x/scale3x.o

scale2x/pixel.o:	$(SRC)/scale2x/pixel.c $(SRC)/scale2x/pixel.fdh $(SRC)/scale2x/pixel.h
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/scale2x/pixel.c -o scale2x/pixel.o

platform.o:	$(SRC)/bootstrap.cpp $(SRC)/bootstrap.fdh $(SRC)/platform/haiku.cpp $(SRC)/platform/win32.cpp \
		$(SRC)/platform/stub.cpp
	gcc -O2 -c `$(SDLCONFIG) --cflags` $(SRC)/bootstrap.cpp -o platform.o


cleanobjects:
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

cleandirectories:
	rm -rf ai
	rm -rf cinematics
	rm -rf editor
	rm -rf scale2x
	rm -rf sdl
	rm -rf bin

cleanexe:
	rm -f keen.exe

cleandll:
	rm -f SDL.dll

cleanfdh:
	rm -f $(SRC)/main.fdh
	rm -f $(SRC)/sanity.fdh
	rm -f $(SRC)/game.fdh
	rm -f $(SRC)/gamedo.fdh
	rm -f $(SRC)/gamepdo.fdh
	rm -f $(SRC)/gamepdo_wm.fdh
	rm -f $(SRC)/editor/editor.fdh
	rm -f $(SRC)/editor/autolight.fdh
	rm -f $(SRC)/console.fdh
	rm -f $(SRC)/fileio.fdh
	rm -f $(SRC)/maploader.fdh
	rm -f $(SRC)/map.fdh
	rm -f $(SRC)/graphics.fdh
	rm -f $(SRC)/palette.fdh
	rm -f $(SRC)/fonts.fdh
	rm -f $(SRC)/misc.fdh
	rm -f $(SRC)/misc_ui.fdh
	rm -f $(SRC)/graphicmaker.fdh
	rm -f $(SRC)/ini.fdh
	rm -f $(SRC)/intro.fdh
	rm -f $(SRC)/menumanager.fdh
	rm -f $(SRC)/menu_options.fdh
	rm -f $(SRC)/menu_keysetup.fdh
	rm -f $(SRC)/menu_savegames.fdh
	rm -f $(SRC)/menu_custommap.fdh
	rm -f $(SRC)/editor/menu_editor.fdh
	rm -f $(SRC)/customepisode.fdh
	rm -f $(SRC)/savegame.fdh
	rm -f $(SRC)/twirly.fdh
	rm -f $(SRC)/sgrle.fdh
	rm -f $(SRC)/lprintf.fdh
	rm -f $(SRC)/vgatiles.fdh
	rm -f $(SRC)/latch.fdh
	rm -f $(SRC)/lz.fdh
	rm -f $(SRC)/message.fdh
	rm -f $(SRC)/cinematics/seqcommon.fdh
	rm -f $(SRC)/cinematics/e1ending.fdh
	rm -f $(SRC)/cinematics/e3ending.fdh
	rm -f $(SRC)/cinematics/blowupworld.fdh
	rm -f $(SRC)/cinematics/mortimer.fdh
	rm -f $(SRC)/cinematics/TBC.fdh
	rm -f $(SRC)/FinaleScreenLoader.fdh
	rm -f $(SRC)/globals.fdh
	rm -f $(SRC)/ai/yorp.fdh
	rm -f $(SRC)/ai/garg.fdh
	rm -f $(SRC)/ai/vort.fdh
	rm -f $(SRC)/ai/butler.fdh
	rm -f $(SRC)/ai/tank.fdh
	rm -f $(SRC)/ai/door.fdh
	rm -f $(SRC)/ai/ray.fdh
	rm -f $(SRC)/ai/icecannon.fdh
	rm -f $(SRC)/ai/teleport.fdh
	rm -f $(SRC)/ai/rope.fdh
	rm -f $(SRC)/ai/walker.fdh
	rm -f $(SRC)/ai/tankep2.fdh
	rm -f $(SRC)/ai/platform.fdh
	rm -f $(SRC)/ai/platvert.fdh
	rm -f $(SRC)/ai/vortelite.fdh
	rm -f $(SRC)/ai/se.fdh
	rm -f $(SRC)/ai/baby.fdh
	rm -f $(SRC)/ai/earth.fdh
	rm -f $(SRC)/ai/foob.fdh
	rm -f $(SRC)/ai/ninja.fdh
	rm -f $(SRC)/ai/meep.fdh
	rm -f $(SRC)/ai/sndwave.fdh
	rm -f $(SRC)/ai/mother.fdh
	rm -f $(SRC)/ai/fireball.fdh
	rm -f $(SRC)/ai/balljack.fdh
	rm -f $(SRC)/ai/nessie.fdh
	rm -f $(SRC)/ai/autoray.fdh
	rm -f $(SRC)/ai/gotpoints.fdh
	rm -f $(SRC)/sdl/keydrv.fdh
	rm -f $(SRC)/sdl/snddrv.fdh
	rm -f $(SRC)/sdl/timedrv.fdh
	rm -f $(SRC)/sdl/viddrv.fdh
	rm -f $(SRC)/scale2x/scalebit.fdh
	rm -f $(SRC)/scale2x/scale2x.fdh
	rm -f $(SRC)/scale2x/scale3x.fdh
	rm -f $(SRC)/scale2x/pixel.fdh
	rm -f $(SRC)/platform.fdh

clean: cleanobjects cleandirectories cleanexe cleandll

cleanall: cleanobjects cleandirectories cleanexe cleandll cleanfdh

