#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class VertexArray
{
public:
    typedef std::function<void(void)> HandleFunc;

    VertexArray()
    {
        glGenVertexArrays(1, &vertex_array_object_);
    };

    virtual ~VertexArray()
    {
        glDeleteVertexArrays(1, &vertex_array_object_);
    };

    void Work(HandleFunc handle_func)
    {
        glBindVertexArray(vertex_array_object_);
        handle_func();
        glBindVertexArray(0);
    };

protected:
    unsigned int vertex_array_object_;
};

#endif