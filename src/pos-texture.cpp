// TODO: add includes
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class PosTexture
{
    private:
        Model model;
    public:
        void init(float w_orig, float h_orig)
        {
            GLfloat w = w_orig/100;
            GLfloat h = (h_orig+70)/100;
            GLfloat x = 0;
            GLfloat y = 0;

            GLfloat vertices[] =
            {
                x,     y,      0, // TOP LEFT     0
                x+w,   y,      0, // TOP RIGHT    1
                x+w,   y-h,    0, // BOTTOM RIGHT 2
                x,     y-h,    0, // BOTTOM LEFT  3
            };

            GLfloat texture[] =
            {
                0,0,
                1,0,
                1,1,
                0,1
            };

            GLint indices[] =
            {
                0,1,2,
                2,3,0
            };

            model.init(vertices, texture, indices);
        }

        void renderTexture(RenderTexture texture, GLfloat x, GLfloat y, Shader shader, glm::mat4 world, Camera cam)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            shader.bind();
            texture.bind(0);
            glm::mat4 tex_pos = glm::mat4().translate(glm::vec3(x, y-(y*(-70)/100), 0));
            glm::mat4 target = glm::mat4();

            cam.getProjection().mul(world, target);
            target.mul(tex_pos);
            shader.setUniform("sampler", 0);
            shader.setUniform("projection", 0);
            model.render();

            glDisable(GL_BLEND);
        }
};
