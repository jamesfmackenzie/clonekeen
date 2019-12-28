#!/bin/sh

cp -r ../../bin/* .
cp -r ../../data/GAMEDATA/KEEN1/* data
mkdir -p ai
mkdir -p cinematics
mkdir -p editor
mkdir -p scale2x
mkdir -p sdl
mkdir -p bin

make