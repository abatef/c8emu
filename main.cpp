#include "cpu.hpp"
#include "utils.hpp"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: ./CHIP8 <rom_path> " << std::endl;
    }
    Instruction JT[0xffff];
    fillJT(JT);
    Memory memory;
    memory.loadRom(argv[1]);
    Display display(64, 32, 10);
    Input input;
    CPU cpu(&memory, &display, &input);
    int ins_cnt = 0;
    int ips = 600 / 60;
    bool quit = false;
    while (!quit) {
        uint8_t msb = cpu.fetch();
        uint8_t lsb = cpu.fetch();
        uint16_t opcode = mergeBytes(msb, lsb);
        extractXYN(cpu, msb, lsb, opcode);
        JT[opcode].execute(cpu);
        std::cout << JT[opcode].mnemonic << std::endl;
        input.handleInput(quit, nullptr);
        display.render();
        updateTimers(cpu, ips, ins_cnt);
    }
}
