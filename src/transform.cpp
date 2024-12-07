// TODO: add includes

class Transform
{
    private:
        GLfloat x,y,x_limit, y_limit;
    public:
        GLloat sizeX,sizeY;
        // add RectCollider
        // TODO; <<;

        void init(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat x_limit, Glfloat y_limit)
        {
            this->x = x;
            this->y = y;
            this->sizeX = sizeX;
            this->sizeY = sizeY;
            this->x_limit = x_limit;
            this->y_limit = y_limit;

            for (Entity ent_in_gp : App.ents) {
                if (ent_in_gp.getComponent(RectCollider.class) != null) {
                    rc.add(ent_in_gp.getComponent(RectCollider.class));
                }
            }
        }
};
