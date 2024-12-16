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
    glm::vec3 pos;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    int w,h;

    float speed = 0.1f;
    float sensitivity = 100.0f;
    float fov;
    float near_plane;
    float far_plane;
    
    Camera(int w, int h, glm::vec3 pos);
    ~Camera();

    void matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform);
    void inputs(GLFWwindow *window);
};

#endif