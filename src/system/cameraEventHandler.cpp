#include "system/cameraEventHandler.hpp"

CameraEventHandler::CameraEventHandler(Camera* _camera)
    : camera(_camera) {}

CameraEventHandler::~CameraEventHandler() {}

void CameraEventHandler::onKeyDown(uint32 key, bool repeated, float deltaTime)
{
    switch(key)
    {
        case GLFW_KEY_W:
            camera->move(CameraMovement::FORWARD, deltaTime);
            break;
        case GLFW_KEY_S:
            camera->move(CameraMovement::BACKWARD, deltaTime);
            break;
        case GLFW_KEY_A:
            camera->move(CameraMovement::LEFT, deltaTime);
            break;
        case GLFW_KEY_D:
            camera->move(CameraMovement::RIGHT, deltaTime);
            break;
        case GLFW_KEY_SPACE:
            camera->move(CameraMovement::UP, deltaTime);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            camera->move(CameraMovement::DOWN, deltaTime);
            break;
        default:
            break;
    }
}
void CameraEventHandler::onKeyUp(uint32 key, bool repeated, float deltaTime)
{

}
void CameraEventHandler::onMouseDown(uint32 button, float deltaTime)
{

}
void CameraEventHandler::onMouseUp(uint32 button, float deltaTime)
{

}
void CameraEventHandler::onMouseMove(float xPos, float yPos, float deltaX, float deltaY, float deltaTime)
{

}
