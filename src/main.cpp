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

int fe_main() {
    Window::initGLFW();
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    Model model;

    Shader shader("shaders/shader_def.glsl");
    const GLuint uniID = glGetUniformLocation(shader.getProgram(), "scale");

    Texture texture("assets/textures/logo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture.texUnit(shader, "tex0", 0);

    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        shader.bind();
        glUniform1f(uniID, 0.5f);
        texture.bind();
        model.bindBuff();

        window.swapBuffers();
    }


    return 0;
}

