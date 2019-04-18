#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#define POS glm::vec3(0.0f, 0.0f, 0.0f)
#define WUP glm::vec3(0.0f, 1.0f, 0.0f)

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Camera(glm::vec3 _position = POS, glm::vec3 _worldUp = WUP, float _yaw = YAW, float _pitch = PITCH, float _fov = FOV, float _cNear = CNEAR, float _cFar = CFAR);
    virtual ~Camera();

    // Movement Functions
    void move(CameraMovement direction, float amount);
    void rotate(float _yaw, float _pitch);
    void zoom(float amount);

    // Set Camera Attributes
    void setPosition(const glm::vec3& pos);

    // Get Camera Attributes
    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getFront() const { return front; }

    // Get Matrix Functions
    const glm::mat4 getViewMatrix() const;
    const glm::mat4 getProjectionMatrix(float aspect) const;

private:
    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    // Camera Options
    float movementSpeed;
    float mouseSensitivity;
    float fov;
    float cNear;
    float cFar;

    // Static Constant Default Variables
    static const float YAW;
    static const float PITCH;
    static const float SPEED;
    static const float SENSITIVITY;
    static const float FOV;
    static const float CNEAR;
    static const float CFAR;

    // Private Functions
    void updateCameraVectors();
};

#endif // CAMERA_H
