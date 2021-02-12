#ifndef GUI_HPP
#define GUI_HPP

#include <GLFW/glfw3.h>

const unsigned int WIDTH = 1280;            // window width in pixels
const unsigned int HEIGTH = 720;            // window height in pixels
const unsigned int PIXELS = 64 * 32;        // number of emulated pixels
const unsigned char PIXELS_HORIZONTAL = 64; // number of horizontal pixels in emulated screen
const unsigned char PIXELS_VERTICAL = 32;   // number of vertical pixels in emulated screen
const float MARGIN_HORIZONTAL = 0.3f;       // margin from emulated screen to window borders (horizontal)
const float MARGIN_VERTICAL = 0.2f;         // margin from emulated screen to window borders (vertical)

class Gui
{
public:
    GLFWwindow *window; // openGL window

    ~Gui(); // desctructor

    void setupGraphics();                                // function to initialize GLFW window
    void drawGraphics(const unsigned char *pixelStates); // function to draw graphics
    void clearGraphics();                                // remove all allocated openGL graphic objects
    bool shouldCloseGui();                               // returns true if Gui should be closed

private:
    unsigned int shaderProgramWhite;  // opengl shader program identifier (white)
    unsigned int shaderProgramBlack;  // opengl shader program idnetifier (black)
    unsigned int VBOs[PIXELS];        // vertex buffer objects
    unsigned int VAOs[PIXELS];        // vertex array objects
    unsigned int EBOs[PIXELS];        // element buffer objects
    unsigned int indices[PIXELS * 6]; // indices for element buffer objects
    float vertices[PIXELS * 12];      // vertex data

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

    void initializeVersion();        // define openGL version
    void initializeWindow();         // create openGL window
    void initializeShaderPrograms(); // create shader programs (black and white)
    void initializeVertexData();     // create vertex data for pixels
    void initializeVertexArrays();   // initialize vertex array objects and vertex buffer objects
};

#endif