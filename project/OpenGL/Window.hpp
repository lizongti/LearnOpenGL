#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Window
{
public:
    Window(){};

    typedef std::function<void(GLFWwindow*)> CallbackFunc;

    bool Initialize(CallbackFunc init_cb, CallbackFunc update_cb, CallbackFunc fini_cb)
    {
        init_cb_ = init_cb;
        update_cb_ = update_cb;
        fini_cb_ = fini_cb;

        /* Initialize the library */
        if (!glfwInit())
        {
            return false;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        /* Create a windowed mode window and its OpenGL context */
        window_ = glfwCreateWindow(800, 600, "Welome to opengl project", NULL, NULL);
        if (!window_)
        {
            glfwTerminate();
            return false;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window_);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "[Window]Failed to initialize GLAD" << std::endl;
        }

        glEnable(GL_DEPTH_TEST);

#ifdef USE_CULL_FACE
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);
#endif

        init_cb_(window_);
        
      return true;
    };

    bool Run()
    {
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window_))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

            update_cb_(window_);

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }

        return true;
    };

    bool Finalize()
    {
        glfwTerminate();
        return 0;
    };

private:
    GLFWwindow* window_ = nullptr;
    CallbackFunc init_cb_;
    CallbackFunc update_cb_;
    CallbackFunc fini_cb_;
};

#endif