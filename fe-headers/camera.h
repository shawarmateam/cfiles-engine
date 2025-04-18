#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "shader.h"

class Camera {
public:
    int w, h;
    glm::vec3 pos;
    glm::vec3 orientation = glm::vec3(0.1f, -0.4f, 0.9f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.f);
    glm::mat4 view = glm::mat4(1.f);

    float speed = 0.1f;
    float sensitivity = 50.0f;
    float fov;
    float near_plane;
    float far_plane;
    bool showImGui = false;

    Camera(int w, int h, glm::vec3 pos, float FOVdeg, float near, float far) : w(w), h(h), pos(pos), fov(FOVdeg), near_plane(near), far_plane(far) {}

    void updateMatrix(void);
    void matrix(Shader &shader, const char *uniform);
};

#endif
