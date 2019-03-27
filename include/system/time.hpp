#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

namespace Time
{
    static float deltaTime = 0.0f;
    static float lastFrame = 0.0f;
    static float currentFrame = glfwGetTime();

    float getDeltaTime();
}

#endif // TIME_H
