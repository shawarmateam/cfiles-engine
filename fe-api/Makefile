# Makefile
all: build

CC = gcc
FLAGS = -fPIC -shared
OUT = libfe-api.so
BINF = bin
CODE = fe-api.c

build:
	mkdir -p ${BINF}
	${CC} ${FLAGS} -o ${BINF}/${OUT} ${CODE}

run: build
	LD_PRELOAD=${BINF}/${OUT} ./test

clean:
	rm -rf ${BINF}
