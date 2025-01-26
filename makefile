SRC_DIR = src/
BIN_DIR = bin/
TARGET = main.cpp fmt_wav.c xclock.c vgui/vgui_base.c
INCLUDE = lib/sdl-mingw32/include
LINK = lib/sdl-mingw32/lib
BIN = writetowav
CC = g++
CFLAGS = -Wall -Werror -std=c++11 -I ${INCLUDE}
LDFLAGS = -L ${LINK} -lSDL3

SRC_FILES = $(patsubst %, $(SRC_DIR)%, $(TARGET))

all:
	${CC} ${CFLAGS} ${SRC_FILES} ${LDFLAGS} -o ${BIN_DIR}${BIN}

