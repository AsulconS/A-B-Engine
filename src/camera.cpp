#include "graphics/camera.hpp"

const float Camera::YAW         = -90.0f;
const float Camera::PITCH       = 0.0f;
const float Camera::SPEED       = 2.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::FOV         = 45.0f;
const float Camera::CNEAR       = 0.1f;
const float Camera::CFAR        = 100.0f;

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, float _yaw, float _pitch, float _fov, float _cNear, float _cFar)
{
    position = _position;
    worldUp = _worldUp;

    yaw = _yaw;
    pitch = _pitch;
    updateCameraVectors();

    movementSpeed = SPEED;
    mouseSensitivity = SENSITIVITY;
    fov = _fov;
    cNear = _cNear;
    cFar = _cFar;
}

Camera::~Camera()
{
    //
}

void Camera::move(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    switch(direction)
    {
        case CameraMovement::FORWARD:
            position += front * velocity;
            break;

        case CameraMovement::BACKWARD:
            position -= front * velocity;
            break;

        case CameraMovement::LEFT:
            position -= right * velocity;
            break;

        case CameraMovement::RIGHT:
            position += right * velocity;
            break;

        default:
            break;
    }
    // position.y = 0.0f;
}

void Camera::rotate(float _yaw, float _pitch)
{
    yaw += _yaw * mouseSensitivity;
    pitch += _pitch * mouseSensitivity;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::zoom(float amount)
{
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= amount;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 nFront;
    nFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    nFront.y = sin(glm::radians(pitch));
    nFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    front = glm::normalize(nFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect)
{
    return glm::perspective(glm::radians(fov), aspect, cNear, cFar);
}
