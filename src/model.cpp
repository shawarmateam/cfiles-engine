// TODO: add includes
#include <GL/gl.h>
#include <iostream>
#include <vector>

class Model
{
    private:
        GLuint draw_count,v_id,t_id,i_id;

    public:
        void init(GLfloat vertices[], GLuint size, GLfloat tex_coords[], GLuint tc_size, GLint indices[], GLuint draw_count)
        {
            LOG("Init of Model");
            glGenBuffers(1, &v_id);
            LOG("Buffers generated (v_id)");
            glBindBuffer(GL_ARRAY_BUFFER, v_id);
            LOG("GL_ARRAY_BUFFER was binded");
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
            LOG("GL_ARRAY_BUFFER was filled");

            LOG("In t_id");
            glGenBuffers(1, &t_id);
            glBindBuffer(GL_ARRAY_BUFFER, t_id);
            glBufferData(GL_ARRAY_BUFFER, tc_size, tex_coords, GL_STATIC_DRAW);

            LOG("In i_id");
            glGenBuffers(1, &i_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_id);

            LOG("Copying i_id to buffer");
            std::vector<GLint> buffer;
            buffer.reserve(draw_count);
            buffer.insert(buffer.end(), indices, indices+draw_count);

            LOG("GlBufferData");
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(int), buffer.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            LOG("End of Model.init()");
        }

        void render()
        {
            #ifndef DISABLE_MODEL_LOGS_FE
            LOG("In render of model");
            #endif
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, v_id);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);

            glBindBuffer(GL_ARRAY_BUFFER, t_id);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,0);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_id);
            glVertexAttribPointer(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, GL_FALSE, 0, (void *)0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, draw_count);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            #ifndef DISABLE_MODEL_LOGS_FE
            LOG("End of render model");
            #endif
        }
};
