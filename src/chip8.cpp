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
    for (char i = 0; i < FONTSET_SIZE; i++)
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
    decodeAndExecuteOpcode();
    updateTimers();
}

void Chip8::setKeys()
{
}

void Chip8::fetchOpcode()
{
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void Chip8::decodeAndExecuteOpcode()
{
    // case 00E0: clears the screen
    if (opcode == 0x00E0)
    {
        return;
    }

    // case 00EE: Returns from subroutine
    if (opcode == 0x00EE){
        return;
    }

    // case 0NNN: Calls machine code routine at address NNN.
    if (opcode & 0XF000 == 0X000)
    {
        return;
    }

    // case 1NNN: Jumps to address NNN 
    if (opcode >> 12 == 0X001)
    {
        return;
    }

    // case 2NNN: Calls subroutine at NNN
    if (opcode >> 12 == 0x002)
    {
        return;
    }

    // case 3XNN: Skips the next instruction if register X content equals NN
    if (opcode >> 12 == 0x003)
    {
        return;
    }

    // case 4XNN: Skips the next instruction if register X content does not equal NN
    if (opcode >> 12 == 0x004)
    {
        return;
    }

    // case 5XY0: Skips the next instruction if register X content equals register Y content
    if (opcode >> 12 == 0x005)
    {
        return;
    }

    // case 6XNN: Set NN to register X content
    if (opcode >> 12 == 0x006)
    {
        return;
    }

    // case 7XNN: Add NN to content of register X
    if (opcode >> 12 == 0x007)
    {
        return;
    }

    // case 8XY0: Set content of register Y to register X content
    if (opcode & 0xF00F == 0x8000)
    {
        return;
    }

    // case 8XY1: Set content of register X as bitwise or of registers X and Y
    if (opcode & 0xF00F == 0x8001)
    {
        return;
    }

    // case 8XY2: Set content of register X as bitwise and of registers X and Y
    if (opcode & 0XF00F == 0X8002)
    {
        return;
    }

    // case 8XY3: Set content of register X as bitwise xor of registers X and Y
    if (opcode & 0XF00F == 0X8003)
    {
        return;
    }

    // case 8XY4: Adds register Y content to register X. 
    // Register F is 1 when there is carry, and 0 otherwise
    if (opcode & 0XF00F == 0X8004)
    {
        return;
    }

    // case 8XY5: Remove register Y from register X.
    // Register F is set to 0 when there is a borrow, 1 otherwise
    if (opcode & 0XF00F == 0X8005)
    {
        return;
    }

    // case 8XY6: Stores the least significant bit of register X in 
    // register F and then shifts register X to the right by 1
    if (opcode & 0XF00F == 0x8006)
    {
        return;
    }

    // case 8XY7: Sets register X to register Y minus register X.
    // Register F is set to 0, when there is a borrow, and 1 otherwise
    if (opcode & 0XF00F == 0x8007)
    {
        return;
    }

    // case 8XYE: Stores the most significant bit of register X in register F 
    // and then shifts VX to the left by 1
    if(opcode & 0XF00F == 0X800E)
    {
        return;
    }

    // case 9XY0
    

    // case ANNN

    // case BNNN

    // case CXNN

    // case DXYN

    // case EX9E

    // case EXA1

    // case FX07

    // case FX0A

    // case FX15

    // case FX18

    // case FX1E

    // case FX29

    // case FX33

    // case FX55

    // case FX65
}

void Chip8::updateTimers()
{
}