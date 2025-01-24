SRC_DIR = src/
TARGET = main.c
CC = gcc
CFLAGS = -Wall

all:
	${CC} ${CFLAGS} ${SRC_DIR}${TARGET} -o wav_exec