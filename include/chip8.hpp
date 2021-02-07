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

    void fetchOpcode();            // get next opcode
    void decodeAndExecuteOpcode(); // decode and execute the opcode
    void updateTimers();           // update delay timer and sound timer

    void executeOpcode00E0(); // clear the screen
    void executeOpcode00EE(); // return from subroutine
    void executeOpcode0NNN(); // call machine code routine at address NNN
    void executeOpcode1NNN(); // jump to address NNN
    void executeOpcode2NNN(); // call subroutine at address NNN
    void executeOpcode3XNN(); // skip next instruction if registers[X] == NN
    void executeOpcode4XNN(); // skip next instruction if registers[X] != NN
    void executeOpcode5XY0(); // skip next instruction if registers[X] == registers[Y]
    void executeOpcode6XNN(); // registers[X] = NN
    void executeOpcode7XNN(); // registers[X] += NN
    void executeOpcode8XY0(); // registers[X] = registers[Y] 
    void executeOpcode8XY1(); // registers[X] = registers[X] | registers[Y]
    void executeOpcode8XY2(); // registers[X] = registers[X] & registers[Y]
    void executeOpcode8XY3(); // registers[X] = registers[X] ^ registers[Y]
    void executeOpcode8XY4(); // registers[X] += registers[Y]; registers[F] = (1 or 0)
    void executeOpcode8XY5(); // registers[X] -= registers[Y]; registers[F] = (1 or 0)
    void executeOpcode8XY6(); // store least significat bit to registers[F] and shift registers[X] >> 1
    void executeOpcode8XY7(); // registers[X] = registers[Y] - registers[X]; registers[F] = (0 or 1)
    void executeOpcode8XYE(); // store most significant bit to registers[F] and shift registers[X] << 1
    void executeOpcode9XY0(); // skip next instruction if registers[X] != registers[Y]
    void executeOpcodeANNN(); // ir = NNN
    void executeOpcodeBNNN(); // Jumps to address NNN + registers[0]
    void executeOpcodeCXNN(); // register[X] = rand() & NN
    void executeOpcodeDXYN(); // Draws a sprite at coordinate (registesr[X], registers[Y]) that has a height of N+1 pixels
    void executeOpcodeEX9E(); // Skips the next instruction if the key stored in registers[X] is pressed
    void executeOpcodeEXA1(); // Skips the next instruction if the key stored in registers[X] is not pressed.
    void executeOpcodeFX07(); // registers[X] = delay_timer
    void executeOpcodeFX0A(); // A key press is awaited, and then stored in VX. (Blocking until next key event) 
    void executeOpcodeFX15(); // delay_timer = registers[X]
    void executeOpcodeFX18(); // sound_timer = registers[X]
    void executeOpcodeFX1E(); // ir += registers[X]
    void executeOpcodeFX29(); // Sets ir to the location of the sprite for the character in registers[X]
    void executeOpcodeFX33(); // Stores the binary-coded decimal representation of registers[X]
    void executeOpcodeFX55(); // Stores registers[0] to registers[X] (including registers[X] in memory starting at address ir
    void executeOpcodeFX65(); // Fills registers[0] to registers[X] (including registers[X]) with values starting at address ir
};

#endif