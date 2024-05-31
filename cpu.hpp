#ifndef CPU_HPP
#define CPU_HPP

#include "memory.hpp"
#include "display.hpp"

namespace HW
{
    enum R { V0 = 0, VF = 15 };
    namespace CPU
    {
        struct CPU
        {
            CPU(Memory *_m, Display *_d);
            uint8_t  R[16];
            uint16_t I;
            uint16_t PC;
            uint16_t STACK[20];
            uint8_t  SP;
            uint8_t  d_timer, s_timer;
            Display *display;
            Memory  *memory;
            uint8_t  X, Y, KK, N;
            uint16_t NNN;
            void     setVf()
            {
                R[R::VF] = 1;
            }
            void clearVf()
            {
                R[R::VF] = 0;
            }
            uint8_t fetch();
        };
    } // namespace CPU
} // namespace HW

using namespace HW::CPU;

uint16_t OP00E0(CPU &cpu);
uint16_t OP1NNN(CPU &cpu);
uint16_t OP6XNN(CPU &cpu);
uint16_t OP7XNN(CPU &cpu);
uint16_t OPANNN(CPU &cpu);
uint16_t OPDXYN(CPU &cpu);

#endif // CPU_HPP
