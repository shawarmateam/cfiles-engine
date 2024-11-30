// TODO: include libs
#include <iostream>


#define RED "\033[31m"
#define RESET "\033[0m"
#define logftl(msg) std::cerr << RED "FE_FATAL: " msg RESET << std::endl
#define logerr(msg) std::cerr << RED "FE_ERROR: " RESET msg << std::endl

class Shader
{
    private:
        GLuint program,vs,fs;
        bool startReadFragment;

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

        void init(const char *filename)
        {
            const char *shader_str = readfile(filename);
            program = glCreateProgram();

            vs = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vs, shader_str);
            glCompileShader(vs);
            if (glGetShaderi(vs, GL_COMPILE_STATUS) != 1)
            {
                logftl("UNABLE TO COMPILE SHADER");
                std::cout << glGetShaderInfoLog(vs) << std::endl;
                exit(1);
            }

            fs = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fs, shader_str);
            glCompileShader(fs);
            if (glGetShaderi(fs, GL_COMPILE_STATUS) != 1)
            {
                logftl("UNABLE TO COMPILE SHADER");
                std::cout << glGetShaderInfoLog(fs) << std::endl;
                exit(1);
            }

            glAttachShader(program, vs);
            glAttachShader(program, fs);

            glBindAttribLocation(program, 0, "vertices");
            glBindAttribLocation(program, 1, "textures");

            glLinkProgram(program);
            if (glGetProgrami(program, GL_LINK_STATUS) != 1)
            {
                logftl("UNABLE TO LINK SHADER PROGRAM");
                std::cout << glGetProgramInfoLog(program) << std::endl;
                exit(1);
            }

            glValidateProgram(program);
            if (glGetProgrami(program, GL_VALIDATE_STATUS) != 1)
            {
                logftl("UNABLE TO VALIDATE SHADER PROGRAM");
                std::cout << glGetProgramInfoLog(program) << std::endl;
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

        void setUniform4f(char *name, Matrix4f val)
        {
            int location = glGetUniformLocation(program, name);
            FloatBuffer buffer = BufferUtils.createFloatBuffer(16);
            val.get(buffer);
            if (location != -1) glUniformMatrix4fv(location, false, buffer);
        }
};
