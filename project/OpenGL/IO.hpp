#ifndef IO_HPP
#define  IO_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class IO
{
public:
    IO()
    {};

    virtual ~IO()
    {};

public:
    void Init(GLFWwindow* window)
    {
        window_ = window;
        glfwSetFramebufferSizeCallback(window_, IO::FrameBufferSizeCallback);
        glfwSetCursorPosCallback(window_, IO::MouseCallback);
        glfwSetScrollCallback(window_, IO::ScrollCallback);
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    };

    static void MouseCallback(GLFWwindow* window, double x_pos, double y_pos)
    {
        static bool first_mouse = true;
        static float last_x = 0.0f;
        static float last_y = 0.0f;

        if (first_mouse)
        {
            last_x = x_pos;
            last_y = y_pos;
            first_mouse = false;
        }

        float x_move = x_pos - last_x;
        float y_move =  -1 * (y_pos - last_y);

        last_x = x_pos;
        last_y = y_pos;

        Singleton<FPSMVP>::instance().Direction(x_move, y_move);
    }

    static void ScrollCallback(GLFWwindow* window, double x_move, double y_move)
    {
        
        Singleton<FPSMVP>::instance().Zoom(y_move);
    }

    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    };

    static void KeyboradPressedCallback(GLFWwindow* window, uint32_t key, float delta_time)
    {
        switch(key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_W:
            Singleton<FPSMVP>::instance().Move(FPSMVP::FORWARD, delta_time);
            break;
        case GLFW_KEY_S:
            Singleton<FPSMVP>::instance().Move(FPSMVP::BACKWARD, delta_time);
            break;
        case GLFW_KEY_A:
            Singleton<FPSMVP>::instance().Move(FPSMVP::LEFT, delta_time);
            break;
        case GLFW_KEY_D:
            Singleton<FPSMVP>::instance().Move(FPSMVP::RIGHT, delta_time);
            break;
        default:
            break;
        }
    };

    void ProcessInput()
    {
        static float last_process_time = 0;
        static float current_process_time = 0;
        static float delta_time = 0;

        last_process_time = current_process_time;
        current_process_time = glfwGetTime();

        if(last_process_time == 0)
        {
            delta_time = 0;
        }
        else
        {
            delta_time = current_process_time - last_process_time;
        }

        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            KeyboradPressedCallback(window_, GLFW_KEY_ESCAPE, delta_time);
        if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
            KeyboradPressedCallback(window_, GLFW_KEY_W, delta_time);
        if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
            KeyboradPressedCallback(window_, GLFW_KEY_S, delta_time);
        if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
            KeyboradPressedCallback(window_, GLFW_KEY_A, delta_time);
        if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
            KeyboradPressedCallback(window_, GLFW_KEY_D, delta_time);
    };
protected:
    GLFWwindow* window_;
    
};

#endif