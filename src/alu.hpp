#ifndef _ALU_HPP_
#define _ALU_HPP_

#include<iostream>
#include <cstdint>

using Byte = std::uint8_t;

Byte ADD(Byte a, Byte b, bool& carry);
Byte SUB(Byte a, Byte b, bool& carry);
Byte AND(Byte a, Byte b);
Byte OR(Byte a, Byte b);
Byte XOR(Byte a, Byte b);
Byte NOT(Byte a);
Byte SHL(Byte a);
Byte SHR(Byte a);
Byte INC(Byte a);
Byte DEC(Byte a);

#endif