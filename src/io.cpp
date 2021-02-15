#include "io.hpp"

void processInput(GLFWwindow *window, Chip8 *chip8)
{
    // if escape is pressed, then exit the program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    // if key 1 is pressed, then change its state
    chip8->setKey(0x1, glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS ? 1 : 0);

    // if key 2 is pressed then change its state
    chip8->setKey(0x2, glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS ? 1 : 0);

    // if key 3 is pressed then change its state
    chip8->setKey(0x3, glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS ? 1 : 0);

    // if key 4 is pressed then change state of key C
    chip8->setKey(0xC, glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS ? 1 : 0);

    // if key Q is pressed then change state of key 4
    chip8->setKey(0x4, glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS ? 1 : 0);

    // if key W is pressed then change state of key 5
    chip8->setKey(0x5, glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ? 1 : 0);

    // if key E is pressed then change state of key 6
    chip8->setKey(0x6, glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ? 1 : 0);

    // if key R is pressed then change state of key D
    chip8->setKey(0xD, glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS ? 1 : 0);

    // if key A is pressed then change state of key 7
    chip8->setKey(0x7, glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? 1 : 0);

    // if key S is pressed then change state of key 8
    chip8->setKey(0x8, glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? 1 : 0);

    // if key D is pressed then change state of key 9
    chip8->setKey(0x9, glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? 1 : 0);

    // if key F is pressed then change state of key E
    chip8->setKey(0xE, glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS ? 1 : 0);

    // if key Z is pressed then change state of key A
    chip8->setKey(0xA, glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS ? 1 : 0);

    // if key X is pressed then change state of key 0
    chip8->setKey(0x0, glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS ? 1 : 0);

    // if key C is pressed then change state of key B
    chip8->setKey(0xB, glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS ? 1 : 0);

    // if key V is pressed then change state of key F
    chip8->setKey(0xF, glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS ? 1 : 0);
}