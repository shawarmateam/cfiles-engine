#include "window.h"
#include "shader.h"
#include "buffers.h"
#include "texture.h"
#include <cmath>
#include <vector>
#include "stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "model.h"
#include "camera.h"

int fe_main() {
    Window::initGLFW();
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    Model model;

    Shader shader("shaders/shader_def.glsl");

    Texture texture("assets/textures/logo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture.texUnit(shader, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        shader.bind();

        camera.inputs(window.getWindow());
        camera.matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

        texture.bind();
        model.bindBuff();

        window.swapBuffers();
    }


    return 0;
}

