// TODO: add includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "transform.cpp"

class Camera
{
    private:
        glm::vec3 pos;
        glm::mat4 projection;
        float zPos = 0;

    public:
        Transform transform;

        void init(Transform new_transform)
        {
            this->transform = new_transform;
            pos = glm::vec3(-this->transform.x, -this->transform.y, 0);
            projection = glm::ortho(-this->transform.w /2, this->transform.w /2, -this->transform.h /2, this->transform.h /2);
        }

        /*void init() // for scene manager
        {
            pos = glm::vec3(-x*SceneManager.scaleOfCam[0], -transform.getY()*SceneManager.scaleOfCam[0], -zPos);
        }*/

        void setZ(float z)
        {
            pos.z = z;
            zPos = z;
        }

        glm::vec3 getPosition() {return pos;}
        glm::mat4 getProjection()
        {
            glm::mat4 target;
            glm::mat4 pos;

            target = pos + target;
            return target;
        }
};
