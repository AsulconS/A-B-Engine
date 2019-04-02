#include "graphics/display.hpp"

GLFWwindow* Display::window = NULL;
Camera* Display::currentCamera = NULL;

float Display::lastX = 0.0f;
float Display::lastY = 0.0f;
float Display::deltaX = 0.0f;
float Display::deltaY = 0.0f;
bool Display::firstMouse = false;

Display::Display(const unsigned int width, const unsigned int height, const std::string& title, const unsigned int glVersion, Camera* camera)
{
    // Initializing Members
    currentCamera = camera;

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

Display::~Display()
{
    //
}

void Display::processInput()
{
    float deltaTime = Time::getDeltaTime();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        currentCamera->move(CameraMovement::FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        currentCamera->move(CameraMovement::BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        currentCamera->move(CameraMovement::LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        currentCamera->move(CameraMovement::RIGHT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        currentCamera->move(CameraMovement::UP, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        currentCamera->move(CameraMovement::DOWN, deltaTime);
}

void Display::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Display::pollEvents()
{
    glfwPollEvents();
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
