#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#define POS glm::vec3(0.0f, 0.0f, 0.0f)
#define VUP glm::vec3(0.0f, 1.0f, 0.0f)

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
        glm::vec3 position;

        Camera(glm::vec3 _position = POS, glm::vec3 _worldUp = VUP, float _yaw = YAW, float _pitch = PITCH, float _fov = FOV, float _cNear = CNEAR, float _cFar = CFAR);
        virtual ~Camera();

        // Movement Functions
        void move(CameraMovement direction, float amount);
        void rotate(float _yaw, float _pitch);
        void zoom(float amount);

        // Get Matrix Functions
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(float aspect);

    private:
        // Camera Attributes
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

        // Private Functions
        void updateCameraVectors();

        // Static Constant Variables
        static const float YAW;
        static const float PITCH;
        static const float SPEED;
        static const float SENSITIVITY;
        static const float FOV;
        static const float CNEAR;
        static const float CFAR;
};

#endif // CAMERA_H
