#ifndef CAMERA_EVENT_HANDLER_H
#define CAMERA_EVENT_HANDLER_H

#include <GLFW/glfw3.h>

#include "system/iEventHandler.hpp"
#include "graphics/camera.hpp"

class CameraEventHandler : public IEventHandler
{
public:
    CameraEventHandler(Camera* _camera);
    virtual ~CameraEventHandler();

    virtual void onKeyDown(uint32 key, bool repeated, float deltaTime = 0.0f);
    virtual void onKeyUp(uint32 key, bool repeated, float deltaTime = 0.0f);
    virtual void onMouseDown(uint32 button, float deltaTime = 0.0f);
    virtual void onMouseUp(uint32 button, float deltaTime = 0.0f);
    virtual void onMouseMove(float xPos, float yPos, float deltaX, float deltaY, float deltaTime = 0.0f);

private:
    Camera* camera;
};

#endif // CAMERA_EVENT_HANDLER_H
