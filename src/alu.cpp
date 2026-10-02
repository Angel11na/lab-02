#include "alu.hpp"


//  Допоміжна функція для встановлення флагів 
//  для побітових логічних операцій (AND, OR, XOR)
static inline void set_bit_operation_flags(Flags& flags, Byte result) {
    flags.c = false;                //  ніколи немає переповнення
    flags.z = (result == 0);        //  нульовий результат?
    flags.n = (result & 0x80) != 0; //  старший біт - одиниця?
}


//  Побітове додавання двох байтів
//  carry - перенесення 8го байта (чи виникло)
Byte ADD(Byte a, Byte b, Flags &flags){
    Byte result = 0;
    bool carry = false;          // вхідний перенос, локальний

    for (int i = 0; i < 8; ++i) {
        bool ab = (a >> i) & 1;
        bool bb = (b >> i) & 1;
        bool t  = ab ^ bb ^ carry;

        carry = (ab && bb) || (ab && carry) || (bb && carry);

        if (t)
            result = (Byte)(result | (1u << i));
    }

    flags.c = carry;                 // записуємо локальний перенос у флаг
    flags.z = (result == 0);
    flags.n = (result & 0x80) != 0;  // 0x80 = 128(10) = 1000_0000(2) - маска старшого біта

    return result;
}

//  Побітове віднімання двох байтів
//  borrow - запозичення з 9го байта (чи виникло)
Byte SUB(Byte a, Byte b, Flags &flags){
    Byte result = 0;
    bool borrow = false;         // вхідне запозичення, локальне

    for (int i = 0; i < 8; ++i) {
        bool ab = (a >> i) & 1;
        bool bb = (b >> i) & 1;
        bool t  = ab ^ bb ^ borrow;

        // borrow виникає, коли треба відняти, а біта не вистачає (відняти від 0 одиницю)
        borrow = (!ab && bb) || (!ab && borrow) || (bb && borrow);

        if (t)
            result = (Byte)(result | (1u << i));
    }

    flags.c = borrow;                // записуємо вихідне запозичення у флаг
    flags.z = (result == 0);
    flags.n = (result & 0x80) != 0;

    return result;
}

//  -----------------------------------
//  --- Побітові логічні операції   ---

Byte AND(Byte a, Byte b, Flags &flags){
    Byte result = (Byte)(a & b);
    set_bit_operation_flags(flags, result);

    /*  Example
        0010 1010
        0111 0110
        ==========
        0010 0010
    */

    return result;
}
Byte OR(Byte a, Byte b, Flags &flags){
    Byte result = (Byte)(a | b);
    set_bit_operation_flags(flags, result);

    /* Example
        0110 0100
        1010 0111
        ===========
        1110 0111
    */

    return result;
}
Byte XOR(Byte a, Byte b, Flags &flags){
    Byte result = (Byte)(a ^ b);
    set_bit_operation_flags(flags, result);

    /* Example
        0110 0100
        1010 0111
        ===========
        1100 0011
    */

    return result;
}
Byte NOT(Byte a, Flags &flags){
    Byte result = ~a;
    set_bit_operation_flags(flags, result);
    
    /* Example
        0100 1101
        ===========
        1011 0010
    */

    return result;
}
//  -------------------------------------------------------------



//  -----------------------
//  --- Зсуви (логічні) ---

Byte SHL(Byte a, Flags &flags){
    Byte result = (Byte)(a << 1);

    /* Example
        0100 1101 <<
        =============
        1001 1010
    */

    flags.c = (a & 0x80) != 0;       //  біт 7 виштовхнувся назовні
    flags.z = (result == 0);
    flags.n = (result & 0x80) != 0;

    return result;
}
Byte SHR(Byte a, Flags &flags){
    Byte result = (Byte)((a >> 1) | (a & 0x80));
    
    /* Example
        0100 1101 >>
        =============
        0010 0110
    */

    flags.c = (a & 0x01) != 0;
    flags.z = (result == 0);
    flags.n = (result & 0x80) != 0;
    
    return result;
}
//  ------------------------------------------------------------------



//  -------------------------------
//  --- Інкремент / декремент   ---

Byte INC(Byte a, Flags &flags){
    bool saved_c = flags.c;
    
    Byte result = ADD(a, 1, flags);
    flags.c = saved_c;               //  INC не впливає на C
    
    return result;
}
Byte DEC(Byte a, Flags &flags){
    bool saved_c = flags.c;
    Byte result = SUB(a, 1, flags);
    flags.c = saved_c;               //  DEC не впливає на C
    return result;
}
//  -----------------------------------------------------------------