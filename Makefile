CXX = g++
INCLUDES = /usr/include /usr/include/glm ./include ./fe-headers
INCLUDES_FLAGS = $(addprefix -I,$(INCLUDES))
CXXFLAGS = $(INCLUDES_FLAGS) -lGL -lglfw
SOURCES = src/main.cpp src/glad.c src/buffers.cpp src/shader.cpp src/boot.c src/window.cpp src/stb.cpp
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/main

all: $(TARGET_DIR) $(TARGET)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET_DIR)
