#!/bin/bash

CFLAGS='-Wall -Wextra -Werror -Wpedantic -fsanitize=address'
CFILES='nm_test.c'
LIBS='-lm'

clang ${CFLAGS} ${CFILES} ${LIBS} -o main
./main
rm main
