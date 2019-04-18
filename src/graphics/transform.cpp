#include "graphics/transform.hpp"

Transform::Transform(const glm::mat4& _translation, const glm::mat4& _rotation, const glm::mat4& _scale)
    : translation(_translation), rotation(_rotation), scale(_scale) {}

Transform::~Transform() {}

void Transform::setTranslation(const glm::mat4& _translation)
{
    translation = _translation;
}
void Transform::setRotation(const glm::mat4& _rotation)
{
    rotation = _rotation;
}
void Transform::setScale(const glm::mat4& _scale)
{
    scale = _scale;
}

const glm::mat4 Transform::getModelMatrix()
{
    return translation * rotation * scale;
}
