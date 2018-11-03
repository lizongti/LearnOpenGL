#ifndef SHADER_HPP
#define SHADER_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Shader
{
public:
    Shader()
    {};

    virtual ~Shader()
    {};

    virtual bool Compile(const std::string& gl_code)
    {
        gl_code_ = gl_code;
        size_t length = strlen(gl_code_.c_str());
        char* buffer = new char[length + 1];
        buffer[length] = '\0';
        memcpy(buffer, gl_code_.c_str(), length);

        glShaderSource(shader_, 1, (const GLchar **)&buffer, 0);
        glCompileShader(shader_);

        int  success;
        char infoLog[512];
        glGetShaderiv(shader_, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader_, 512, 0, infoLog);
            std::cout << "[SHADER] compile failed! shader : " << shader_ << ", " << infoLog << std::endl;

            return false;
        }

        compiled_ = true;
        return true;
    };

public:
    bool compiled()
    {
        return compiled_;
    };

    std::string suffix()
    {
        return suffix_;
    };

    unsigned int index()
    {
        return shader_;
    };

protected:
    unsigned int shader_;
    bool compiled_ = false;
    std::string gl_code_;
    std::string suffix_;
};

class VertexShader : public Shader
{
public:
    VertexShader():Shader()
    {
        shader_ = glCreateShader(GL_VERTEX_SHADER);
        suffix_ = ".vert";
    };

    virtual ~VertexShader()
    {
        glDeleteShader(shader_);
    };
};

class FragmentShader : public Shader
{
public:
    FragmentShader():Shader()
    {
        shader_ = glCreateShader(GL_FRAGMENT_SHADER);
        suffix_ = ".frag";
    };

    virtual ~FragmentShader()
    {
        glDeleteShader(shader_);
    };
};

class ShaderProgram
{
public:
    ShaderProgram()
    {
        shader_program_ = glCreateProgram();
    };

    virtual ~ShaderProgram()
    {
        for(auto shader_iter : shader_map_)
        {
            Shader* shader = shader_iter.second;
            delete shader;
        }
    };

    virtual bool Collect(const std::string& path_file)
    {
        shader_source_list_.push_back(path_file);

        return true;
    };

    virtual bool Build()
    {
        bool ret = false;
        
        for(auto source_path_file : shader_source_list_)
        {
            ret = Compile(source_path_file);
            if(!ret)
            {
                std::cerr << "[SHADER] build error! shader_program : " << shader_program_ << ", file : " << source_path_file << std::endl;
                return false;
            }
        }

        ret = Link();
        if(!ret)
        {
            std::cerr << "[SHADER] link error! shader program : " << shader_program_ << std::endl;
            return false;
        }

        return true;
    };

    virtual bool Use()
    {
        glUseProgram(shader_program_);
        return true;
    };

protected:
    virtual bool Compile(std::string& path_file)
    {
        bool ret = false;

        std::ifstream ifstream(path_file);
        std::string gl_code((std::istreambuf_iterator<char>(ifstream)),
                        std::istreambuf_iterator<char>());

        Shader* shader;
        if(boost::ends_with(path_file, ".vert") && shader_map_.find(".vert") == shader_map_.end())
        {
            shader = new VertexShader();
        }
        else if(boost::ends_with(path_file, ".frag") && shader_map_.find(".frag") == shader_map_.end())
        {
            shader = new FragmentShader();
        }
        else
        {
            std::cerr << "[SHADER] suffix not match shader! shader_program : " << shader_program_ << std::endl;
            return false;
        }

        ret = shader->Compile(gl_code);
        if(!ret)
        {
            return false;
        }

        shader_map_.insert(std::make_pair(shader->suffix(), shader));

        return true;
    }

    virtual bool Link()
    {
        for(auto shader_iter : shader_map_)
        {
            auto shader = shader_iter.second;
            if(shader->compiled())
            {
                glAttachShader(shader_program_, shader->index());
            }
            else
            {
                std::cerr << "[SHADER] shader not built before link! shader_program : " << shader_program_ << ", shader : " << shader->index() << std::endl;
            }
        }
        glLinkProgram(shader_program_);

        int  success;
        char infoLog[512];
        glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
        if(!success) 
        {
            glGetProgramInfoLog(shader_program_, 512, 0, infoLog);
            std::cout << "[SHADER] linke error! shader_program : " << shader_program_ << ", " << infoLog << std::endl;
            return false;
        }

        return true;
    };

public:
    unsigned int index(){ return shader_program_; };

protected:
    std::list<std::string> shader_source_list_;
    std::map<std::string, Shader*> shader_map_;
    unsigned int shader_program_;
};
#endif