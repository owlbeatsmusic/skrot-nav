#!/bin/zsh
gcc -Wall -pedantic -std=iso9899:1999 src/main.c src/external/space.c src/navigation/skrot-nav.c src/navigation/devices.c src/external/renderer.c libraries/awlib_log/log.c -o main