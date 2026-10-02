//#pragma once
#ifndef _CPU_HPP_
#define _CPU_HPP_

#include <iostream>
#include <cstdint>
using namespace std;

#include "memory.hpp"

struct DecodedOp {
    Byte high;  // Старший півбайт
    Byte low;   // Молодший півбайт 
};
DecodedOp decode(Byte op);


const Byte GRP_IO  = 0x0;
const Byte GRP_ALU = 0x1;

const Byte OP_HALT = 0x0;  //  Stop VM (exit)   0
const Byte OP_NOP  = 0x1;  //  No operation     1

const Byte OP_ADD  = 0x0;  //  +    16
const Byte OP_SUB  = 0x1;  //  -    17
const Byte OP_AND  = 0x2;  //  &&   18
const Byte OP_OR   = 0x3;  //  ||   19
const Byte OP_XOR  = 0x4;  //  %2   20
const Byte OP_NOT  = 0x5;  //  !    21
const Byte OP_SHL  = 0x6;  //  <<   22
const Byte OP_SHR  = 0x7;  //  >>   23
const Byte OP_INC  = 0x8;  //  ++   24
const Byte OP_DEC  = 0x9;  //  --   25


















// Коди операцій — саме з ISA.uk.md, свого не вигадуйте.





//  ---------------------------------------------------------



//  Types
//
struct Flags {
    bool z = false;   // результат нульовий
    bool n = false;   // старший біт результату — одиниця
    bool c = false;   // біт, який виїхав за межу восьми
};

struct CPU {
    Memory* mem = nullptr;   // вказівник на пам'ять
    std::uint16_t pc = 0;    // адреса НАСТУПНОЇ інструкції
    Byte a = 0;
    Byte b = 0;
    Flags f;
    bool halted = false;     // після HALT наступні step відмовляють
};
//  -----------------------------------------------------------------



//  Functions
//  
void step(CPU& cpu);
void dump_regs(const CPU& cpu);
string flags_state(const CPU& cpu);
//  ----------------------------------------

#endif