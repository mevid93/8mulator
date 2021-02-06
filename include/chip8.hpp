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
    static const char FONTSET_SIZE = 80;    // chip 8 font set size

    bool drawFlag; // flag tells if the display needs to be updated or not

    void initialize();                            // initialize the chipset
    void loadProgram(const std::string filename); // load program into the chipset memory
    void emulateCycle();                          // emulate one cycle
    void setKeys();                               // store key press state (press and release)

private:
    unsigned char memory[MEMORY_SIZE];       // memory of the chipset
    unsigned short opcode;                   // current operation code
    unsigned char registers[REGISTERS_SIZE]; // chipset registers
    unsigned short ir;                       // index register
    unsigned short pc;                       // program counter
    unsigned char gfx[PIXELS_SIZE];          // pixel states (on/off)
    unsigned char delayTimer;                // 60 Hz delay timer
    unsigned char soundTimer;                // 60 Hz timer for sound
    unsigned short stack[STACK_SIZE];        // 16-level stack
    unsigned short sp;                       // stack pointer
    unsigned char keys[KEYS_SIZE];           // states of the keypad keys
    unsigned char fontset[FONTSET_SIZE] =    // font set for chip 8 --> each character is 4*5 pixels
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    void fetchOpcode();
    void decodeAndExecuteOpcode();
    void updateTimers();
};

#endif