#ifndef BUFFERS_FE_H
#define BUFFERS_FE_H

#include <glad/glad.h>

class Buffers
{
    public:
        GLuint VBO, VAO, EBO;
        Buffers();
        void unbind();
        void bind();
        void free();
};

#endif // BUFFERS_FE_H
