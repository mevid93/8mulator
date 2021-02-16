#include <iostream>
#include <fstream>
#include <string>
#include "chip8.hpp"

Chip8::~Chip8()
{
    soundEngine->drop();
}

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

    // set sound engine
    soundEngine = irrklang::createIrrKlangDevice();
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

void Chip8::setKey(const unsigned char key, const unsigned char state)
{
    keys[key] = state;
}

void Chip8::updateTimers()
{


    // Update timers
    if (delayTimer > 0)
        --delayTimer;

    if (soundTimer > 0)
    {
        //if (soundTimer == 1 && !soundEngine->isCurrentlyPlaying(SOUND_FILE))
        //    soundEngine->play2D(SOUND_FILE);
        --soundTimer;
    }
    //else if (soundTimer == 0 && soundEngine->isCurrentlyPlaying(SOUND_FILE))
    //{
    //    soundEngine->stopAllSounds();
    //}
}

unsigned char *Chip8::getPixelStates()
{
    return gfx;
}

void Chip8::fetchOpcode()
{
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void Chip8::decodeAndExecuteOpcode()
{
    if (opcode == 0x00E0) // case 00E0
    {
        executeOpcode00E0();
    }
    else if (opcode == 0x00EE) // case 00EE
    {
        executeOpcode00EE();
    }
    else if ((opcode & 0xF000) == 0x0000) // case 0NNN
    {
        executeOpcode0NNN();
    }
    else if (opcode >> 12 == 0x0001) // case 1NNN
    {
        executeOpcode1NNN();
    }
    else if (opcode >> 12 == 0x0002) // case 2NNN
    {
        executeOpcode2NNN();
    }
    else if (opcode >> 12 == 0x0003) // case 3XNN
    {
        executeOpcode3XNN();
    }
    else if (opcode >> 12 == 0x0004) // case 4XNN
    {
        executeOpcode4XNN();
    }
    else if (opcode >> 12 == 0x0005) // case 5XY0
    {
        executeOpcode5XY0();
    }
    else if (opcode >> 12 == 0x0006) // case 6XNN
    {
        executeOpcode6XNN();
    }
    else if (opcode >> 12 == 0x0007) // case 7XNN
    {
        executeOpcode7XNN();
    }
    else if ((opcode & 0xF00F) == 0x8000) // case 8XY0
    {
        executeOpcode8XY0();
    }
    else if ((opcode & 0xF00F) == 0x8001) // case 8XY1
    {
        executeOpcode8XY1();
    }
    else if ((opcode & 0xF00F) == 0x8002) // case 8XY2
    {
        executeOpcode8XY2();
    }
    else if ((opcode & 0xF00F) == 0x8003) // case 8XY3
    {
        executeOpcode8XY3();
    }
    else if ((opcode & 0xF00F) == 0x8004) // case 8XY4
    {
        executeOpcode8XY4();
    }
    else if ((opcode & 0xF00F) == 0x8005) // case 8XY5
    {
        executeOpcode8XY5();
    }
    else if ((opcode & 0xF00F) == 0x8006) // case 8XY6
    {
        executeOpcode8XY6();
    }
    else if ((opcode & 0xF00F) == 0x8007) // case 8XY7
    {
        executeOpcode8XY7();
    }
    else if ((opcode & 0xF00F) == 0x800E) // case 8XYE
    {
        executeOpcode8XYE();
    }
    else if ((opcode & 0xF00F) == 0x9000) // case 9XY0
    {
        executeOpcode9XY0();
    }
    else if (opcode >> 12 == 0x000A) // case ANNN
    {
        executeOpcodeANNN();
    }
    else if (opcode >> 12 == 0x000B) // case BNNN
    {
        executeOpcodeBNNN();
    }
    else if (opcode >> 12 == 0x000C) // case CXNN
    {
        executeOpcodeCXNN();
    }
    else if (opcode >> 12 == 0x000D) // case DXYN
    {
        executeOpcodeDXYN();
    }
    else if ((opcode & 0xF0FF) == 0xE09E) // case EX9E
    {
        executeOpcodeEX9E();
    }
    else if ((opcode & 0xF0FF) == 0xE0A1) // case EXA1
    {
        executeOpcodeEXA1();
    }
    else if ((opcode & 0xF0FF) == 0xF007) // case FX07
    {
        executeOpcodeFX07();
    }
    else if ((opcode & 0xF0FF) == 0xF00A) // case FX0A
    {
        executeOpcodeFX0A();
    }
    else if ((opcode & 0xF0FF) == 0xF015) // case FX15
    {
        executeOpcodeFX15();
    }
    else if ((opcode & 0xF0FF) == 0xF018) // case FX18
    {
        executeOpcodeFX18();
    }
    else if ((opcode & 0xF0FF) == 0xF01E) // case FX1E
    {
        executeOpcodeFX1E();
    }
    else if ((opcode & 0xF0FF) == 0xF029) // case FX29
    {
        executeOpcodeFX29();
    }
    else if ((opcode & 0xF0FF) == 0xF033) // case FX33
    {
        executeOpcodeFX33();
    }
    else if ((opcode & 0xF0FF) == 0xF055) // case FX55
    {
        executeOpcodeFX55();
    }
    else if ((opcode & 0xF0FF) == 0xF065) // case FX65
    {
        executeOpcodeFX65();
    }
}

void Chip8::executeOpcode00E0()
{
    for (int i = 0; i < PIXELS_SIZE; i++)
    {
        gfx[i] = 0;
    }
    pc += 2;
}

void Chip8::executeOpcode00EE()
{
    sp--;
    pc = stack[sp];
    pc += 2;
}

void Chip8::executeOpcode0NNN()
{
    unsigned short nnn = opcode & 0x0FFF;
    pc = nnn;
}

void Chip8::executeOpcode1NNN()
{
    pc = opcode & 0x0FFF;
}

void Chip8::executeOpcode2NNN()
{
    stack[sp] = pc;
    sp++;
    pc = opcode & 0x0FFF;
}

void Chip8::executeOpcode3XNN()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short nn = opcode & 0x00FF;
    if (registers[x] == nn)
        pc += 2;
    pc += 2;
}

