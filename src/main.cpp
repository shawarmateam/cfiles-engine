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

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Set the viewport
    glViewport(0, 0, 600, 600);

    // Define the vertices for a triangle
    GLfloat vertices[] = 
    {
        -0.5f, -0.5f * sqrt(3) / 3, 0.0f,
         0.5f, -0.5f * sqrt(3) / 3, 0.0f,
         0.0f,  0.5f * sqrt(3)*2 / 3, 0.0f,
        
        -0.5f/2, 0.5f * sqrt(3) / 6, 0.0f,
         0.5f/2, 0.5f * sqrt(3) / 6, 0.0f,
         0.0f,  -0.5f * sqrt(3) / 3, 0.0f
    };

    GLuint indices[] =
    {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    Buffers buffs;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffs.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Load and compile shaders
    Shader shader("shaders/shader_def.glsl");

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Clear the color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        shader.bind();

        // Draw the triangle
        buffs.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    buffs.free();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

