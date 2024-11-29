
FLAGS = -lGL -lGLEW -lglfw


all: build run

build:
	mkdir -p ./bin
	g++ ./src/main.cpp -o ./bin/main ${FLAGS}

run: build
	./bin/main
