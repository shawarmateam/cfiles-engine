#include <GL/gl.h>
#include <iostream>
#include <fstream>

class RenderTexture
{
    public:
        int w,h;
        GLuint id;

        std::string texture_path;

        unsigned char* loadImage(const std::string& filename, size_t& outSize) {
            std::ifstream file(filename, std::ios::binary);
            if (!file) {
                std::cerr << "Unable to open file: " << filename << std::endl;
                return nullptr;
            }

            file.seekg(0, std::ios::end);
            outSize = file.tellg();
            file.seekg(0, std::ios::beg);

            unsigned char* buffer = new unsigned char[outSize];
            if (!buffer) {
                std::cerr << "Unable to allocate memory" << std::endl;
                return nullptr;
            }

            file.read(reinterpret_cast<char*>(buffer), outSize);
            if (!file) {
                std::cerr << "Error during reading file" << std::endl;
                delete[] buffer;
                return nullptr;
            }

            file.close();
            return buffer;
        }

        void setImg(unsigned char *img_buff)
        {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_buff);
        }

        void setSize(int new_w, int new_h)
        {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, new_w, new_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        }

        void bind(int sampler)
        {
            if (sampler >= 0 && sampler <= 31)
            {
                glActiveTexture(GL_TEXTURE0 + sampler);
                glBindTexture(GL_TEXTURE_2D, id);
            }
        }

        int getW()  { return w; }
        int getH()  { return h; }
        int getId() { return id; }
};
