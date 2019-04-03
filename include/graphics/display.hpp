#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "system/time.hpp"
#include "graphics/camera.hpp"

class Display
{
    public:
        Display(const unsigned int width, const unsigned int height, const std::string& title, const unsigned int glVersion, Camera* camera = NULL);
        virtual ~Display();

        void processInput();
        void swapBuffers();
        void pollEvents();

        void setCamera(Camera* camera);
        void centerWindow(GLFWmonitor* monitor);

        bool active();

    private:
        static GLFWwindow* window;
        static Camera* currentCamera;

        // Mouse Internal Variables (Relevant for FPS effect)
        static float lastX;
        static float lastY;
        static float deltaX;
        static float deltaY;
        static bool firstMouse;

        // Private Functions
        static void framebuffer_size_callback(GLFWwindow* _window, int width, int height);
        static void mouse_callback(GLFWwindow* _window, double xPos, double yPos);
        static void scroll_callback(GLFWwindow* _window, double _deltaX, double _deltaY);
};

#endif // DISPLAY_H
