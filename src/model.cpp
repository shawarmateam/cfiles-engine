// TODO: add includes
#include <GL/gl.h>
#include <iostream>
#include <vector>

class Model
{
    private:
        GLint draw_count,v_id,t_id,i_id;

    public:
        void init(GLfloat[] vertices, GLfloat[] tex_coords, GLint[] indices)
        {
            draw_count = sizeof(indices) / sizeof(indices[0]);

            v_id = glGenBuffers();
            glBindBuffer(GL_ARRAY_BUFFER, v_id);
            glBufferData(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);

            t_id = glGenBuffers();
            glBindBuffer(GL_ARRAY_BUFFER, t_id);
            glBufferData(GL_ARRAY_BUFFER, tex_coords, GL_STATIC_DRAW);

            i_id = glGenBuffers();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_id);

            std::vector<GLint> buffer;
            buffer.reserve(draw_count);
            buffer.insert(buffer.end(), indices, indices+draw_count);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void render()
        {
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, v_id);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);

            glBindBuffer(GL_ARRAY_BUFFER, t_id);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,0);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_id);
            glVertexAttribPointer(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, draw_count);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }
};
