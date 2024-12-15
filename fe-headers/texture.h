#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shader.h"
#include <string>

class Texture {

public:
    GLuint id;
    GLenum type;
    int width, height, nrChannels;

    Texture(unsigned char *data, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    Texture(const char *path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    ~Texture();

    unsigned char* getData(const char *path);
    void texUnit(Shader& shader, const char *uniform, GLuint unit);
    void bind();
    void unbind();
    void remove();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif