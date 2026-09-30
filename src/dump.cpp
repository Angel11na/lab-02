// dump.cpp — hex + ASCII, like the Unix tool `hexdump -C`.
//
// The `dump` function below is GIVEN and working, except for one TODO.
// Read it before you change it: it is the shape of nearly every loop you will
// write this semester (an outer loop over rows, an inner loop over columns).
#include <iomanip>
#include <iostream>

#include "dump.hpp"


// How many bytes we print on one line. Try changing it to 8 and rebuilding.
const std::size_t BYTES_PER_LINE = 32;

// Is this byte something a terminal can print as a glyph?
// 0x20 is space, 0x7E is '~'. Everything outside that range we show as '.'.
static bool is_printable(Byte b) { return b >= 0x20 && b <= 0x7E; }

void dump(const Memory& mem) {
    // std::hex switches the stream to hexadecimal; setfill/setw pad with zeros
    // so every number is the same width and the columns line up.
    for (std::size_t row = 0; row < MEM_SIZE; row += BYTES_PER_LINE) {

        // The address column: 0000, 0010, 0020, ...
        std::cout << std::hex << std::setfill('0') << std::setw(4) << row << "  ";
        //  0, 16, 32, 48, ....

        // The hex column: 16 bytes, two digits each.
        for (std::size_t col = 0; col < BYTES_PER_LINE; ++col) {
            Byte b = mem.data[row + col];
            std::cout << std::setw(2) << static_cast<int>(b) << ' ';
        }

        std::cout << " |";

        // The ASCII gutter.
        for (std::size_t col = 0; col < BYTES_PER_LINE; ++col) {
            Byte b = mem.data[row + col];
            // TODO(lab-01, M2): when the byte IS printable, print the byte
            //                   itself instead of the dot. One token changes.
            //                   Hint: a Byte sent to std::cout prints as a
            //                   character already - that is the whole joke of
            //                   Lab 1. Right now every byte looks unprintable.
            if (is_printable(b)) {
                std::cout << b;
            } else {
                std::cout << '.';
            }
        }

        std::cout << "|\n";
    }

    // Put the stream back to decimal, or every number you print later is hex.
    std::cout << std::dec << std::setfill(' ');
}





std::string to_bin(long long n, int bits = 8) {
    std::string res = "0b";
    for (int i = bits - 1; i >= 0; --i) {
        //  Transform data with binary operations
        res += (n & (1LL << i)) ? '1' : '0';
    }
    return res;
}



// Показати байт у вигляді 10го, 16го, 2го, та символ
//  Приймає байт, друкує строку виду: 65  0x41  0b01000001  'A'
void show_byte(Byte b) {
    // Expected for `set 0 65` then `get 0`:
    //   65  0x41  0b01000001  'A'

    int number = static_cast<int>(b);
    
    char character = 
        is_printable(b) ? b : '.';

    //  DEC
    std::cout << number << "  ";
    //  HEX
    std::cout << "0x" << std::hex << number << "  " << std::dec;
    //  BIN
    std::cout << to_bin(number) << "  ";
    //  CHAR
    std::cout << "'" << character << "'" << "\n";
}
