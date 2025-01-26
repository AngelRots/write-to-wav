SRC_DIR = src/
BIN_DIR = bin/
TARGET = main.c fmt_wav.c xclock.c vgui/vgui_base.c
INCLUDE = lib/sdl-mingw32/include
LINK = lib/sdl-mingw32/lib
BIN = writetowav
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -I ${INCLUDE}
LDFLAGS = -L ${LINK} -lSDL3

SRC_FILES = $(patsubst %, $(SRC_DIR)%, $(TARGET))

all:
	${CC} ${CFLAGS} ${SRC_FILES} ${LDFLAGS} -o ${BIN_DIR}${BIN}

