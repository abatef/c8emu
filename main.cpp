#include <iostream>
#include "cpu.hpp"

using namespace std;

uint16_t mergeBytes(uint8_t msb, uint8_t lsb)
{
    uint16_t _msb = 0x00ff & msb;
    uint16_t _lsb = 0x00ff & lsb;
    return ((_msb << 8) | _lsb);
}

int main()
{
    Memory  memory("/home/abdelrahman/Downloads/IBM Logo.ch8");
    Display display(64, 32, 10);
    CPU     cpu(&memory, &display);

    while (true) {
        uint8_t  msb = cpu.fetch();
        uint8_t  lsb = cpu.fetch();
        uint16_t opcode = mergeBytes(msb, lsb);
        cpu.X = msb & 0x0f;
        cpu.Y = (lsb & 0xf0) >> 4;
        cpu.NNN = opcode & 0x0fff;
        cpu.N = lsb & 0x0f;
        cpu.KK = lsb;
        uint8_t un = msb & 0xf0;
        if (opcode == 0x00e0) {
            OP00E0(cpu);
        } else if (un == 0x10) {
            OP1NNN(cpu);
        } else if (un == 0x60) {
            OP6XNN(cpu);
        } else if (un == 0x70) {
            OP7XNN(cpu);
        } else if (un == 0xa0) {
            OPANNN(cpu);
        } else if (un == 0xd0) {
            OPDXYN(cpu);
        }
        display.render();
    }
}
