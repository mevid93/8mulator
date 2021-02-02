#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string>

class Chip8
{
public:
    bool drawFlag; // flag tells if the display needs to be updated or not

    void initialize();                            // initialize the chipset
    void loadProgram(const std::string filename); // load program into the chipset memory
    void emulateCycle();                          // emulate one cycle
    void setKeys();                               // store key press state (press and release)

private:
    unsigned char memory[4096];  // memory of the chipset
    unsigned short opcode;       // current operation code
    unsigned char registers[16]; // chipset registers
    unsigned short index;        // index register
    unsigned short pc;           // program counter
    unsigned char gfx[64 * 32];  // pixel states (on/off)
    unsigned char delayTimer;    // 60 Hz delay timer
    unsigned char soundTimer;    // 60 Hz timer for sound
    unsigned short stack[16];    // 16-level stack
    unsigned short sp;           // stack pointer
    unsigned char key[16];       // states of the keypad keys
};

#endif