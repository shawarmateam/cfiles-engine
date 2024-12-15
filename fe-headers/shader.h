#ifndef SHADER_CLASS_FE
#define SHADER_CLASS_FE

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "fe-kernel.h"

#define RED "\033[31m"
#define RESET "\033[0m"
#define logftl(msg) std::cerr << RED "FE_FATAL: " msg RESET << std::endl
#define logerr(msg) std::cerr << RED "FE_ERROR: " RESET msg << std::endl
#define VERTEX_MARKER "// vertex shader"
#define FRAGMENT_MARKER "// fragment shader"
#define VERTEX_MARKER_LEN 16
#define FRAGMENT_MARKER_LEN 18

class Shader
{
    private:
        GLuint program,vs,fs;
        void splitShader(const char* shaderSource, char** vertexShader, char** fragmentShader);

    public:
        char* readFile(const char* filename);
        Shader(const char* filename);
        void bind();
        void setUniform(const char *name, int val);
        void setUniform(const char *name, glm::mat4 val);
        void killShader();
        void freeShader();
        GLuint getProgram();
};

#endif // SHADER_CLASS_FE
