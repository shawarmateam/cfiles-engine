
#FLAGS = -lGL -lGLEW -lglfw -I/usr/include/glm -fmodules-ts -I/usr/include/

CXX = g++
CXXFLAGS = -I/usr/include -lGL -lglfw -I/usr/include/glm -I./include
SOURCES = src/main.cpp src/glad.c src/buffers.cpp src/shader.cpp
#SOURCES = src/*
#src/shader.cpp

TARGET_DIR = bin
TARGET = $(TARGET_DIR)/main

all: $(TARGET_DIR) $(TARGET)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET_DIR)
