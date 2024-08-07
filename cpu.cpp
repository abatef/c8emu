#include "cpu.hpp"
#include <random>

CPU::CPU(Memory *_m, Display *_d, Input *_i)
    : memory(_m)
    , display(_d)
    , input(_i)
{
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

uint16_t OP00EE(CPU &cpu)
{
    if (cpu.SP - 1 < 0) {
        return 1;
    }
    cpu.PC = cpu.STACK[cpu.SP--];
    return 0;
}

uint16_t OP1NNN(CPU &cpu)
{
    cpu.PC = cpu.NNN;
    return 0;
}

uint16_t OP2NNN(CPU &cpu)
{
    cpu.STACK[++cpu.SP] = cpu.PC;
    cpu.PC = cpu.NNN;
    return 0;
}

uint16_t OP3XKK(CPU &cpu)
{
    if (cpu.R[cpu.X] == cpu.KK) {
        cpu.PC += 2;
    }
    return 0;
}

uint16_t OP4XKK(CPU &cpu)
{
    if (cpu.R[cpu.X] != cpu.KK) {
        cpu.PC += 2;
    }
    return 0;
}

uint16_t OP5XY0(CPU &cpu)
{
    if (cpu.R[cpu.X] == cpu.R[cpu.Y]) {
        cpu.PC += 2;
    }
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

uint16_t OP8XY0(CPU &cpu)
{
    cpu.R[cpu.X] = cpu.R[cpu.Y];
    return 0;
}

uint16_t OP8XY1(CPU &cpu)
{
    cpu.R[cpu.X] |= cpu.R[cpu.Y];
    return 0;
}

uint16_t OP8XY2(CPU &cpu)
{
    cpu.R[cpu.X] &= cpu.R[cpu.Y];
    return 0;
}

uint16_t OP8XY3(CPU &cpu)
{
    cpu.R[cpu.X] ^= cpu.R[cpu.Y];
    return 0;
}

uint16_t OP8XY4(CPU &cpu)
{
    if (int(cpu.R[cpu.X]) + int(cpu.R[cpu.Y]) > 255) {
        cpu.setVf();
    } else {
        cpu.clearVf();
    }
    cpu.R[cpu.X] += cpu.R[cpu.Y];
    return 0;
}

uint16_t OP8XY5(CPU &cpu)
{
    if (cpu.R[cpu.X] > cpu.R[cpu.Y]) {
        cpu.setVf();
    } else {
        cpu.clearVf();
    }
    cpu.R[cpu.X] -= cpu.R[cpu.Y];
    return 0;
}

uint16_t OP8XY6(CPU &cpu)
{
    if (cpu.R[cpu.X] & 0x01) {
        cpu.setVf();
    }
    cpu.R[cpu.X] >>= 1;
    return 0;
}

uint16_t OP8XY7(CPU &cpu)
{
    if (cpu.R[cpu.X] < cpu.R[cpu.Y]) {
        cpu.setVf();
    } else {
        cpu.clearVf();
    }
    cpu.R[cpu.X] = cpu.R[cpu.Y] - cpu.R[cpu.X];
    return 0;
}

uint16_t OP8XYE(CPU &cpu)
{
    if (cpu.R[cpu.X] & 0x80) {
        cpu.setVf();
    }
    cpu.R[cpu.X] <<= 1;
    return 0;
}

uint16_t OP9XY0(CPU &cpu)
{
    if (cpu.R[cpu.X] != cpu.R[cpu.Y]) {
        cpu.PC += 2;
    }
    return 0;
}

uint16_t OPANNN(CPU &cpu)
{
    cpu.I = cpu.NNN;
    return 0;
}

uint16_t OPBNNN(CPU &cpu)
{
    cpu.PC = cpu.NNN + cpu.R[R::V0];
    return 0;
}

uint16_t OPCXKK(CPU &cpu)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
    uint8_t randomNumber = distrib(gen);
    cpu.R[cpu.X] = cpu.KK & randomNumber;
    return 0;
}

uint16_t OPDXYN(CPU &cpu)
{
    uint8_t x = cpu.R[cpu.X];
    uint8_t y = cpu.R[cpu.Y];
    uint8_t height = cpu.N;

    cpu.clearVf();

    for (int row = 0; row < height; row++) {
        uint8_t spriteByte = cpu.memory->readByteFromMemory(cpu.I + row);

        for (int col = 0; col < 8; col++) {
            uint8_t spritePixel = spriteByte & (0x80 >> col);
            uint8_t wrappedX = (x + col) % 64;
            uint8_t wrappedY = (y + row) % 32;

            uint8_t *screenPixel = &cpu.display->backBuffer[wrappedX][wrappedY];
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

uint16_t OPEX9E(CPU &cpu)
{
    if (cpu.input->isPressed(cpu.R[cpu.X])) {
        cpu.PC += 2;
    }
    return 0;
}

uint16_t OPEXA1(CPU &cpu)
{
    if (!cpu.input->isPressed(cpu.R[cpu.X])) {
        cpu.PC += 2;
    }
    return 0;
}

uint16_t OPFX07(CPU &cpu)
{
    cpu.R[cpu.X] = cpu.d_timer;
    return 0;
}

uint16_t OPFX0A(CPU &cpu)
{
    cpu.pause = false;
    while (!cpu.pause) {
        cpu.input->handleInput(cpu.pause, &cpu.R[cpu.X]);
    }
    return 0;
}

uint16_t OPFX15(CPU &cpu)
{
    cpu.d_timer = cpu.R[cpu.X];
    return 0;
}

uint16_t OPFX18(CPU &cpu)
{
    cpu.s_timer = cpu.R[cpu.X];
    return 0;
}

uint16_t OPFX1E(CPU &cpu)
{
    cpu.I += cpu.R[cpu.X];
    return 0;
}

uint16_t OPFX29(CPU &cpu)
{
    cpu.I = _font_start_addr_s + cpu.R[cpu.X] * 5;
    return 0;
}

uint16_t OPFX33(CPU &cpu)
{
    uint8_t x = cpu.R[cpu.X];
    uint8_t o = x % 10;
    x /= 10;
    uint8_t t = x % 10;
    x /= 10;
    cpu.memory->writeByteToMemory(x, cpu.I);
    cpu.memory->writeByteToMemory(t, cpu.I + 1);
    cpu.memory->writeByteToMemory(o, cpu.I + 2);
    return 0;
}

uint16_t OPFX55(CPU &cpu)
{
    for (int i = 0; i <= cpu.X; i++) {
        cpu.memory->writeByteToMemory(cpu.R[i], cpu.I + i);
    }
    cpu.I += cpu.X + 1;
    return 0;
}

uint16_t OPFX65(CPU &cpu)
{
    for (int i = 0; i <= cpu.X; i++) {
        cpu.R[i] = cpu.memory->readByteFromMemory(cpu.I + i);
    }
    cpu.I += cpu.X + 1;
    return 0;
}
