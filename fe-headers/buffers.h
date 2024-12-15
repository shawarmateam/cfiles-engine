#ifndef BUFFERS_FE_H
#define BUFFERS_FE_H

#include <glad/glad.h>

class Buffers
{
    public:
        GLuint VBO, VAO, EBO;
        Buffers();
        void makeAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
        void unbind();
        void bind();
        void free();
};

#endif // BUFFERS_FE_H
