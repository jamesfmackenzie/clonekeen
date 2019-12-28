# clonekeen
A very nearly complete clone of one of the classic DOS game, Commander Keen: Invasion of the Vorticons by ID. The game is written in pure C, uses SDL, and is generally very easy to compile on most platforms. The original author is Caitlin Shaw. For more info see http://clonekeen.sourceforge.net/?nav=main

## How to Play
Find pre-packaged, downloadable copies of clonekeen under Releases below. Simply extract and play  

### Controls
* Arrows - Move Keen around
* Ctrl - Jump
* Alt- Use Pogo/Stop Pogo (if you have one)
* Ctrl AND Alt - Fire raygun (if it has charges)

## Releases
Downloadable game packages available in <a href="https://github.com/jamesfmackenzie/clonekeen/tree/master/Releases">Releases</a>. All versions come packaged as zip files with game data. Just extract and run. On Linux, you'll need the <a href="https://wiki.libsdl.org/Installation#Linux.2FUnix" target="_blank">SDL 1.2 runtime</a> installed. Other versions come pre-packaged with SDL

* <a href="https://github.com/jamesfmackenzie/clonekeen/tree/master/Releases/Linux">Releases/Linux</a> - Linux version. Run `./keen`-->
* <a href="https://github.com/jamesfmackenzie/clonekeen/tree/master/Releases/Windows">Releases/Windows</a> - Run `clonekeen.exe`

## Building
You can clone or download the chocolatekeen repo and build it yourself

### Linux
For Linux builds you'll need a C compiler (e.g. gcc) and toolchain. The setup varies between distros. For Ubuntu you can install the build-essential package via `sudo apt-get install build-essential`. Once you have that setup:

1. Install the SDL 1.2.15 development libraries. This varies between Linux distros. For Ubuntu it's `sudo apt-get install libsdl1.2-dev`
2. Launch a shell
3. Navigate to `/build/linux`
4. Run `./build_linux.sh`

### Windows (MinGW)
This is a Makefile project. To build for Windows you'll need something like <a href="https://www.msys2.org/" target="_blank">MSYS2</a> and a gcc toolchain

CloneKeen uses a legacy version of SDL (1.2). At the time of writing there are no 64-bit development libraries available for Windows. You'll need to use a 32-bit gcc toolchain. Find setup instructions <a href="https://www.math.ucla.edu/~wotaoyin/windows_coding.html" target="_blank">here</a>

1. Download and unzip SDL 1.2.15 development libraries: https://www.libsdl.org/download-1.2.php
2. Launch a UNIX shell
3. Navigate to `/build/MingGW`
4. Run `./build_mingw32.sh /path/to/SDL2` e.g. `./build_mingw32.sh /d/Development/SDL-1.2.15`

Game data is automatically copied to the build Directory before compilation

### Windows (Visual Studio)
Build and Debug with Microsoft Visual Studio / Visual C++

1. Navigate to `/build/Visual C++`
2. Open Solution file (`clonekeen.sln`) in Visual Studio
3. Restore NuGet dependencies (Project -> Manage NuGet Dependencies > Restore)
4. Build (Build > Build Solution)
5. Run (Debug > Start Without Debugging) or Debug (Debug > Start Debugging)

Game data is automatically copied to the Target Directory as part of build - so everything should "just run"

## Authors
The original author of clonekeen is Caitlin Shaw. For more info see http://clonekeen.sourceforge.net/?nav=main
