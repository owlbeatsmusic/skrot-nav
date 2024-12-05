#!/bin/zsh

gcc -Wall -pedantic -std=iso9899:1999 \
    -I./include -I./lib \
    \
    src/main.c \
    src/common/vector.c \
    src/common/print.c \
    src/engine/renderer.c \
    src/engine/space.c \
    src/nav/communication.c \
    src/nav/core.c \
    src/nav/devices.c \
    src/nav/flight_path.c \
    src/nav/position.c \
    \
    lib/awlib_log/log.c \
    \
    -o \
    main
