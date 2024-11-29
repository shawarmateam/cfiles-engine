#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
    private:
        int w, h;
        std::string title = "Files Engine";
        GLFWwindow *window;

    public:
        static void error_callback(int error, const char* description) {
            std::cerr << "Error: " << description << std::endl;
        }


        void init()
        {
            w=600;
            h=600;

            glfwSetErrorCallback(Window::error_callback);
            
            if (!glfwInit()) {
                exit(1);
            }

            // Configure GLFW
            glfwDefaultWindowHints();
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Create the window
            window=glfwCreateWindow(w,h, title.c_str(), 0,0);
            
            if (!window) {
                glfwTerminate();
                exit(1);
            }

            // Get the thread stack & push a new frame
            /*try (MemoryStack stack = stackPush())
            {
                
            }*/

            // Settings
            glfwMakeContextCurrent(Window::window);
            glfwSwapInterval(1);
            glfwShowWindow(window);

            // Init GLEW
            if (glewInit() != GLEW_OK) {
                std::cerr << "Failed to initialize GLEW" << std::endl;
                exit(1);
            }
        }

        void kill()
        {
            // Free the window callbacks & destroy window
            //glfwFreeCallbacks();
            glfwDestroyWindow(Window::window);

            // Terminate GLFW & free the ERR callback
            glfwTerminate();
            glfwSetErrorCallback(0);
        }

        int getW() { return w; }
        int getH() { return h; }
        void setW(int new_w) { w=new_w; }
        void setH(int new_h) { h=new_h; }
        GLFWwindow* getWindow() { return window; }
};
