#include "cpu.hpp"

CPU::CPU(Memory *_m, Display *_d)
{
    memory = _m;
    display = _d;
    PC = 0x200;
    SP = 0;
    I = 0;
    d_timer = 0;
    s_timer = 0;
}
uint8_t CPU::fetch()
{
    return memory->readByteFromMemory(PC++);
}

uint16_t OP00E0(CPU &cpu)
{
    cpu.display->clear();
    return 0;
}

uint16_t OP1NNN(CPU &cpu)
{
    cpu.PC = cpu.NNN;
    return 0;
}

uint16_t OP6XNN(CPU &cpu)
{
    cpu.R[cpu.X] = cpu.KK;
    return 0;
}

uint16_t OP7XNN(CPU &cpu)
{
    cpu.R[cpu.X] += cpu.KK;
    return 0;
}

uint16_t OPANNN(CPU &cpu)
{
    cpu.I = cpu.NNN;
    return 0;
}

// OPCODE DXYN
uint16_t OPDXYN(CPU &cpu)
{
    uint8_t x = cpu.R[cpu.X];
    uint8_t y = cpu.R[cpu.Y];
    uint8_t height = cpu.N;

    cpu.clearVf();

    for (int row = 0; row < height; ++row) {
        uint8_t spriteByte = cpu.memory->readByteFromMemory(cpu.I + row);

        for (int col = 0; col < 8; ++col) {
            uint8_t spritePixel = spriteByte & (0x80 >> col);
            uint8_t wrappedX = (x + col) % 64;
            uint8_t wrappedY = (y + row) % 32;

            uint8_t *screenPixel = &cpu.display->pixels[wrappedX][wrappedY];
            if (spritePixel && *screenPixel) {
                cpu.setVf();
            }
            *screenPixel ^= spritePixel;
        }
    }
    // cpu.display->drawFlag = 1;
    cpu.display->update();
    return 0;
}
