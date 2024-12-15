#include "window.h"
#include "shader.h"
#include "buffers.h"
#include <cmath>
#include <vector>

int fe_main() {
    Window::initGLFW();
    
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    const std::vector<GLfloat> vertices = {
        -0.5f, -0.5f * sqrt(3)/3, 0.0f, 0.8f, 0.3f, 0.2f,
         0.5f, -0.5f * sqrt(3)/3, 0.0f, 0.8f, 0.3f, 0.02f,
         0.0f,  0.5f * sqrt(3)*2/3, 0.0f, 1.0f, 0.6f, 0.32f,
        -0.25f, 0.5f * sqrt(3)/6, 0.0f, 0.9f, 0.45f, 0.17f,
         0.25f, 0.5f * sqrt(3)/6, 0.0f, 0.9f, 0.45f, 0.17f,
         0.0f, -0.5f * sqrt(3)/3, 0.0f, 0.8f, 0.3f, 0.02f
    };

    const std::vector<GLuint> indices = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    Buffers buffs;
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffs.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    constexpr GLsizei stride = 6 * sizeof(GLfloat);
    buffs.makeAttrib(0, 3, GL_FLOAT, stride, nullptr);
    buffs.makeAttrib(1, 3, GL_FLOAT, stride, (GLvoid*)(3 * sizeof(GLfloat)));

    Shader shader("shaders/shader_def.glsl");
    const GLuint uniID = glGetUniformLocation(shader.getProgram(), "scale");

    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        shader.bind();
        glUniform1f(uniID, 0.5f);
        buffs.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        window.swapBuffers();
    }

    buffs.free();
    Window::terminateGLFW();

    return 0;
}

