#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Light
{
public:
    Light(ShaderProgram* shader_program) : shader_program_(shader_program)
    {};
    virtual ~Light()
    {};

    struct Material
    {

        int diffuse; // texture id
        int specular; // texture id

        float shininess;
    };

    struct Directional
    {
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct Point
    {
        glm::vec3 position;
        
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;
    };

    struct Spot
    {
        glm::vec3 position;
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;

        float cutOff;
        float outerCutOff;
    };

public:
    void SetViewPos(glm::vec3 viewPos)
    {
        Uniform(shader_program_).Set("viewPos", viewPos);
    };

    void SetMaterial(Material& material)
    {
        std::string head = "material.";
        Uniform(shader_program_).Set(head + "diffuse", material.diffuse);
        Uniform(shader_program_).Set(head + "specular", material.specular);
        Uniform(shader_program_).Set(head + "shininess", material.shininess);
    };

    void SetDirectionalLight(std::vector<Directional>& directional_vector)
    {
        for(auto index = 0; index < directional_vector.size(); ++index)
        {
            auto& directional = directional_vector[index];
            std::string head = (boost::format("dirLights[%d].") % index).str();
            Uniform(shader_program_).Set(head + "direction", directional.direction);
            Uniform(shader_program_).Set(head + "ambient", directional.ambient);
            Uniform(shader_program_).Set(head + "diffuse", directional.diffuse);
            Uniform(shader_program_).Set(head + "specular", directional.specular);
        }
    };

    void SetPointLight(std::vector<Point>& point_vector)
    {
        for(auto index = 0; index < point_vector.size(); ++index)
        {
            auto& point = point_vector[index];
            std::string head = (boost::format("pointLights[%d].") % index).str();
            Uniform(shader_program_).Set(head + "position", point.position);
            Uniform(shader_program_).Set(head + "ambient", point.ambient);
            Uniform(shader_program_).Set(head + "diffuse", point.diffuse);
            Uniform(shader_program_).Set(head + "specular", point.specular);
            Uniform(shader_program_).Set(head + "constant", point.constant);
            Uniform(shader_program_).Set(head + "linear", point.linear);
            Uniform(shader_program_).Set(head + "quadratic", point.quadratic);
        }
    };

    void SetSpotLight(std::vector<Spot>& spot_vector)
    {
        for(auto index = 0; index < spot_vector.size(); ++index)
        {
            auto& spot = spot_vector[index];
            std::string head = (boost::format("spotLights[%d].") % index).str();
            Uniform(shader_program_).Set(head + "position", spot.position);
            Uniform(shader_program_).Set(head + "direction", spot.direction);
            Uniform(shader_program_).Set(head + "ambient", spot.ambient);
            Uniform(shader_program_).Set(head + "diffuse", spot.diffuse);
            Uniform(shader_program_).Set(head + "specular", spot.specular);
            Uniform(shader_program_).Set(head + "constant", spot.constant);
            Uniform(shader_program_).Set(head + "linear", spot.linear);
            Uniform(shader_program_).Set(head + "quadratic", spot.quadratic);
            Uniform(shader_program_).Set(head + "cutOff", spot.cutOff);
            Uniform(shader_program_).Set(head + "outerCutOff", spot.outerCutOff);  
        }
    };

protected:
    ShaderProgram* shader_program_;
};

#endif