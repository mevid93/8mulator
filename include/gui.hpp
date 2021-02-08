#ifndef GUI_HPP
#define GUI_HPP

#include <GLFW/glfw3.h>

class Gui
{
public:
    GLFWwindow *window; // openGL window

    ~Gui(); // desctructor

    void setupGraphics(); // function to initialize GLFW window
    void drawGraphics();  // function to draw graphics
    void clearGraphics(); // remove all allocated openGL graphic objects

private:
    const unsigned int WIDTH = 1280;           // window width in pixels
    const unsigned int HEIGTH = 720;           // window height in pixels
    const unsigned char pixelsHorizontal = 64; // number of horizontal pixels in emulated screen
    const unsigned char pixelsVertical = 32;   // number of vertical pixels in emulated screen

    unsigned int shaderProgram; // opengl shader program identifier

    // openGL vertex shader resource
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    // openGL vertex shader resource (white color)
    const char *whiteFragmentShaderSource = "#version 330 core\n"
                                            "out vec4 FragColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                                            "}\n\0";

    // openGL vertex shader resource (black color)
    const char *blackFragmentShaderSource = "#version 330 core\n"
                                            "out vec4 FragColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
                                            "}\n\0";
};

#endif