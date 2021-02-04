#include <iostream>
#include <fstream>
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
    ir = 0;
    delayTimer = 0;
    soundTimer = 0;
    pc = 0x200;
    sp = 0;

    // load font set into memory
    for(char i = 0; i < FONTSET_SIZE; i++)
    {
        memory[i] = fontset[i];
    }
}

void Chip8::loadProgram(const std::string filename)
{
    // create file input stream for reading the binary content
    std::ifstream is(filename, std::ifstream::binary);

    // get file length
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    // read to buffer
    char *buffer = new char[length];
    is.read(buffer, length);

    // load buffer to chipset memory
    for (int i = 0; i < length; i++)
    {
        memory[i + 0x200] = buffer[i];
    }

    // close stream and delete buffer
    is.close();
    delete[] buffer;
}

void Chip8::emulateCycle()
{
    fetchOpcode();
    decodeOpcode();
    executeOpcode();
    updateTimers();
}

void Chip8::setKeys()
{
}

void Chip8::fetchOpcode()
{

}

void Chip8::decodeOpcode()
{

}

void Chip8::executeOpcode()
{

}

void Chip8::updateTimers()
{

}