#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "chip8.hpp"
#include "utilities.hpp"
#include "gui.hpp"

/* main function for the program */
int main(int argc, char *argv[])
{
    // check that user provided existing program file as parameter
    if (argc < 2 || !isExistingFile(argv[1]))
    {
        std::cout << "Please provide existing program file as parameter!" << std::endl;
        std::cout << "Command syntax: 8mulator <program_file>" << std::endl;
        return -1;
    }

    // initialize the Chip8 system and load the program into the memory
    Chip8 *chip8 = new Chip8();
    chip8->initialize();
    chip8->loadProgram(argv[1]);

    // set up OpenGL render system 
    GLFWwindow *window = setupGraphics();
    if(window == nullptr) return -1;
    
    // register input callbacks
    // setupInput();

    // emulation loop
    while (!glfwWindowShouldClose(window))
    {
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

        // emulate one cycle
        chip8->emulateCycle();

        // if the draw flag is set, update the screen
        if (chip8->drawFlag)
            // drawGraphics();

            // Store key press state (Press and Release)
            chip8->setKeys();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}