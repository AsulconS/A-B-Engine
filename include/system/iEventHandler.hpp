#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "system/common.hpp"

class IEventHandler
{
public:
    IEventHandler() {}
    virtual ~IEventHandler() {}

    virtual void onKeyDown(uint32 key, bool repeated, float deltaTime = 0.0f) = 0;
    virtual void onKeyUp(uint32 key, bool repeated, float deltaTime = 0.0f) = 0;
    virtual void onMouseDown(uint32 button, float deltaTime = 0.0f) = 0;
    virtual void onMouseUp(uint32 button, float deltaTime = 0.0f) = 0;
    virtual void onMouseMove(float xPos, float yPos, float deltaX, float deltaY, float deltaTime = 0.0f) = 0;
};

#endif // EVENT_HANDLER_H
