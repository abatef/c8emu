#include "cpu.hpp"
#include "utils.hpp"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2) {
        std::cout << "Usage: ./CHIP8 -rom <rom_path> " << std::endl;
        return 0;
    }

    Instruction JT[0xffff];
    fillJT(JT);
    Memory memory {};
    int width = 640, height = 320;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-rom")) {
            if (i + 1 >= argc) {
                std::cout << "Usage: ./CHIP8 -rom <rom_path> " << std::endl;
                return 1;
            }
            memory.loadRom(argv[i + 1]);
        } else if (!strcmp(argv[i], "-res")) {
            if (i + 2 >= argc) {
                std::cout << "Usage: ./CHIP8 -res width height " << std::endl;
                return 1;
            }
            width = stoi(argv[i + 1]);
            height = stoi(argv[i + 2]);
        }
    }
    Display display(width, height);
    Input input {};
    CPU cpu(&memory, &display, &input);
    Audio audio;
    audio.init();
    int ins_cnt = 0;
    int ips = 540 / 60;
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
        updateTimers(cpu, ips, ins_cnt, audio);
    }
}
