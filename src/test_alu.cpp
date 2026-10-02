#include<iostream>
#include<iomanip>
using namespace std;

#include "cpu.hpp"
#include "alu.hpp"
#include "dump.hpp"


int main(){

    Byte a = 14;
    Byte b = 44;
    Byte result = 0;

    Flags flags;


    cout << "A = " << setw(3) << static_cast<int>(a) << " = " << to_bin(a) << "\n";
    cout << "B = " << setw(3) << static_cast<int>(b) << " = " << to_bin(b) << "\n\n";

    //  --- ADD Test
    cout << "--- ADD test\n";
    result = ADD(a, b, flags);

    //  static_cast<Потрібний-Тип>(Що-Перетворити)
    cout << "result=" << static_cast<int>(result) << "  " << 
        "Z=" << flags.z << " " << 
        "N=" << flags.n << " " << 
        "C=" << flags.c << "\n\n";
    //  ------------------------------------


    //  AND Test
    cout << "--- AND test\n";
    
    result = AND(a,b,flags);
    cout << setw(6) << "A = "<< to_bin(a) << "\n";
    cout << setw(6) << "B = "<< to_bin(b) << "\n";
    cout << setw(6) << "A&B = " << to_bin (result) << "\n";
    cout << 
        "Z=" << flags.z << " " << 
        "N=" << flags.n << " " << 
        "C=" << flags.c << "\n\n";
    //  ------------------------------------


    //  SHL Test
    cout << "--- SHL test\n";
    cout << setw(9) << "A = " << to_bin(a) << "\n";
    result = SHL(a, flags);
    cout << setw(9) << "SHL(A) = " << to_bin(result) << "\n";
    cout << 
        "Z=" << flags.z << " " << 
        "N=" << flags.n << " " << 
        "C=" << flags.c << "\n\n";
    //  ------------------------------------





    return 0;
}