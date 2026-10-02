// dump.cpp — hex + ASCII, like the Unix tool `hexdump -C`.
//
// The `dump` function below is GIVEN and working, except for one TODO.
// Read it before you change it: it is the shape of nearly every loop you will
// write this semester (an outer loop over rows, an inner loop over columns).
#include <iomanip>
#include <iostream>
using namespace std;

#include "dump.hpp"


// How many bytes we print on one line. Try changing it to 8 and rebuilding.
const size_t BYTES_PER_LINE = 32;

// Is this byte something a terminal can print as a glyph?
// 0x20 is space, 0x7E is '~'. Everything outside that range we show as '.'.
static bool is_printable(Byte b) { return b >= 0x20 && b <= 0x7E; }

void dump(const Memory& mem) {
    // hex switches the stream to hexadecimal; setfill/setw pad with zeros
    // so every number is the same width and the columns line up.
    for (size_t row = 0; row < MEM_SIZE; row += BYTES_PER_LINE) {

        // The address column: 0000, 0010, 0020, ...
        cout << hex << setfill('0') << setw(4) << row << "  ";
        //  0, 16, 32, 48, ....

        // The hex column: 16 bytes, two digits each.
        for (size_t col = 0; col < BYTES_PER_LINE; ++col) {
            Byte b = mem.data[row + col];
            cout << setw(2) << static_cast<int>(b) << ' ';
        }

        cout << " |";

        // The ASCII gutter.
        for (size_t col = 0; col < BYTES_PER_LINE; ++col) {
            Byte b = mem.data[row + col];
            // TODO(lab-01, M2): when the byte IS printable, print the byte
            //                   itself instead of the dot. One token changes.
            //                   Hint: a Byte sent to cout prints as a
            //                   character already - that is the whole joke of
            //                   Lab 1. Right now every byte looks unprintable.
            if (is_printable(b)) {
                cout << b;
            } else {
                cout << '.';
            }
        }

        cout << "|\n";
    }

    // Put the stream back to decimal, or every number you print later is hex.
    cout << dec << setfill(' ');
}





string to_bin(long long n, int bits) {
    string res = "0b";
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
    cout << number << "  ";
    //  HEX
    cout << "0x" << hex << number << "  " << dec;
    //  BIN
    cout << to_bin(number) << "  ";
    //  CHAR
    cout << "'" << character << "'" << "\n";
}
