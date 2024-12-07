#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.cpp"
#include "fe-kernel.h"
#include "shader.cpp"
#include "camera.cpp"
#include "render-texture.cpp"
#include "pos-texture.cpp"
#include "transform.cpp"

Camera cam;
Window window_main;

void run()
{
    std::cout << "Starting files engine..." << std::endl;
    window_main.init();
    
    Transform cam_pos;
    cam_pos.x = 0;
    cam_pos.y = 0;
    cam_pos.w = 600;
    cam_pos.h = 600;
    cam_pos.x_limit = 1000;
    cam_pos.y_limit = 1000;
    
    cam.init(cam_pos); // TODO: add transform
    glEnable(GL_TEXTURE_2D);
}

int loop()
{
    glViewport(0,0,600,600);

    Shader shader;
    shader.init("shaders/shader_def.glsl");
    glm::mat4 projection = glm::ortho(cam.transform.w/2, -cam.transform.w/2, cam.transform.h/2, -cam.transform.h/2);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::translate(scale, glm::vec3(.0f, .0f, .0f));
    scale = glm::scale(scale, glm::vec3(80.f, 80.f, 80.f));

    RenderTexture test;
    size_t size_test=0;
    test.setImg("/home/adisteyf/2024-11-10_11-20.png", size_test);

    PosTexture pos_test;
    pos_test.init(1365, 485);

    while (!glfwWindowShouldClose(window_main.getWindow())) {
        glfwPollEvents();

        glfwSwapBuffers(window_main.getWindow());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        pos_test.renderTexture(test, 0, 0, shader, scale, cam);

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
