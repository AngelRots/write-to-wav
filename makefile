SRC_DIR = src/
BIN_DIR = bin/
TARGET = main.cpp fmt_wav.c xclock.c vgui/vgui_base.c
INCLUDE = lib/sdl-mingw32/include lib/imgui
LINK = lib/sdl-mingw32/lib
BIN = writetowav
CC = g++
CFLAGS = -Wall -Werror -std=c++11 $(foreach d, $(INCLUDE), -I$d)
LDFLAGS = -L ${LINK} -lSDL3

# ImGui source files
IMGUI_SRC = lib/imgui/imgui.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp lib/imgui/backends/imgui_impl_sdl3.cpp lib/imgui/backends/imgui_impl_opengl3.cpp

SRC_FILES = $(patsubst %, $(SRC_DIR)%, $(TARGET)) $(IMGUI_SRC)

all:
	${CC} ${CFLAGS} ${SRC_FILES} ${LDFLAGS} -o ${BIN_DIR}${BIN}