
FLAGS = -lGL -lGLEW -lglfw -I/usr/include/glm -fmodules-ts


all: build run

build:
	mkdir -p ./bin
	g++ -c ./src/main.cpp -o ./bin/main.o
	gcc -c ./src/boot.c -o ./bin/boot.o
	g++ ./bin/boot.o ./bin/main.o -o ./bin/main ${FLAGS}

run: build
	./bin/main
