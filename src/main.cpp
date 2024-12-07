#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.cpp"
#include "fe-kernel.h"
#include "shader.cpp"
#include "render-texture.cpp"
#include "camera.cpp"

Camera cam;
Window window_main;

void run()
{
    std::cout << "Starting files engine..." << std::endl;
    window_main.init();
    cam.init(); // TODO: add transform
    glEnable(GL_TEXTURE_2D);
}

int loop()
{
    glViewport(0,0,600,600);

    Shader shader;
    shader.init("shaders/shader_def.glsl");
    glm::mat4 projection = glm::mat4()
        .ortho2D(cam.transform.sizeX/2, -cam.transform.sizeX/2, cam.transform.sizeY/2, -cam.transform.sizeY/2);

    RenderTexture test;
    size_t size_test=0;
    test.setImg("/home/adisteyf/2024-11-14_11-57.png", size_test);

    while (!glfwWindowShouldClose(window_main.getWindow())) {
        glfwPollEvents();

        glfwSwapBuffers(window_main.getWindow());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        shader.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    */

    window_main.kill();

    glfwDestroyWindow(window_main.getWindow());
    glfwTerminate();
    return 0;
}
