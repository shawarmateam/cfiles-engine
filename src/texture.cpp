#include "texture.h"

Texture::Texture(const char *path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(texType, id);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, data);
    glGenerateMipmap(texType);

    stbi_image_free(data);
    glBindTexture(texType, 0);
}


Texture::Texture(unsigned char *data, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;
    
    stbi_set_flip_vertically_on_load(true);
    //unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(texType, id);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, data);
    glGenerateMipmap(texType);

    stbi_image_free(data);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char *uniform, GLuint unit) {
    GLuint tex0Uni = glGetUniformLocation(shader.getProgram(), uniform);
    shader.bind();
    glUniform1i(tex0Uni, unit);
}

void Texture::bind() {
    glBindTexture(type, id);
}

void Texture::unbind() {
    glBindTexture(type, 0);
}

void Texture::remove() {
    glDeleteTextures(1, &id);
}

Texture::~Texture() {
    remove();
}
