#include "model.h"

Model::Model() {
    Model::vertices = {
        -0.5f,  0.0f, 0.5f,        0.83f, 0.70f, 0.44f,       0.0f, 0.0f, // Bottom left
        -0.5f,  0.0f, -0.5f,        0.83f, 0.70f, 0.44f,      5.0f, 0.0f, // Top left
         0.5f,  0.0f, -0.5f,        0.83f, 0.70f, 0.44f,      0.0f, 0.0f, // Top right
         0.5f,  0.0f, 0.5f,        0.83f, 0.70f, 0.44f,       5.0f, 0.0f,  // Bottom right
         0.0f, 0.8f, 0.0f,        0.92f, 0.86f, 0.76f,       2.5f, 5.0f
    };

    Model::indices = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };


    glBufferData(GL_ARRAY_BUFFER, Model::vertices.size() * sizeof(GLfloat), Model::vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffs.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model::indices.size() * sizeof(GLuint), Model::indices.data(), GL_STATIC_DRAW);

    constexpr GLsizei stride = 8 * sizeof(GLfloat);
    
    buffs.makeAttrib(0, 3, GL_FLOAT, stride, nullptr);
    buffs.makeAttrib(1, 3, GL_FLOAT, stride, (GLvoid*)(3 * sizeof(GLfloat)));
    buffs.makeAttrib(2, 2, GL_FLOAT, stride, (GLvoid*)(6 * sizeof(GLfloat)));
}

void Model::bindBuff() {
    buffs.bind();
    glDrawElements(GL_TRIANGLES, Model::indices.size(), GL_UNSIGNED_INT, nullptr);
}

Model::~Model() {
    buffs.free();
}