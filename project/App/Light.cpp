#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

void PrepareObjectsVertexs(VertexBuffer* vertex_buffer)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };  
    vertex_buffer->Import(vertices, sizeof(vertices));
};

void UpdateLightsShader(ShaderProgram* shader_program)
{
    float directional_data[] = {
        -0.2f, -1.0f, -0.3f,
        0.05f, 0.05f, 0.05f,
        0.4f, 0.4f, 0.4f,
        0.5f, 0.5f, 0.5f
    };

    float point_data[] = {
        0.7f,  0.2f,  2.0f,
        0.05f, 0.05f, 0.05f,
        0.8f, 0.8f, 0.8f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.09f, 0.032f,

        2.3f, -3.3f, -4.0f,
        0.05f, 0.05f, 0.05f,
        0.8f, 0.8f, 0.8f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.09f, 0.032f,

        -4.0f,  2.0f, -12.0f,
        0.05f, 0.05f, 0.05f,
        0.8f, 0.8f, 0.8f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.09f, 0.032f,

        0.0f,  0.0f, -3.0f,
        0.05f, 0.05f, 0.05f,
        0.8f, 0.8f, 0.8f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.09f, 0.032f,        
    };

    float spot_data[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.09f, 0.032f,
        12.5f, 15.0f
    };

    float material_data[] = {
        1, 2, 32.0f
    };

    static uint32_t pos = 0;
    static float* data = nullptr;
    auto next = [&](){ return data[pos++]; };
    auto reset = [&](float* d){ pos = 0; data = d;};

    // direction light
    std::vector<Light::Directional> directional_vector;
    reset(directional_data);
    for (auto index = 0; index < sizeof(directional_data) / 12; ++index)
    {
        Light::Directional directional;
        directional.direction = glm::vec3(next(), next(), next());
        directional.ambient = glm::vec3(next(), next(), next());
        directional.diffuse = glm::vec3(next(), next(), next());
        directional.specular = glm::vec3(next(), next(), next());
        directional_vector.push_back(directional);
    }

    // point light
    std::vector<Light::Point> point_vector;
    reset(point_data);
    for (auto index = 0; index < sizeof(point_data) / 20; ++index)
    {
        Light::Point point;
        point.position = glm::vec3(next(), next(), next());
        point.ambient = glm::vec3(next(), next(), next());
        point.diffuse = glm::vec3(next(), next(), next());
        point.specular = glm::vec3(next(), next(), next());
        point.constant = next();
        point.linear = next();
        point.quadratic = next();
#ifdef USE_GAMMA_CORRECTION
        point.constant = 0;
        point.linear = 1;
        point.quadratic = 0;
#endif
        point_vector.push_back(point);
    }

    std::vector<Light::Spot> spot_vector;
    reset(spot_data);
    for (auto index = 0; index < sizeof(spot_data) / 20; ++index)
    {
        Light::Spot spot;
        spot.position = glm::vec3(next(), next(), next());
        spot.direction = glm::vec3(next(), next(), next());
        spot.ambient = glm::vec3(next(), next(), next());
        spot.diffuse = glm::vec3(next(), next(), next());
        spot.specular = glm::vec3(next(), next(), next());
        spot.constant = next();
        spot.linear = next();
        spot.quadratic = next();
#ifdef USE_GAMMA_CORRECTION
        spot.constant = 0;
        spot.linear = 1;
        spot.quadratic = 0;
#endif
        spot.cutOff = glm::cos(glm::radians(next()));
        spot.outerCutOff = glm::cos(glm::radians(next()));
        spot_vector.push_back(spot);
    }

    reset(material_data);
    Light::Material material;
    material.diffuse = (int)next();
    material.specular = (int)next();
    material.shininess = next();

    shader_program->Use();
    Light(shader_program).SetViewPos(Singleton<FPSMVP>::instance().camera_pos());
    Light(shader_program).SetMaterial(material);
    Light(shader_program).SetDirectionalLight(directional_vector);
    Light(shader_program).SetPointLight(point_vector);    
    Light(shader_program).SetSpotLight(spot_vector); 
};

void PrepareShaderProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/light.vert");
    shader_program->Collect("GLSL/light.frag");
    shader_program->Build();
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
    VertexArray* objects_vao; 
    VertexArray* lights_vao;
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
        // objects
        objects_vao = new VertexArray();
        objects_vao->Work([&](){
            PrepareObjectsVertexs((VertexBuffer*)new TextureNormalVertexBuffer());
        });

        texture1 = (Texture*)new MipMapTexture();
        texture1->Import("Resource/container2.png");
        texture2 = (Texture*)new MipMapTexture();
        texture2->Import("Resource/container2_specular.png");
    };

    auto update = [&](GLFWwindow* window)
    {
        Singleton<IO>::instance().ProcessInput();

        shader_program->Use();

        UpdateLightsShader(shader_program);

        texture1->Use(1);
        texture2->Use(2);

        objects_vao->Work([&](){
            for (unsigned int i = 0; i < 10; i++)
            {
                Singleton<FPSMVP>::instance().ResetObject();
                Singleton<FPSMVP>::instance().MoveObjectAbs(cube_position[i]);
                Singleton<FPSMVP>::instance().RotateObjectAbs(glm::vec3(1.0f, 0.3f, 0.5f), 20.0f * i);
                Singleton<FPSMVP>::instance().ScaleObjectAbs(glm::vec3(1.1f, 1.1f, 1.1f));
                
                glm::mat4 value = Singleton<FPSMVP>::instance().Value();
                Uniform(shader_program).Set("model", 4, 1, Singleton<FPSMVP>::instance().model());
                Uniform(shader_program).Set("view", 4, 1, Singleton<FPSMVP>::instance().view());
                Uniform(shader_program).Set("projection", 4, 1, Singleton<FPSMVP>::instance().projection());
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    auto fini = [&](GLFWwindow* window)
    {
        //can do free staff here 
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