#include "graphics/display.hpp"

GLFWwindow* Display::window = NULL;
Camera* Display::currentCamera = NULL;

float Display::lastX = 0.0f;
float Display::lastY = 0.0f;
float Display::deltaX = 0.0f;
float Display::deltaY = 0.0f;
bool  Display::firstMouse = false;

Display::Display(const unsigned int width, const unsigned int height, const std::string& title, const unsigned int glVersion)
{
    // Initializing Members
    currentCamera = NULL;

    lastX = (float)width / 2;
    lastY = (float)height / 2;
    firstMouse = true;

    // Initializing GLFW
    // -----------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif // __APPLE__

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(window == NULL)
    {
        std::cerr << "Unable to create window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    centerWindow(glfwGetPrimaryMonitor());
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

Display::~Display() {}

void Display::processInput(IEventHandler& eventHandler, Light* light)
{
    float deltaTime = Time::getDeltaTime();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        eventHandler.onKeyDown(GLFW_KEY_W, false, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        eventHandler.onKeyDown(GLFW_KEY_S, false, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        eventHandler.onKeyDown(GLFW_KEY_A, false, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        eventHandler.onKeyDown(GLFW_KEY_D, false, deltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        eventHandler.onKeyDown(GLFW_KEY_SPACE, false, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        eventHandler.onKeyDown(GLFW_KEY_LEFT_SHIFT, false, deltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        light->disable();
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        light->enable();
}

void Display::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Display::pollEvents()
{
    glfwPollEvents();
}

void Display::setCamera(Camera* camera)
{
    currentCamera = camera;
}

void Display::centerWindow(GLFWmonitor* monitor)
{
    if(monitor == NULL)
        return;
    
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if(mode == NULL)
        return;
    
    int monitorX;
    int monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glfwSetWindowPos(window, monitorX + (mode->width - windowWidth) / 2, monitorY + (mode->height - windowHeight) / 2);
}

bool Display::active()
{
    return !glfwWindowShouldClose(window);
}

void Display::mouse_callback(GLFWwindow* _window, double xPos, double yPos)
{
    if(firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    deltaX = xPos - lastX;
    deltaY = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    currentCamera->rotate(deltaX, deltaY);
}

void Display::scroll_callback(GLFWwindow* _window, double _deltaX, double _deltaY)
{
    currentCamera->zoom(_deltaY);
}

void Display::framebuffer_size_callback(GLFWwindow* _window, int width, int height)
{
    glViewport(0, 0, width, height);
}
