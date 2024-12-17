#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
public:
    GLuint VBObuff;

    VBO(GLfloat* vertices, GLsizeiptr size);
    ~VBO();
    void bind();
    void unbind();
    void free();
};

#endif