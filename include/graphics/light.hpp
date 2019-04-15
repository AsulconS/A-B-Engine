#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "graphics/shader.hpp"

class Light
{
    public:
        Light(Shader* _shader, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
        virtual ~Light();

        virtual void enable() = 0;
        virtual void disable() = 0;
    
    protected:
        // Light Attributes
        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        // Shader
        Shader* shader;
};

class DirectionalLight : public Light
{
    public:
        DirectionalLight(Shader* _shader, glm::vec3 _dir, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
        virtual ~DirectionalLight();

        virtual void enable();
        virtual void disable();
    
    private:
        glm::vec3 direction;
};

#endif // LIGHT_H
