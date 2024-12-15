#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <cstring>
#include "shader.h"
#include "buffers.h"

int fe_main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

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

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();
        glUniform1f(uniID, 0.5f);
        buffs.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
    }

    buffs.free();
    shader.killShader();
    shader.freeShader();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

