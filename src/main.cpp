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
#include "fe-settings.h"

GLfloat lightVertices[] = {
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
    -0.1f,  0.1f,  0.1f,

    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7,
};

int fe_main() {
    log("fe_main(): initializing GLFW...");
    Window::initGLFW();
    log("fe_main(): initializing window...");
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    log("fe_main(): initializing model...");
    Model model;

    log("fe_main(): initializing shader...");
    Shader shader("shaders/shader_def.glsl");

    log("fe_main(): initializing light shader...");
    Shader lightShader("shaders/light_shader.glsl");

    log("fe_main(): initializing light buffers...");
    Buffers light;
    light.bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);
    light.makeAttrib(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    light.unbind();

    log("fe_main(): initializing light model...");
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    log("fe_main(): initializing pyramid model...");
    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    log("fe_main(): binding light shader...");
    lightShader.bind();
    log("fe_main(): setting light model...");
    lightShader.setUniform("model", lightModel);
    log("fe_main(): binding shader...");
    shader.bind();
    log("fe_main(): setting pyramid model...");
    shader.setUniform("model", pyramidModel);

    log("fe_main(): initializing texture...");
    Texture texture("assets/textures/logo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    log("fe_main(): setting texture unit...");
    texture.texUnit(shader, "tex0", 0);

    log("fe_main(): enabling depth test...");
    glEnable(GL_DEPTH_TEST);

    log("fe_main(): initializing camera...");
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    log("fe_main(): entering main loop...");
    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        camera.inputs(window.getWindow());
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        log("fe_main(): binding shader...");
        shader.bind();
        log("fe_main(): setting camera matrix...");
        camera.matrix(shader, "camMatrix");
        log("fe_main(): binding texture...");
        texture.bind();
        log("fe_main(): binding model...");
        model.bindBuff();
        log("fe_main(): drawing elements...");
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        log("fe_main(): binding light shader...");
        lightShader.bind();
        log("fe_main(): setting camera matrix...");
        camera.matrix(lightShader, "camMatrix");
        log("fe_main(): binding light buffers...");
        light.bind();
        log("fe_main(): drawing elements...");
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        window.swapBuffers();
    }

    log("fe_main(): exiting main loop (end of fe_main)...");
    return 0;
}

