#include "alu.hpp"

//  Побітове додавання двох байтів
//  carry - перенесення 8го байта (чи виникло)
Byte ADD(Byte a, Byte b, bool& carry){
    Byte result = 0;
    carry = false;

    for (int i = 0; i < 8; ++i) {
        bool ab = (a >> i) & 1, bb = (b >> i) & 1;
        bool t = ab ^ bb ^ carry;
        
        carry = (ab && bb) || (ab && carry) || (bb && carry);
        
        if (t) 
            result = (Byte)(result | (1u << i));
    }

    return result;
}

//  Побітове віднімання двох байтів
//  borrow - запозичення з 9го байта (чи виникло)
Byte SUB(Byte a, Byte b, bool& borrow){
    Byte result = 0;
    borrow = false;

    for (int i = 0; i < 8; ++i) {
        bool ab = (a >> i) & 1;
        bool bb = (b >> i) & 1;
        bool t  = ab ^ bb ^ borrow;

        // borrow = (bb && borrow) || (!ab && (bb || borrow));
        borrow = (!ab && bb) || (!ab && borrow) || (bb && borrow);

        if (t)
            result = (Byte)(result | (1u << i));
    }

    return result;
}





Byte AND(Byte a, Byte b){}
Byte OR(Byte a, Byte b){}
Byte XOR(Byte a, Byte b){}
Byte NOT(Byte a){}
Byte SHL(Byte a){}
Byte SHR(Byte a){}
Byte INC(Byte a){}
Byte DEC(Byte a){}