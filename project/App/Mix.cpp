#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

bool PrepareVertexs(VertexBuffer* vertex_buffer)
{
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    vertex_buffer->Import(vertices, sizeof(vertices));

    return true;
};

bool PrepareIndices(IndiceBuffer* indice_buffer)
{
    uint32_t indices[] = {
        0, 1, 3, 
        1, 2, 3
    };
    indice_buffer->Import(indices, sizeof(indices));

    return true;
};

bool PrepareShaderProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/mix.vert");
    shader_program->Collect("GLSL/mix.frag");
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
    glClear(GL_COLOR_BUFFER_BIT);
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};

void SetViewPort(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
};

int main(int argc, char** argv)
{
    ShaderProgram* shader_program;
    VertexArray* vertex_array;
    Texture* texture1;
    Texture* texture2;
    
    auto init = [&](GLFWwindow* window){
        //set view port pos
        SetViewPort(window);

        // Build shader program
        shader_program = new ShaderProgram();
        PrepareShaderProgram(shader_program);

        // Perpare data as shader program's input
        vertex_array = new VertexArray();
        vertex_array->Work([&](){
            VertexBuffer* vertex_buffer = (VertexBuffer*)new TextureColorVertexBuffer();
            PrepareVertexs(vertex_buffer);

            IndiceBuffer* indice_buffer = new IndiceBuffer();
            PrepareIndices(indice_buffer);
        });

        texture1 = (Texture*)new MipMapTexture();
        texture1->Import("Resource/container1.jpg");
        texture2 = (Texture*)new MipMapTexture();
        texture2->Import("Resource/awesomeface.png");
    };

    auto update = [&](GLFWwindow* window){
        //process input before draw
        ProcessInput(window);

        //clear buffer befefore draw
        ClearBuffer();

        shader_program->Use();

        texture1->Use(1);
        texture2->Use(2);

        Uniform(shader_program).Set("texture1", 1); // seperate use
        Uniform(shader_program).Set("texture2", 2);

        // Draw output
        vertex_array->Work([&](){
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    auto fini = [&](GLFWwindow* window){
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