void Chip8::executeOpcode4XNN()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short nn = opcode & 0x00FF;
    if (registers[x] != nn)
        pc += 2;
    pc += 2;
}

void Chip8::executeOpcode5XY0()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    if (registers[x] == registers[y])
        pc += 2;
    pc += 2;
}

void Chip8::executeOpcode6XNN()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short nn = opcode & 0x00FF;
    registers[x] = nn;
    pc += 2;
}

void Chip8::executeOpcode7XNN()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short nn = opcode & 0x00FF;
    registers[x] += nn;
    pc += 2;
}

void Chip8::executeOpcode8XY0()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    registers[x] = registers[y];
    pc += 2;
}

void Chip8::executeOpcode8XY1()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    registers[x] = registers[x] | registers[y];
    pc += 2;
}

void Chip8::executeOpcode8XY2()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    registers[x] = registers[x] & registers[y];
    pc += 2;
}

void Chip8::executeOpcode8XY3()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    registers[x] = registers[x] ^ registers[y];
    pc += 2;
}

void Chip8::executeOpcode8XY4()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    unsigned int check = 0x10000;
    unsigned int sum = registers[x] + registers[y];
    registers[0xF] = 0;
    if ((sum & check) != 0x0)
        registers[0xF] = 1;
    registers[x] = (registers[y] + registers[x]) & 0xFFFF;
    pc += 2;
}

void Chip8::executeOpcode8XY5()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    registers[0xF] = 0;
    if (registers[y] < registers[x])
        registers[0xF] = 1;
    registers[x] -= registers[y];
    pc += 2;
}

void Chip8::executeOpcode8XY6()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    registers[0xF] = registers[x] & 1;
    registers[x] = registers[x] >> 1;
    pc += 2;
}

void Chip8::executeOpcode8XY7()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    registers[0xF] = 0;
    if (registers[y] > registers[x])
        registers[0xF] = 1;
    registers[x] = registers[y] - registers[x];
    pc += 2;
}

void Chip8::executeOpcode8XYE()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    registers[0xF] = registers[x] >> 11;
    registers[x] = registers[x] << 1;
    pc += 2;
}

void Chip8::executeOpcode9XY0()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    if (registers[x] != registers[y])
        pc += 2;
    pc += 2;
}

void Chip8::executeOpcodeANNN()
{
    ir = opcode & 0x0FFF;
    pc += 2;
}

void Chip8::executeOpcodeBNNN()
{
    unsigned short nnn = opcode & 0x0FFF;
    pc = nnn + registers[0x0];
}

void Chip8::executeOpcodeCXNN()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short nn = opcode & 0x00FF;
    registers[x] = nn & (rand() % 256);
    pc += 2;
}

void Chip8::executeOpcodeDXYN()
{
    unsigned short x = registers[(opcode & 0x0F00) >> 8];
    unsigned short y = registers[(opcode & 0x00F0) >> 4];
    unsigned short n = (opcode & 0x000F);
    unsigned short pixel;

    registers[0xF] = 0;
    for (unsigned int row = 0; row < n; row++)
    {
        pixel = memory[ir + row];
        for (unsigned int col = 0; col < 8; col++)
        {
            if ((pixel & (0x80 >> col)) != 0)
            {
                if (gfx[(y + row) * 64 + x + col] == 1)
                    registers[0xF] = 1;
                gfx[(y + row) * 64 + x + col] ^= 1;
            }
        }
    }
    drawFlag = true;
    pc += 2;
}

void Chip8::executeOpcodeEX9E()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    if (keys[registers[x]] == 1)
        pc += 2;
    pc += 2;
}

void Chip8::executeOpcodeEXA1()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    if (keys[registers[x]] != 1)
        pc += 2;
    pc += 2;
}

void Chip8::executeOpcodeFX07()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    registers[x] = delayTimer;
    pc += 2;
}

void Chip8::executeOpcodeFX0A()
{
    for (unsigned char key = 0; key < KEYS_SIZE; key++)
    {
        if (keys[key] == 1)
        {
            unsigned short x = (opcode & 0x0F00) >> 8;
            registers[x] = key;
            pc += 2;
            return;
        }
    }
}

void Chip8::executeOpcodeFX15()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    delayTimer = registers[x];
    pc += 2;
}

void Chip8::executeOpcodeFX18()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    soundTimer = registers[x];
    pc += 2;
}

void Chip8::executeOpcodeFX1E()
{
    int x = (opcode & 0x0F00) >> 8;
    ir += registers[x];
    pc += 2;
}

void Chip8::executeOpcodeFX29()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    ir = registers[x] * 5;
    pc += 2;
}

void Chip8::executeOpcodeFX33()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    memory[ir + 0] = registers[x] / 100;
    memory[ir + 1] = (registers[x] - memory[ir + 0] * 100) / 10;
    memory[ir + 2] = registers[x] - memory[ir + 0] * 100 - memory[ir + 1] * 10;
    pc += 2;
}

void Chip8::executeOpcodeFX55()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    for (unsigned short i = 0; i <= x; i++)
    {
        memory[ir + i] = registers[i];
    }
    pc += 2;
}

void Chip8::executeOpcodeFX65()
{
    unsigned short x = (opcode & 0x0F00) >> 8;
    for (unsigned short i = 0; i <= x; i++)
    {
        registers[i] = memory[ir + i];
    }
    pc += 2;
}
