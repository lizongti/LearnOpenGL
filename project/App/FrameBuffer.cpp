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

void PrepareObjectsModelVertexs(VertexBuffer* vertex_buffer)
{
    //prepare model mat4
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

    uint32_t model_num = sizeof(cube_position) / sizeof(glm::vec3);
        
    glm::mat4* model_array = new glm::mat4[model_num];
    for (unsigned int i = 0; i < model_num; i++)
    {
        Singleton<FPSMVP>::instance().ResetObject();
        Singleton<FPSMVP>::instance().MoveObjectAbs(cube_position[i]);
        Singleton<FPSMVP>::instance().RotateObjectAbs(glm::vec3(1.0f, 0.3f, 0.5f), 20.0f * i);
        Singleton<FPSMVP>::instance().ScaleObjectAbs(glm::vec3(1.1f, 1.1f, 1.1f));
            
        model_array[i] = Singleton<FPSMVP>::instance().model();
    }
    vertex_buffer->Import(&model_array[0], model_num * sizeof(glm::mat4));
};

void PrepareSkyboxVertexs(VertexBuffer* vertex_buffer)
{
   float vertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    }; 
    for (auto i = 0; i < sizeof(vertices) / 4; ++i)
    {
        vertices[i] *= 100;
    }
    vertex_buffer->Import(vertices, sizeof(vertices));
};

void PrepareTransparentVertexs(VertexBuffer* vertex_buffer)
{
    float vertices[] = {
        0.0f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        0.0f, -0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 0.0f,  1.0f,
        1.0f, -0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 1.0f,  1.0f,

        0.0f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        1.0f, -0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 1.0f,  1.0f,
        1.0f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 1.0f,  0.0f
    };
    vertex_buffer->Import(vertices, sizeof(vertices));
};

void PrepareTransparentModelVertexs(VertexBuffer* vertex_buffer)
{
    //prepare model mat4, from far to near
    //对于不规则的透明物体或者透明面来说，不能采用如此简单的计算方法， 这个只是静态模拟，切换视角后就会出错。
    glm::vec3 unsorted_windows_position[] = {
        glm::vec3( 1.5f, 0.0f, 0.51f),
        glm::vec3( 0.0f, 0.0f, 0.7f),
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3( 0.5f, 0.0f, -0.6f)
    };
    uint32_t model_num = sizeof(unsorted_windows_position) / sizeof(glm::vec3);

    std::map<float, glm::vec3> sorted_windows_position;
    for (uint32_t index = 0; index < model_num; ++index)
    {
        float distance = glm::length(Singleton<FPSMVP>::instance().camera_pos() - unsorted_windows_position[index]);
        sorted_windows_position[distance] = unsorted_windows_position[index];
    }
    glm::vec3 windows_position[model_num];
    uint32_t start = model_num;
    for (auto val : sorted_windows_position)
    {
        windows_position[--start] = val.second;
    }
        
    glm::mat4* model_array = new glm::mat4[model_num];
    for (unsigned int i = 0; i < model_num; i++)
    {
        Singleton<FPSMVP>::instance().ResetObject();
        Singleton<FPSMVP>::instance().MoveObjectAbs(windows_position[i]);
            
        model_array[i] = Singleton<FPSMVP>::instance().model();
    }
    vertex_buffer->Import(&model_array[0], model_num * sizeof(glm::mat4));
};

void PrepareScreenVertexArray(VertexBuffer* vertex_buffer)
{
    float vertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    vertex_buffer->Import(vertices, sizeof(vertices));
};

void UpdateObjectsShader(ShaderProgram* shader_program)
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

void PrepareObjectsShaderProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/instance.vert");
    shader_program->Collect("GLSL/instance.frag");
    shader_program->Build();
};

void PrepareSkyboxShaderProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/skybox.vert");
    shader_program->Collect("GLSL/skybox.frag");
    shader_program->Build();
};

void PrepareScreenShaderProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/screen.vert");
    shader_program->Collect("GLSL/screen.frag");
    shader_program->Build();
};

void PrepareTransparentProgram(ShaderProgram* shader_program)
{
    shader_program->Collect("GLSL/blend.vert");
    shader_program->Collect("GLSL/blend.frag");
    shader_program->Build();
};

