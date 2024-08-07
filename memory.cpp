#include "memory.hpp"
#include <fstream>
#include <iostream>
bool adress_assert(uint16_t address)
{
    return (address >= _program_address_s && address <= _program_address_e);
}

Memory::Memory()
{
    memory.resize(0x0fff);
}

Memory::Memory(std::string rom)
{
    memory.resize(0x0fff);
    loadRom(rom);
    loadFonts();
}

uint8_t Memory::readByteFromMemory(uint16_t address)
{
    return memory[address];
}

uint8_t Memory::writeByteToMemory(uint8_t byte, uint16_t address)
{
    if (address < 0x200 || address > 0x69f) {
        return 1;
    }
    memory[address] = byte;
    return 0;
}

void Memory::loadFonts()
{

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 5; j++) {
            memory[i + j + _font_start_addr_s] = font_set[i][j];
        }
    }
}

void Memory::loadRom(std::string rom)
{

    std::ifstream file(rom, std::ios::binary | std::ios::ate);

    if (!file) {
        std::cerr << "Error opening ROM file: " << rom << std::endl;
        return;
    }

    std::streamsize size = file.tellg();

    if (size == -1) {
        std::cerr << "Error determining ROM file size." << std::endl;
        return;
    }
    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char *>(memory.data() + _program_address_s), size);

    if (!file) {
        std::cerr << "Error reading ROM file." << std::endl;
        return;
    }
}
