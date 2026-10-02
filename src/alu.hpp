#ifndef _ALU_HPP_
#define _ALU_HPP_

#include <iostream>
#include <cstdint>

#include "cpu.hpp"

using Byte = std::uint8_t;

Byte ADD(Byte a, Byte b, Flags &flags);
Byte SUB(Byte a, Byte b, Flags &flags);
Byte AND(Byte a, Byte b, Flags &flags);
Byte OR(Byte a, Byte b, Flags &flags);
Byte XOR(Byte a, Byte b, Flags &flags);
Byte NOT(Byte a, Flags &flags);
Byte SHL(Byte a, Flags &flags);
Byte SHR(Byte a, Flags &flags);
Byte INC(Byte a, Flags &flags);
Byte DEC(Byte a, Flags &flags);

#endif