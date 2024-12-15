#include "window.h"
#include "shader.h"
#include "buffers.h"
#include <cmath>
#include <vector>
#include "stb/stb_image.h"

int fe_main() {
    Window::initGLFW();
    
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    const std::vector<GLfloat> vertices = {
        -0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f,       0.0f, 0.0f, // Bottom left
        -0.5f,  0.5f, 0.0f,        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, // Top left
         0.5f,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f,       1.0f, 1.0f, // Top right
         0.5f, -0.5f, 0.0f,        1.0f, 1.0f, 1.0f,       1.0f, 0.0f  // Bottom right
    };

    const std::vector<GLuint> indices = {
        0, 2, 1, // Top triangle
        0, 3, 2  // Bottom triangle
    };

    Buffers buffs;
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffs.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    constexpr GLsizei stride = 8 * sizeof(GLfloat);
    buffs.makeAttrib(0, 3, GL_FLOAT, stride, nullptr);
    buffs.makeAttrib(1, 3, GL_FLOAT, stride, (GLvoid*)(3 * sizeof(GLfloat)));
    buffs.makeAttrib(2, 2, GL_FLOAT, stride, (GLvoid*)(6 * sizeof(GLfloat)));

    Shader shader("shaders/shader_def.glsl");
    const GLuint uniID = glGetUniformLocation(shader.getProgram(), "scale");

    int wImg, hImg, nImg;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load("assets/textures/logo.png", &wImg, &hImg, &nImg, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wImg, hImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0 = glGetUniformLocation(shader.getProgram(), "tex0");
    shader.bind();
    glUniform1i(tex0, 0);

    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        shader.bind();
        glUniform1f(uniID, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
        buffs.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        window.swapBuffers();
    }

    buffs.free();
    Window::terminateGLFW();
    glDeleteTextures(1, &texture);

    return 0;
}

