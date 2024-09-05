#!/bin/zsh
gcc src/main.c src/space.c src/skrot-nav.c src/devices.c src/renderer.c src/awlib_log/log.c -v -o main -Wall