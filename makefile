SRC_DIR = src/
BIN_DIR = bin/
CD_DIR = ${SRC_DIR}vgui/
INCLUDESDL = lib/sdl-mingw32/include
INCLUDEIMGUI = src/imgui/include
LINK = lib/sdl-mingw32/lib
BIN = writetowav
CC = g++
CFLAGS = -Wall -Werror -std=c++11 -I ${INCLUDESDL} -I ${INCLUDEIMGUI}
LDFLAGS = -L ${LINK} -lSDL3

SRC = $(wildcard ${SRC_DIR}*.cpp) $(wildcard ${CD_DIR}*.cpp) $(wildcard ${SRC_DIR}*.c) $(wildcard ${SRC_DIR}imgui/*.cpp) 

all:
	${CC} ${CFLAGS} ${SRC} ${LDFLAGS} -o ${BIN_DIR}${BIN}

