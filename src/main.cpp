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

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        shader.bind();
        double time = glfwGetTime();
        double deltaTime = time - prevTime;

        if (deltaTime >= 1.0 / 60.0) {
            rotation += 1.0f;
            prevTime = time;
        }


        glm::mat4 model_matrix = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model_matrix = glm::rotate(model_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader.getProgram(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));

        int viewLoc = glGetUniformLocation(shader.getProgram(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1f(uniID, 0.5f);
        texture.bind();
        model.bindBuff();

        window.swapBuffers();
    }


    return 0;
}

