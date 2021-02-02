#include <iostream>
#include "chip8.hpp"
#include "utilities.hpp"

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

    // set up OpenGL render system and register input callbacks
    // setupGraphics();
    // setupInput();

    // emulation loop
    while (true)
    {
        // emulate one cycle
        chip8->emulateCycle();

        // if the draw flag is set, update the screen
        if (chip8->drawFlag)
            // drawGraphics();

            // Store key press state (Press and Release)
            chip8->setKeys();
    }

    return 0;
}