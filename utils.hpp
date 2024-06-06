#ifndef UTILS_HPP
#define UTILS_HPP
#include "cpu.hpp"
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

uint16_t mergeBytes(uint8_t msb, uint8_t lsb)
{
    uint16_t _msb = 0x00ff & msb;
    uint16_t _lsb = 0x00ff & lsb;
    return ((_msb << 8) | _lsb);
}

void extractXYN(CPU &cpu, uint8_t msb, uint8_t lsb, uint16_t opcode)
{
    cpu.X = msb & 0x0f;
    cpu.Y = (lsb & 0xf0) >> 4;
    cpu.NNN = opcode & 0x0fff;
    cpu.N = lsb & 0x0f;
    cpu.KK = lsb;
}

void updateTimers(CPU &cpu, int ips, int &ins_cnt)
{
    ins_cnt++;
    if (ins_cnt >= ips) {
        if (cpu.d_timer > 0) {
            cpu.d_timer--;
        }
        if (cpu.s_timer > 0) {
            if (cpu.s_timer == 1) {
                std::cout << '\a' << std::endl;
            }
            cpu.s_timer--;
        }
        ins_cnt = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(ips));
    }
}

void fillJT(Instruction JT[])
{
    for (uint32_t opcode = 0; opcode <= 0xFFFF; ++opcode) {
        // Default to an invalid instruction

        // Extract parts of the opcode
        uint16_t nnn = opcode & 0x0FFF;
        uint8_t nn = opcode & 0x00FF;
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t y = (opcode & 0x00F0) >> 4;
        uint8_t n = opcode & 0x000F;

        switch (opcode & 0xF000) {
            case 0x0000 :
                if (nn == 0xE0) JT[opcode] = {OP00E0, "CLS", {0, 0, 0, 0}};
                else if (nn == 0xEE) JT[opcode] = {OP00EE, "RET", {0, 0, 0, 0}};
                break;
            case 0x1000 :
                JT[opcode] = {OP1NNN, "JP addr", {0, 0, 0, 0}};
                break;
            case 0x2000 :
                JT[opcode] = {OP2NNN, "CALL addr", {0, 0, 0, 0}};
                break;
            case 0x3000 :
                JT[opcode] = {OP3XKK, "SE Vx, byte", {0, 0, 0, 0}};
                break;
            case 0x4000 :
                JT[opcode] = {OP4XKK, "SNE Vx, byte", {0, 0, 0, 0}};
                break;
            case 0x5000 :
                if (n == 0x0) JT[opcode] = {OP5XY0, "SE Vx, Vy", {0, 0, 0, 0}};
                break;
            case 0x6000 :
                JT[opcode] = {OP6XNN, "LD Vx, byte", {0, 0, 0, 0}};
                break;
            case 0x7000 :
                JT[opcode] = {OP7XNN, "ADD Vx, byte", {0, 0, 0, 0}};
                break;
            case 0x8000 :
                switch (n) {
                    case 0x0 :
                        JT[opcode] = {OP8XY0, "LD Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0x1 :
                        JT[opcode] = {OP8XY1, "OR Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0x2 :
                        JT[opcode] = {OP8XY2, "AND Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0x3 :
                        JT[opcode] = {OP8XY3, "XOR Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0x4 :
                        JT[opcode] = {OP8XY4, "ADD Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0x5 :
                        JT[opcode] = {OP8XY5, "SUB Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0x6 :
                        JT[opcode] = {OP8XY6, "SHR Vx {, Vy}", {0, 0, 0, 0}};
                        break;
                    case 0x7 :
                        JT[opcode] = {OP8XY7, "SUBN Vx, Vy", {0, 0, 0, 0}};
                        break;
                    case 0xE :
                        JT[opcode] = {OP8XYE, "SHL Vx {, Vy}", {0, 0, 0, 0}};
                        break;
                }
                break;
            case 0x9000 :
                if (n == 0x0) JT[opcode] = {OP9XY0, "SNE Vx, Vy", {0, 0, 0, 0}};
                break;
            case 0xA000 :
                JT[opcode] = {OPANNN, "LD I, addr", {0, 0, 0, 0}};
                break;
            case 0xB000 :
                JT[opcode] = {OPBNNN, "JP V0, addr", {0, 0, 0, 0}};
                break;
            case 0xC000 :
                JT[opcode] = {OPCXKK, "RND Vx, byte", {0, 0, 0, 0}};
                break;
            case 0xD000 :
                JT[opcode] = {OPDXYN, "DRW Vx, Vy, nibble", {0, 0, 0, 0}};
                break;
            case 0xE000 :
                switch (nn) {
                    case 0x9E :
                        JT[opcode] = {OPEX9E, "SKP Vx", {0, 0, 0, 0}};
                        break;
                    case 0xA1 :
                        JT[opcode] = {OPEXA1, "SKNP Vx", {0, 0, 0, 0}};
                        break;
                }
                break;
            case 0xF000 :
                switch (nn) {
                    case 0x07 :
                        JT[opcode] = {OPFX07, "LD Vx, DT", {0, 0, 0, 0}};
                        break;
                    case 0x0A :
                        JT[opcode] = {OPFX0A, "LD Vx, K", {0, 0, 0, 0}};
                        break;
                    case 0x15 :
                        JT[opcode] = {OPFX15, "LD DT, Vx", {0, 0, 0, 0}};
                        break;
                    case 0x18 :
                        JT[opcode] = {OPFX18, "LD ST, Vx", {0, 0, 0, 0}};
                        break;
                    case 0x1E :
                        JT[opcode] = {OPFX1E, "ADD I, Vx", {0, 0, 0, 0}};
                        break;
                    case 0x29 :
                        JT[opcode] = {OPFX29, "LD F, Vx", {0, 0, 0, 0}};
                        break;
                    case 0x33 :
                        JT[opcode] = {OPFX33, "LD B, Vx", {0, 0, 0, 0}};
                        break;
                    case 0x55 :
                        JT[opcode] = {OPFX55, "LD [I], Vx", {0, 0, 0, 0}};
                        break;
                    case 0x65 :
                        JT[opcode] = {OPFX65, "LD Vx, [I]", {0, 0, 0, 0}};
                        break;
                }
                break;
        }
    }
}

#endif // UTILS_HPP
