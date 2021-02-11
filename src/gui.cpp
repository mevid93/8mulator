#include <iostream>
#include <glad/glad.h>
#include "gui.hpp"

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Gui::~Gui()
{
    // we need to release graphic related resources
    clearGraphics();
}

void Gui::initializeVersion()
{
    // initialize glfw
    glfwInit();

    // set major version of openGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    // set minor version of openGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // use the core version of openGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Gui::initializeWindow()
{
    window = glfwCreateWindow(WIDTH, HEIGTH, "8mulator", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void Gui::initializeShaderPrograms()
{
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
}

void Gui::initializeVertexData()
{
    // set up vertex data where each emulated pixel block has 4 vertices
    // and each vertice has 3 coordinates
    float pixelWidth = (2 - 2 * MARGIN_HORIZONTAL) / PIXELS_HORIZONTAL;
    float pixelHeight = (2 - 2 * MARGIN_VERTICAL) / PIXELS_VERTICAL;

    int p = 0;
    for (int i = 0; i < PIXELS_VERTICAL; i++)
    {
        for (int j = 0; j < PIXELS_HORIZONTAL; j++)
        {
            float leftX = -1 + MARGIN_HORIZONTAL + j * pixelWidth;
            float rightX = leftX + pixelWidth;
            float topY = 1 - MARGIN_VERTICAL - i * pixelHeight;
            float bottomY = topY - pixelHeight;

            // set vertex coorindates
            vertices[p * 12 + 0] = leftX; // top left
            vertices[p * 12 + 1] = topY;
            vertices[p * 12 + 2] = 0.0f;
            vertices[p * 12 + 3] = rightX; // top right
            vertices[p * 12 + 4] = topY;
            vertices[p * 12 + 5] = 0.0f;
            vertices[p * 12 + 6] = leftX; // bottom left
            vertices[p * 12 + 7] = bottomY;
            vertices[p * 12 + 8] = 0.0f;
            vertices[p * 12 + 9] = rightX; // bottom right
            vertices[p * 12 + 10] = bottomY;
            vertices[p * 12 + 11] = 0.0f;

            // set indices for EBOs
            indices[p * 6 + 0] = 0;
            indices[p * 6 + 1] = 1;
            indices[p * 6 + 2] = 2;
            indices[p * 6 + 3] = 1;
            indices[p * 6 + 4] = 2;
            indices[p * 6 + 5] = 3;

            p++;
        }
    }
}

void Gui::initializeVertexArrays()
{
    // initialize vertex array objects and buffer objects
    glGenVertexArrays(PIXELS, VAOs);
    glGenBuffers(PIXELS, VBOs);
    glGenBuffers(PIXELS, EBOs);

    // set up pixels vertices data
    for (int i = 0; i < PIXELS; i++)
    {
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices + i * 12, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices + i * 6, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }
}

void Gui::setupGraphics()
{
    // set openGL version (core)
    initializeVersion();

    // initialize window (glfw)
    initializeWindow();

    // load all openGL function pointers
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // initialize shader programs (black and white)
    initializeShaderPrograms();

    // initialize data for for vertices (coordinates)
    initializeVertexData();

    // initialize vertex buffer objects and fill them with vertex data
    initializeVertexArrays();
}

void Gui::drawGraphics()
{
    // fill with black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // loop thourgh all pixels
    for (int i = 0; i < PIXELS; i++)
    {
        // TODO: check pixel status and choose correct fragment shader
        glUseProgram(shaderProgramWhite);

        // draw emulated pixel rectanle
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Gui::clearGraphics()
{
    // delete vertex arrays
    glDeleteVertexArrays(PIXELS, VAOs);

    // delete vertex buffers
    glDeleteBuffers(PIXELS, VBOs);

    // delete element buffer objects
    glDeleteBuffers(PIXELS, EBOs);

    // detele shader programs
    glDeleteProgram(shaderProgramWhite);
    glDeleteProgram(shaderProgramBlack);
}