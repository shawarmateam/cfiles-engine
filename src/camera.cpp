// TODO: add includes

class Camera
{
    private:
        glm::vec3 pos;
        glm::mat4 projection;
        GLfloat zPos = 0;

    public:
        Transform transform;

        void init(Transform transform)
        {
            this->transform = transform;
            pos = glm::vec3(-transform.getX(), -transform.getY(), 0);
            projection = glm::mat4().setOrtho2D(-transform.sizeX /2, transform.sizeX /2, -transform.sizeY /2, transform.sizeY /2);
        }

        void init() // for scene manager
        {
            pos = glm::vec3(-transform.getX()*SceneManager.scaleOfCam[0], -transform.getY()*SceneManager.scaleOfCam[0], -zPos);
        }

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
