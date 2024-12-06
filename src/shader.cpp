// TODO: include libs
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <cstring>

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

    public:
        char* readFile(const char* filename) {
            std::ifstream file(filename, std::ios::binary | std::ios::ate);
            if (!file) {
                logerr("Unable to open the file");
                std::cout << filename << std::endl;
                exit(1);
            }

            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            char* buffer = new char[size + 1];

            if (!file.read(buffer, size)) {
                logerr("Error during reading the file");
                delete[] buffer;
                exit(1);
            }

            buffer[size] = 0;
            return buffer;
        }

        void splitShader(const char* shaderSource, char** vertexShader, char** fragmentShader)
        {
            const char* vertexPos = strstr(shaderSource, VERTEX_MARKER);
            const char* fragmentPos = strstr(shaderSource, FRAGMENT_MARKER);

            if (vertexPos == nullptr || fragmentPos == nullptr) {
                logerr("Unable to find marker(s)");
                exit(1);
            }

            size_t vertexLength = fragmentPos - vertexPos - VERTEX_MARKER_LEN;
            *vertexShader = new char[vertexLength + 1];
            strncpy(*vertexShader, vertexPos + VERTEX_MARKER_LEN, vertexLength);
            (*vertexShader)[vertexLength] = 0;

            size_t fragmentLength = strlen(fragmentPos + FRAGMENT_MARKER_LEN);
            *fragmentShader = new char[fragmentLength + 1];
            strncpy(*fragmentShader, fragmentPos + FRAGMENT_MARKER_LEN, fragmentLength);
            (*fragmentShader)[fragmentLength] = 0;

            // deleting space after marker comment
            std::string vertexNew(*vertexShader);
            vertexNew.erase(0,1);
            delete[] *vertexShader;
            *vertexShader = strdup(vertexNew.c_str());
        }

        void init(const char *filename)
        {
            const char *shader_str = readFile(filename);
            char *vertexCode = nullptr;
            char *fragmentCode = nullptr;

            splitShader(shader_str, &vertexCode, &fragmentCode);

            program = glCreateProgram();

            vs = glCreateShader(GL_VERTEX_SHADER);

            //          shader, str_num (if [], otherwise 1 (if char*)), idk
            glShaderSource(vs, 1, &vertexCode, 0);
            glCompileShader(vs);
            GLint status;

            glGetShaderiv(vs, GL_COMPILE_STATUS, &status);

            if (status != GL_TRUE)
            {
                logftl("UNABLE TO COMPILE SHADER (vs)");
                GLint logSize;
                glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logSize);
                std::vector<GLchar> infolog(logSize);

                glGetShaderInfoLog(vs, logSize, 0, infolog.data());
                std::cout << infolog.data() << std::endl;
                logftl("VERTEX CODE:");
                std::cout << '{' << vertexCode << '}' << std::endl;
                exit(1);
            }

            fs = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fs, 1, &fragmentCode, 0);
            glCompileShader(fs);

            glGetShaderiv(fs, GL_COMPILE_STATUS, &status);

            if (status != GL_TRUE)
            {
                logftl("UNABLE TO COMPILE SHADER (fs)");
                GLint logSize;
                glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logSize);
                std::vector<GLchar> infolog(logSize);

                glGetShaderInfoLog(vs, logSize, 0, infolog.data());
                std::cout << infolog.data() << std::endl;
                logftl("FRAGMENT CODE:");
                std::cout << fragmentCode << std::endl;
                exit(1);
            }

            glAttachShader(program, vs);
            glAttachShader(program, fs);

            glBindAttribLocation(program, 0, "vertices");
            glBindAttribLocation(program, 1, "textures");

            glLinkProgram(program);

            glGetProgramiv(program, GL_LINK_STATUS, &status);
            if (status != GL_TRUE)
            {
                logftl("UNABLE TO LINK SHADER PROGRAM");
                GLint logSize;
                glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logSize);
                std::vector<GLchar> infolog(logSize);

                glGetProgramInfoLog(program, logSize, 0, infolog.data());
                std::cout << infolog.data() << std::endl;
                exit(1);
            }

            glValidateProgram(program);
            glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

            if (status != GL_TRUE)
            {
                logftl("UNABLE TO VALIDATE SHADER PROGRAM");
                GLint logSize;
                glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logSize);
                std::vector<GLchar> infolog(logSize);

                glGetProgramInfoLog(program, logSize, 0, infolog.data());
                std::cout << infolog.data() << std::endl;
                exit(1);
            }
        }

        void bind()
        {
            glUseProgram(program);
        }

        void setUniformInt(char *name, int val)
        {
            int location = glGetUniformLocation(program, name);
            if (location != -1) glUniform1i(location, val);
        }

        void setUniform4f(char *name, glm::mat4 val)
        {
            int location = glGetUniformLocation(program, name);
            if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
        }

        void killShader()
        {
            glDeleteProgram(program);
        }
};
