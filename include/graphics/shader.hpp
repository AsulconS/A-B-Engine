#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{
public:
    Shader(const std::string& name);
    virtual ~Shader();

    void use();

    void setBool(const std::string& name, bool v0);
    void setInt(const std::string& name, int v0);
    void setFloat(const std::string& name, float v0);

    void setVec2(const std::string& name, float v0, float v1);
    void setVec3(const std::string& name, float v0, float v1, float v2);
    void setVec4(const std::string& name, float v0, float v1, float v2, float v3);

    void setVec2(const std::string& name, const glm::vec2& v);
    void setVec3(const std::string& name, const glm::vec3& v);
    void setVec4(const std::string& name, const glm::vec4& v);

    void setMat3(const std::string& name, const glm::mat3& m0);
    void setMat4(const std::string& name, const glm::mat4& m0);

private:
    enum
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        NUM_SHADERS
    };

    GLuint program;
    GLuint shaders[NUM_SHADERS];

    GLuint createShader(const std::string& name, GLenum type);
    std::string loadShader(const std::string& path);

    // Private Functions
    void checkErrors(GLuint program, bool type);
};

#endif // SHADER_H
