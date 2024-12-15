#include "buffers.h"


Buffers::Buffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    Buffers::bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Buffers::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffers::makeAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}

void Buffers::bind()
{
    glBindVertexArray(VAO);
}

void Buffers::free()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
