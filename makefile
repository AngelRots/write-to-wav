SRC_DIR = src/
BIN_DIR = bin/
TARGET = main.cpp fmt_wav.c xclock.c vgui/vgui_base.c
INCLUDESDL = lib/sdl-mingw32/include
INCLUDEIMGUI = src/imgui/include
LINK = lib/sdl-mingw32/lib
BIN = writetowav
CC = g++
CFLAGS = -Wall -Werror -std=c++11 -I ${INCLUDESDL} -I ${INCLUDEIMGUI}
LDFLAGS = -L ${LINK} -lSDL3

SRC_FILES = $(wildcard src/*.cpp) $(wildcard src/*.c) $(wildcard src/imgui/*.cpp) 

all:
	${CC} ${CFLAGS} ${SRC_FILES} ${LDFLAGS} -o ${BIN_DIR}${BIN}

