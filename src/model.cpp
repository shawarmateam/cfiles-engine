#include "model.h"

Model::Model() {
    Model::vertices = {
        -0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f,       0.0f, 0.0f, // Bottom left
        -0.5f,  0.5f, 0.0f,        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, // Top left
         0.5f,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f,       1.0f, 1.0f, // Top right
         0.5f, -0.5f, 0.0f,        1.0f, 1.0f, 1.0f,       1.0f, 0.0f  // Bottom right
    };

    Model::indices = {
        0, 2, 1, // Top triangle
        0, 3, 2  // Bottom triangle
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