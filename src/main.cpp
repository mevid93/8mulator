#include <iostream>
#include <GLFW/glfw3.h>
#include "chip8.hpp"
#include "utilities.hpp"
#include "gui.hpp"
#include "io.hpp"

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
    Gui *gui = new Gui();
    gui->setupGraphics();
    

    // emulation loop
    while (!gui->shouldCloseGui())
    {
        // check user input
        processInput(gui->window);
        
        // Store key press state (Press and Release)
        chip8->setKeys();

        // emulate one cycle
        chip8->emulateCycle();

        // if the draw flag is set, update the screen
        //if (chip8->drawFlag)
        gui->drawGraphics(chip8->getPixelStates());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(gui->window);
        glfwPollEvents();
    }

    // delete other resources
    delete chip8;
    delete gui;

    return 0;
}