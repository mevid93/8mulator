#include "io.hpp"

void processInput(GLFWwindow *window)
{
    // if escape is pressed, then exit the program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}