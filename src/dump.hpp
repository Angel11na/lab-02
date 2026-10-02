// dump.hpp — two ways of looking at bytes.
// GIVEN.
//#pragma once

#ifndef _DUMP_HPP_
#define _DUMP_HPP_

#include<iostream>
using namespace std;

#include "memory.hpp"

// Print the whole box, 16 bytes per line: address, hex, ASCII gutter.
void dump(const Memory& mem);

// Print ONE byte four ways: decimal, hex, binary, character.
// Example for the byte 65:   65  0x41  0b01000001  'A'
// TODO(lab-01, M3): implement in dump.cpp.
void show_byte(Byte b);

string to_bin(long long n, int bits = 8);

#endif