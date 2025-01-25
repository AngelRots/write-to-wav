SRC_DIR = src/
BIN_DIR = bin/
TARGET = main.c
INCLUDE = lib/sdl-mingw32/include
LINK = lib/sdl-mingw32/lib
BIN = writetowav
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -I ${INCLUDE}
LDFLAGS = -L ${LINK} -lSDL3

all:
	${CC} ${CFLAGS} ${SRC_DIR}${TARGET} ${LDFLAGS} -o ${BIN_DIR}${BIN}