//===========================================================
int main(int argc, char** argv)
{
    ShaderProgram* objects_shader_program;
    ShaderProgram* skybox_shader_program;
    ShaderProgram* transparent_shader_program;
    ShaderProgram* screen_shader_program;
    VertexArray* objects_vao; 
    VertexArray* skybox_vao;
    VertexArray* transparent_vao;
    VertexArray* screen_vao;
    Texture* texture0;
    Texture* texture1;
    Texture* texture2;
    Texture* texture3;

    Frame* frame;

    float delta_time = 0;
    float last_time = 0;
    float current_time = 0;
    
    auto init = [&](GLFWwindow* window)
    {
        // Set view port pos
        Singleton<IO>::instance().Init(window);

        // Build shader program
        objects_shader_program = new ShaderProgram();
        PrepareObjectsShaderProgram(objects_shader_program);
        skybox_shader_program = new ShaderProgram();
        PrepareSkyboxShaderProgram(skybox_shader_program);
        transparent_shader_program = new ShaderProgram();
        PrepareTransparentProgram(transparent_shader_program);
        screen_shader_program = new ShaderProgram();
        PrepareScreenShaderProgram(screen_shader_program);

        // Set vertex array object
        objects_vao = new VertexArray();
        objects_vao->Work([&](){
            PrepareObjectsVertexs((VertexBuffer*)new TextureNormalVertexBuffer());
            PrepareObjectsModelVertexs((VertexBuffer*)new TextureModelInstanceVertexBuffer());
        });
        skybox_vao = new VertexArray();
        skybox_vao->Work([&](){
            PrepareSkyboxVertexs((VertexBuffer*)new VertexBuffer());
        });
        transparent_vao = new VertexArray();
        transparent_vao->Work([&](){
            PrepareTransparentVertexs((VertexBuffer*)new TextureNormalVertexBuffer());
            PrepareTransparentModelVertexs((VertexBuffer*)new TextureModelInstanceVertexBuffer());
        });
        screen_vao = new VertexArray();
        screen_vao->Work([&](){
            PrepareScreenVertexArray((VertexBuffer*)new FrameArrayBuffer());
        });

        // Set Texture
        texture0 = (Texture*)new CubeTexture();
        texture0->Import("Resource/skybox/%s.jpg");
        texture1 = (Texture*)new MipMapTexture();
        texture1->Import("Resource/container2.png");
        texture2 = (Texture*)new MipMapTexture();
        texture2->Import("Resource/container2_specular.png");
        texture3 = (Texture*)new TransparentTexture();
        texture3->Import("Resource/window.png");

        //init Frame
        frame = new Frame();
        frame->AttachTexture();
        frame->AttachRenderBuffer();
    };

    auto update = [&](GLFWwindow* window)
    {
        Singleton<IO>::instance().ProcessInput();

        frame->Work([&](){
            //==================== objects ===================
            objects_shader_program->Use();
            UpdateObjectsShader(objects_shader_program);

            texture1->Use(1);
            texture2->Use(2);

            
            objects_vao->Work([&](){
                Uniform(objects_shader_program).Set("view", 4, 1, Singleton<FPSMVP>::instance().view());
                Uniform(objects_shader_program).Set("projection", 4, 1, Singleton<FPSMVP>::instance().projection());
                glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10);
            });

            //==================== skybox ===================
            glDepthFunc(GL_LEQUAL); 
            skybox_shader_program->Use();

            texture0->Use(0);

            skybox_vao->Work([&](){
                Uniform(skybox_shader_program).Set("skybox", 0);
                Uniform(skybox_shader_program).Set("view", 4, 1, Singleton<FPSMVP>::instance().view());
                Uniform(skybox_shader_program).Set("projection", 4, 1, Singleton<FPSMVP>::instance().projection());
                glDrawArrays(GL_TRIANGLES, 0, 36);         
            });  
            glDepthFunc(GL_LESS); 

            //===================== transparent =====================
            transparent_shader_program->Use();

            texture3->Use(1);

            transparent_vao->Work([&](){
                Uniform(transparent_shader_program).Set("transparent", 1);
                Uniform(transparent_shader_program).Set("view", 4, 1, Singleton<FPSMVP>::instance().view());
                Uniform(transparent_shader_program).Set("projection", 4, 1, Singleton<FPSMVP>::instance().projection());
                glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 5);
            });
        });

        frame->DefaultWork([&](){
            screen_shader_program->Use();

            frame->Use(1);

            screen_vao->Work([&](){
                Uniform(screen_shader_program).Set("screenTexture", 1);
                 
                glDrawArrays(GL_TRIANGLES, 0, 6);
            });
        });

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