#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <glad/glad.h>
#include "buffers.h"

class Model {
public:
    Buffers buffs;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    Model();
    ~Model();
    void bindBuff();
};

#endif