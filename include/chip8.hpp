#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string>

class Chip8
{
public:
    static const int MEMORY_SIZE = 4096;    // size of the memory area
    static const char REGISTERS_SIZE = 16;  // number of registers
    static const char STACK_SIZE = 16;      // number of supported stack levels
    static const char KEYS_SIZE = 16;       // number of keys
    static const int PIXELS_SIZE = 64 * 32; // number of pixels

    bool drawFlag; // flag tells if the display needs to be updated or not

    void initialize();                            // initialize the chipset
    void loadProgram(const std::string filename); // load program into the chipset memory
    void emulateCycle();                          // emulate one cycle
    void setKeys();                               // store key press state (press and release)

private:
    unsigned char memory[MEMORY_SIZE];       // memory of the chipset
    unsigned short opcode;                   // current operation code
    unsigned char registers[REGISTERS_SIZE]; // chipset registers
    unsigned short index;                    // index register
    unsigned short pc;                       // program counter
    unsigned char gfx[PIXELS_SIZE];          // pixel states (on/off)
    unsigned char delayTimer;                // 60 Hz delay timer
    unsigned char soundTimer;                // 60 Hz timer for sound
    unsigned short stack[STACK_SIZE];        // 16-level stack
    unsigned short sp;                       // stack pointer
    unsigned char keys[KEYS_SIZE];           // states of the keypad keys
};

#endif