#ifndef CPU_HPP
#define CPU_HPP

#include "display.hpp"
#include "input.hpp"
#include "memory.hpp"

enum R { V0 = 0, VF = 15 };

struct CPU {
    CPU(Memory *_m, Display *_d, Input *_i);
    uint8_t R[16];
    uint16_t I;
    uint16_t PC;
    uint16_t STACK[20];
    uint8_t SP;
    uint8_t d_timer, s_timer;
    Memory *memory;
    Display *display;
    Input *input;
    uint8_t fetch();
    uint8_t X, Y, KK, N;
    uint16_t NNN;
    bool pause;
    void setVf() { R[R::VF] = 1; }
    void clearVf() { R[R::VF] = 0; }
};

typedef uint16_t (*Execute)(CPU &cpu);

struct Instruction {
    Execute execute;
    const char *mnemonic;
    bool _f[4];
};

uint16_t OP00E0(CPU &cpu);
uint16_t OP00EE(CPU &cpu);
uint16_t OP1NNN(CPU &cpu);
uint16_t OP2NNN(CPU &cpu);
uint16_t OP3XKK(CPU &cpu);
uint16_t OP4XKK(CPU &cpu);
uint16_t OP5XY0(CPU &cpu);
uint16_t OP6XNN(CPU &cpu);
uint16_t OP7XNN(CPU &cpu);
uint16_t OP8XY0(CPU &cpu);
uint16_t OP8XY1(CPU &cpu);
uint16_t OP8XY2(CPU &cpu);
uint16_t OP8XY3(CPU &cpu);
uint16_t OP8XY4(CPU &cpu);
uint16_t OP8XY5(CPU &cpu);
uint16_t OP8XY6(CPU &cpu);
uint16_t OP8XY7(CPU &cpu);
uint16_t OP8XYE(CPU &cpu);
uint16_t OP9XY0(CPU &cpu);
uint16_t OPANNN(CPU &cpu);
uint16_t OPBNNN(CPU &cpu);
uint16_t OPCXKK(CPU &cpu);
uint16_t OPDXYN(CPU &cpu);
uint16_t OPEX9E(CPU &cpu);
uint16_t OPEXA1(CPU &cpu);
uint16_t OPFX07(CPU &cpu);
uint16_t OPFX0A(CPU &cpu);
uint16_t OPFX15(CPU &cpu);
uint16_t OPFX18(CPU &cpu);
uint16_t OPFX1E(CPU &cpu);
uint16_t OPFX29(CPU &cpu);
uint16_t OPFX33(CPU &cpu);
uint16_t OPFX55(CPU &cpu);
uint16_t OPFX65(CPU &cpu);

#endif // CPU_HPP
