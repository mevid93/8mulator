#ifndef IO_HPP
#define IO_HPP

#include <GLFW/glfw3.h>
#include "chip8.hpp"

// query GLFW whether relevant keys are pressed/released
void processInput(GLFWwindow *window, Chip8 *chip8);

#endif