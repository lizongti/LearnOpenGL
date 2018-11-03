#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

bool PrepareVertexs(VertexBuffer* vertex_buffer)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };  
    vertex_buffer->Import(vertices, sizeof(vertices));

    return true;
};

bool PrepareShaderProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/mvp.vert");
    shader_program->Collect("GLSL/mvp.frag");
    if(!shader_program->Build())
    {
        return false;
    }
    
    return true;
};

//===========================================================================
void ClearBuffer()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

//===========================================================
int main(int argc, char** argv)
{
    ShaderProgram* shader_program;
    VertexArray* vertex_array;
    Texture* texture1;
    Texture* texture2;
    float delta_time = 0;
    float last_time = 0;
    float current_time = 0;

    glm::vec3 cube_position[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    auto init = [&](GLFWwindow* window)
    {
        //set view port pos
        Singleton<IO>::instance().Init(window);
        // Build shader program
        shader_program = new ShaderProgram();
        PrepareShaderProgram(shader_program);

        // Perpare data as shader program's input
        vertex_array = new VertexArray();
        vertex_array->Work([&](){
            VertexBuffer* vertex_buffer = (VertexBuffer*)new TextureVertexBuffer();
            PrepareVertexs(vertex_buffer);
        });

        texture1 = (Texture*)new MipMapTexture();
        texture1->Import("Resource/container1.jpg");
        texture2 = (Texture*)new MipMapTexture();
        texture2->Import("Resource/awesomeface.png");
    };

    auto update = [&](GLFWwindow* window)
    {
        Singleton<IO>::instance().ProcessInput();

        shader_program->Use();

        texture1->Use(1);
        texture2->Use(2);

        Uniform(shader_program).Set("texture1", 1); // seperate use
        Uniform(shader_program).Set("texture2", 2);

        vertex_array->Work([&](){
            for (unsigned int i = 0; i < 10; i++)
            {
                Singleton<FPSMVP>::instance().ResetObject();
                Singleton<FPSMVP>::instance().MoveObjectAbs(cube_position[i]);
                Singleton<FPSMVP>::instance().RotateObjectAbs(glm::vec3(1.0f, 0.3f, 0.5f), 20.0f * i);
                Singleton<FPSMVP>::instance().ScaleObjectAbs(glm::vec3(1.1f, 1.1f, 1.1f));
                
                glm::mat4 value = Singleton<FPSMVP>::instance().Value();
                Uniform(shader_program).Set("mvp", 4, 1, value);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    auto fini = [&](GLFWwindow* window)
    {
        //noting
    };

    bool ret = true;
    ret = Singleton<Window>::instance().Initialize(init, update, fini);
    if(!ret)
    {
        printf("window init error");
        return -1;
    }

    ret = Singleton<Window>::instance().Run();
    if(!ret)
    {
        printf("window start error");
        return -1;
    }

    ret = Singleton<Window>::instance().Finalize();
    if(!ret)
    {
        printf("window stop error");
        return -1;
    }

    return 0;
}