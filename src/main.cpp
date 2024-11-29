#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.cpp"

int main()
{
    Window window_main;
    window_main.init();

    while (!glfwWindowShouldClose(window_main.getWindow())) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window_main.getWindow());
        glfwPollEvents();
    }

    window_main.kill();

    glfwDestroyWindow(window_main.getWindow());
    glfwTerminate();
    return 0;
}

