#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform
{
public:
    Transform(const glm::mat4& _translation, const glm::mat4& _rotation, const glm::mat4& _scale);
    virtual ~Transform();

    // Transform Setters
    void setTranslation(const glm::mat4& _translation);
    void setRotation(const glm::mat4& _rotation);
    void setScale(const glm::mat4& _scale);

    // Transform Getter
    const glm::mat4 getModelMatrix();

private:
    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scale;
};

#endif // TRANSFORM_H
