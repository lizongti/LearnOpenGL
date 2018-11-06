#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Uniform
{
public:
    Uniform(ShaderProgram* shader_program):shader_program_(shader_program)
    {};

    virtual ~Uniform()
    {};

    // single value for int
    void Set(const std::string& name, int value)
    {
        glUniform1i(glGetUniformLocation(shader_program_->index(), name.c_str()), value); 
    };

    // single value for uint
    void Set(const std::string& name, unsigned int value)
    {
        glUniform1ui(glGetUniformLocation(shader_program_->index(), name.c_str()), value); 
    };

    // single value for float
    void Set(const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(shader_program_->index(), name.c_str()), value); 
    };

    //vec3
    void Set(const std::string& name, glm::vec3& value)
    {
        glUniform3f(glGetUniformLocation(shader_program_->index(), name.c_str()), value[0], value[1], value[2]);
    };

    // multiple vector for int
    void Set(const std::string& name, size_t element_num, size_t vector_num, const int* values)
    {
        switch(element_num)
        {
            case 1://vec1
                glUniform1iv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 2://vec2
                glUniform2iv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 3://vec3
                glUniform3iv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 4://vec4
                glUniform4iv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            default:
                std::cerr << "[SHADER] value num is not supported! shader program : " << shader_program_->index() << std::endl;
                return;           
        }
    };

    // multiple vector for uint
    void Set(const std::string& name, size_t element_num, size_t vector_num, const unsigned int* values)
    {
        switch(element_num)
        {
            case 1://vec1
                glUniform1uiv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 2://vec2
                glUniform2uiv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 3://vec3
                glUniform3uiv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 4://vec4
                glUniform4uiv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            default:
                std::cerr << "[SHADER] value num is not supported! shader progarm : " << shader_program_->index() << std::endl;
                return;           
        }
    };

    // multiple vector for float
    void Set(const std::string& name, size_t element_num, size_t vector_num, const float* values)
    {
        switch(element_num)
        {
            case 1://vec1
                glUniform1fv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 2://vec2
                glUniform2fv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 3://vec3
                glUniform3fv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            case 4://vec4
                glUniform4fv(glGetUniformLocation(shader_program_->index(), name.c_str()), vector_num, values);
                return;
            default:
                std::cerr << "[SHADER] value num is not supported! shader progarm : " << shader_program_->index() << std::endl;
                return;           
        }
    };

    //mutiple matrix for float 
    void Set(const std::string& name, size_t element_num, size_t matrix_num, glm::mat4 values)
    {
        switch(element_num)
        {
            case 2://vec2
                glUniformMatrix2fv(glGetUniformLocation(shader_program_->index(), name.c_str()), matrix_num, GL_FALSE, &values[0][0]);
                return;
            case 3://vec3
                glUniformMatrix3fv(glGetUniformLocation(shader_program_->index(), name.c_str()), matrix_num, GL_FALSE, &values[0][0]);
                return;
            case 4://vec4
                glUniformMatrix4fv(glGetUniformLocation(shader_program_->index(), name.c_str()), matrix_num, GL_FALSE, &values[0][0]);
                return;
            default:
                std::cerr << "[SHADER] value num is not supported! shader progarm : " << shader_program_->index() << std::endl;
                return;           
        }
    };

private:
    ShaderProgram* shader_program_;
};

#endif