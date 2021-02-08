#include <iostream>
#include <glad/glad.h>
#include "gui.hpp"

// glfw: whenever the window size changed, this callback function executes
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Gui::~Gui()
{
    clearGraphics();
}

void Gui::setupGraphics()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGTH, "8mulator", NULL, NULL);
    if (window == NULL)
    {
        window = nullptr;
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        window == nullptr;
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // TODO: build shader programs

    // TODO: set up vertex data

    // TODO: object binding
}

void Gui::drawGraphics()
{
    // TODO: check status of all pixels and update if needed
    
    // TODO: bind objects and redraw all pixels
}

void Gui::clearGraphics()
{
    // TODO: Delete all resources related to openGL
}