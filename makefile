SRC_DIR = src/
TARGET = main.c
CC = gcc
CFLAGS = -Wall -Werror

all:
	${CC} ${CFLAGS} ${SRC_DIR}${TARGET} -o wav_exec