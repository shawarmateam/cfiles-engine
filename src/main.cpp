#include "window.h"
#include "shader.h"
#include "texture.h"
#include <cmath>
#include <vector>
#include "stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "model.h"
#include "camera.h"
#include "fe-settings.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

GLfloat vertices[] = {
    // Position            // Color              // UV           // Normal
    -1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f,     0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f,-1.0f,     0.0f, 0.0f, 0.0f,     0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,-1.0f,     0.0f, 0.0f, 0.0f,     1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
};

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

GLfloat lightVertices[] = {
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,

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
    4, 6, 7
};



int fe_main() {
    felog("fe_main(): initializing GLFW...");
    Window::initGLFW();
    felog("fe_main(): initializing window...");
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    //Model model;



    felog("fe_main(): initializing shader...");
    Shader shader("shaders/shader_def.glsl");
    felog("fe_main(): initializing model...");

    VAO vao;
    vao.bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.makeAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    vao.makeAttrib(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.makeAttrib(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.makeAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    felog("fe_main(): initializing light shader...");
    Shader lightShader("shaders/light_shader.glsl");

    felog("fe_main(): initializing light buffers...");
    //Buffers light;
    //light.bind();

    VAO lightVAO;
    lightVAO.bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.makeAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    lightVAO.unbind();
    lightVBO.unbind();
    lightEBO.unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    felog("fe_main(): initializing light model...");
    glm::vec3 lightPos(1.0f, 1.0f, 1.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));

    felog("fe_main(): initializing pyramid model...");
    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    felog("fe_main(): binding light shader...");
    lightShader.bind();
    felog("fe_main(): setting light model...");
    lightShader.setUniform("model", lightModel);

    felog("fe_main(): setting light color...");
    glUniform4f(glGetUniformLocation(lightShader.getProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    felog("fe_main(): binding shader...");
    shader.bind();
    felog("fe_main(): setting pyramid model...");
    shader.setUniform("model", pyramidModel);

    glUniform4f(glGetUniformLocation(shader.getProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    felog("fe_main(): initializing texture...");
    Texture texture("assets/textures/wood.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    if (!texture.id) {
        felogftl("Failed to load texture");
        return -1;
    }

    felog("fe_main(): setting texture unit...");
    texture.texUnit(shader, "tex0", 0);

    Texture texture2("assets/textures/wood_ac.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    if (!texture2.id) {
        felogftl("Failed to load texture2");
        return -1;
    }

    texture2.texUnit(shader, "tex1", 1);

    felog("fe_main(): enabling depth test...");
    glEnable(GL_DEPTH_TEST);

    felog("fe_main(): initializing camera...");
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    felog("fe_main(): entering main loop...");
    while (!window.shouldClose() && !fe_status) {
        window.pollEvents();
        window.clear();

        camera.inputs(window.getWindow());
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        felog("fe_main(): binding shader...");
        shader.bind();
        glUniform3f(glGetUniformLocation(shader.getProgram(), "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);
        felog("fe_main(): setting camera matrix...");
        camera.matrix(shader, "camMatrix");

        felog("fe_main(): binding texture...");
        texture.bind();
        texture2.bind();
        felog("fe_main(): binding model...");
        vao.bind();
        felog("fe_main(): drawing elements...");
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

        felog("fe_main(): binding light shader...");
        lightShader.bind();
        felog("fe_main(): setting camera matrix...");
        camera.matrix(lightShader, "camMatrix");
        felog("fe_main(): binding light buffers...");
        lightVAO.bind();
        felog("fe_main(): drawing elements...");
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        felog("fe_main(): swapping buffers...");
        window.swapBuffers();
        felog("fe_main(): end of main loop");
    }

    felog("fe_main(): exiting main loop (end of fe_main)...");
    return 0;
}

