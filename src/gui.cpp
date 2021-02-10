#include <iostream>
#include <glad/glad.h>
#include "gui.hpp"

// whenever the window size changed, this callback function executes
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
    // initialize version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    window = glfwCreateWindow(WIDTH, HEIGTH, "8mulator", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // load all openGL function pointers
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // create vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // create fragment shader white
    unsigned int fragmentShaderWhite = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderWhite, 1, &whiteFragmentShaderSource, NULL);
    glCompileShader(fragmentShaderWhite);

    // create fragment shader black
    unsigned int fragmentShaderBlack = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderBlack, 1, &blackFragmentShaderSource, NULL);
    glCompileShader(fragmentShaderBlack);

    // create shader programs
    shaderProgramWhite = glCreateProgram();
    shaderProgramBlack = glCreateProgram();

    // link the first program object (white) with shader
    glAttachShader(shaderProgramWhite, vertexShader);
    glAttachShader(shaderProgramWhite, fragmentShaderWhite);
    glLinkProgram(shaderProgramWhite);
    glDeleteShader(fragmentShaderWhite);

    // link the second program object (black) with shader
    glAttachShader(shaderProgramBlack, vertexShader);
    glAttachShader(shaderProgramBlack, fragmentShaderBlack);
    glLinkProgram(shaderProgramBlack);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderBlack);
    
    // TODO: set up vertex data


    // TODO: set up vertex buffers
    

    // TODO: configure vertex attributes
}

void Gui::drawGraphics()
{
    // TODO: check status of all pixels and update if needed
    
    // TODO: bind objects and redraw all pixels
}

void Gui::clearGraphics()
{
    // TODO: delete vertex arrays

    // TODO: delete vertex buffers

    // detele shader programs
    glDeleteProgram(shaderProgramWhite);
    glDeleteProgram(shaderProgramBlack);
}