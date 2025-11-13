#!/bin/bash

CFLAGS='-std=c89 -Wall -Wextra -Wpedantic -fsanitize=address'
CFILES='nm_test.c'
LIBS='-lm'

clang ${CFLAGS} ${LIBS} ${CFILES} -o main
./main
rm main
