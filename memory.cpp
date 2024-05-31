#include "memory.hpp"
#include <fstream>
#include <iterator>
#include <iostream>
bool adress_assert(uint16_t address)
{
    return (address >= _program_address_s && address <= _program_address_e);
}

Memory::Memory(std::string rom)
{
    // Open the file in binary mode and move to the end to get the size
    std::ifstream file(rom, std::ios::binary | std::ios::ate);

    // Error handling: check if the file opened successfully
    if (!file) {
        std::cerr << "Error opening ROM file: " << rom << std::endl;
        return;
    }

    // Get the file size
    std::streamsize size = file.tellg();

    // Error handling: check if we got a valid file size
    if (size == -1) {
        std::cerr << "Error determining ROM file size." << std::endl;
        return;
    }

    // Move file pointer back to the beginning
    file.seekg(0, std::ios::beg);

    // Reserve space in the memory vector to avoid reallocations
    memory.resize(0xffff);

    // Read the entire file contents directly into the memory vector
    file.read(reinterpret_cast<char *>(memory.data() + _program_address_s), size);

    // Error handling: check if the file was read successfully
    if (!file) {
        std::cerr << "Error reading ROM file." << std::endl;
        return;
    }

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

    // int i = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 5; j++) {
            memory[i + j + _font_start_addr_s] = fonts[i][j];
        }
    }
}

void Memory::loadRom(std::string rom)
{

    std::ifstream   f(rom, std::ios::binary);
    std::streamsize fsize = 0;
    fsize = f.tellg();
    f.seekg(0, std::ios::end);
    fsize = f.tellg() - fsize;
    memory.reserve(0xffff);
    // std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
    memory.insert(memory.begin() + _program_address_s, std::istream_iterator<char>(f),
                  std::istream_iterator<char>());
}
