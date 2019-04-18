#include "graphics/light.hpp"

Light::Light(Shader* _shader, const glm::vec3& _position,
                              const glm::vec3& _ambient,
                              const glm::vec3& _diffuse,
                              const glm::vec3& _specular)
     : position(_position), ambient(_ambient), diffuse(_diffuse), specular(_specular), shader(_shader)
{
    //
}

Light::~Light()
{
    //
}

DirectionalLight::DirectionalLight(Shader* _shader, const glm::vec3& _dir,
                                                    const glm::vec3& _ambient,
                                                    const glm::vec3& _diffuse,
                                                    const glm::vec3& _specular)
    : Light(_shader, glm::vec3(0.0f, 0.0f, 0.0f), _ambient, _diffuse, _specular), direction(_dir)
{
    shader->use();
    enable();
}

DirectionalLight::~DirectionalLight()
{
    //
}

void DirectionalLight::enable()
{
    shader->use();
    shader->setVec3("dirLight.ambient", ambient);
    shader->setVec3("dirLight.diffuse", diffuse);
    shader->setVec3("dirLight.specular", specular);
}

void DirectionalLight::disable()
{
    shader->use();
    shader->setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
    shader->setVec3("dirLight.diffuse", 0.0f, 0.0f, 0.0f);
    shader->setVec3("dirLight.specular", 0.0f, 0.0f, 0.0f);
}
