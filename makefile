SRC_DIR = src/
TARGET = main.c
CC = gcc
CFLAGS = -Wall -Werror -std=c99

all:
	${CC} ${CFLAGS} ${SRC_DIR}${TARGET} -o wav_exec