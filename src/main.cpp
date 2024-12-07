#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.cpp"
#include "fe-kernel.h"
#include "shader.cpp"
#include "render-texture.cpp"

const char *vertexShaderCode =
"#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderCode =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";

void run()
{
    std::cout << "Starting files engine..." << std::endl;
}

int loop()
{
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3,   0.0f,
         0.5f, -0.5f * float(sqrt(3)) / 3,   0.0f,
         0.0f,  0.5f * float(sqrt(3))*2 / 3, 0.0f
    };

    Window window_main;
    window_main.init();

    glViewport(0,0,600,600);

    Shader shader;
    shader.init("shaders/shader_def.glsl");

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    RenderTexture test;
    size_t size_test=0;
    test.setImg("/home/adisteyf/2024-11-14_11-57.png", size_test);

    while (!glfwWindowShouldClose(window_main.getWindow())) {
        glfwPollEvents();

        glfwSwapBuffers(window_main.getWindow());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        shader.bind();
        test.bind(0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    window_main.kill();

    glfwDestroyWindow(window_main.getWindow());
    glfwTerminate();
    return 0;
}
