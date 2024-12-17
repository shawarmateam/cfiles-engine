#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &VBObuff);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuff);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    free();
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBObuff);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::free()
{
    glDeleteBuffers(1, &VBObuff);
}