#include <iostream>
#include "chip8.hpp"

void Chip8::initialize()
{
    // initialize the memory
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }

    // initialize registers
    for (int i = 0; i < REGISTERS_SIZE; i++)
    {
        registers[i] = 0;
    }

    // initialize pixels
    for (int i = 0; i < PIXELS_SIZE; i++)
    {
        gfx[i] = 0;
    }

    // initialize stack
    for (int i = 0; i < STACK_SIZE; i++)
    {
        stack[i] = 0;
    }

    // initialize keys
    for (int i = 0; i < KEYS_SIZE; i++)
    {
        keys[i] = 0;
    }

    // initialize other values
    opcode = 0;
    index = 0;
    delayTimer = 0;
    soundTimer = 0;
    pc = 0;
    sp = 0;
}

void Chip8::loadProgram(const std::string filename)
{
}

void Chip8::emulateCycle()
{
    // Fetch Opcode
    // Decode Opcode
    // Execute Opcode
    // Update timers
}

void Chip8::setKeys()
{
}