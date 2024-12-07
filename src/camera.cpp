// TODO: add includes
#include <glm/glm.cppm>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    private:
        glm::vec3 pos;
        glm::mat4 projection;
        GLfloat zPos = 0;

    public:
        //Transform transform;

        void init(float x, float y, float sizeX, float sizeY)
        {
            //this->transform = transform;
            pos = glm::vec3(-x, -y, 0);
            projection = glm::ortho(-sizeX /2, sizeX /2, -sizeY /2, sizeY /2);
        }

        /*void init() // for scene manager
        {
            pos = glm::vec3(-x*SceneManager.scaleOfCam[0], -transform.getY()*SceneManager.scaleOfCam[0], -zPos);
        }*/

        void setZ(GLfloat z)
        {
            pos.z = z;
            zPos = z;
        }

        glm::vec3 getPosition() {return pos;}
        glm::mat4 getProjection()
        {
            glm::mat4 target;
            glm::mat4 pos;

            target = projection.mul(pos, target);
            return target;
        }
};
