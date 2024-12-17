#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{
public:
    GLuint EBObuff;

    EBO(GLuint* indices, GLsizeiptr size);
    ~EBO();
    void bind();
    void unbind();
    void free();
};

#endif