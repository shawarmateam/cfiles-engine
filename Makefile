
FLAGS = -lGL -lGLEW -lglfw


all: build run

build:
	mkdir -p ./bin
	g++ -c ./src/main.cpp -o ./bin/main.o
	gcc -c ./src/boot.c -o ./bin/boot.o
	g++ ./bin/boot.o ./bin/main.o -o main ${FLAGS}

run: build
	./bin/main
