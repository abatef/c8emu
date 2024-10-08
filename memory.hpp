#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <string>
#include <vector>

const uint16_t _intrept_address_s = 0x0000;
const uint16_t _font_start_addr_s = 0x0050;
const uint16_t _intrept_address_e = 0x01ff;
const uint16_t _program_address_s = 0x0200;
const uint16_t _program_address_e = 0x0e8f;

const uint8_t font_set[][16] = {
    // clang-format off
        {0xF0, 0x90, 0x90, 0x90, 0xF0},  // 0
        {0x20, 0x60, 0x20, 0x20, 0x70},  // 1
        {0xF0, 0x10, 0xF0, 0x80, 0xF0},  // 2
        {0xF0, 0x10, 0xF0, 0x10, 0xF0},  // 3
        {0x90, 0x90, 0xF0, 0x10, 0x10},  // 4
        {0xF0, 0x80, 0xF0, 0x10, 0xF0},  // 5
        {0xF0, 0x80, 0xF0, 0x90, 0xF0},  // 6
        {0xF0, 0x10, 0x20, 0x40, 0x40},  // 7
        {0xF0, 0x90, 0xF0, 0x90, 0xF0},  // 8
        {0xF0, 0x90, 0xF0, 0x10, 0xF0},  // 9
        {0xF0, 0x90, 0xF0, 0x90, 0x90},  // A
        {0xE0, 0x90, 0xE0, 0x90, 0xE0},  // B
        {0xF0, 0x80, 0x80, 0x80, 0xF0},  // C
        {0xE0, 0x90, 0x90, 0x90, 0xE0},  // D
        {0xF0, 0x80, 0xF0, 0x80, 0xF0},  // E
        {0xF0, 0x80, 0xF0, 0x80, 0x80}   // F
    // clang-format on
};

struct Memory {
    Memory();
    Memory(std::string rom);
    std::vector<uint8_t> memory;
    uint8_t readByteFromMemory(uint16_t address);
    uint8_t writeByteToMemory(uint8_t byte, uint16_t address);
    void loadRom(std::string rom);
    void loadFonts();
};

#endif // MEMORY_HPP