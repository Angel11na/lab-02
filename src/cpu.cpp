#include <iostream>
#include <iomanip>
using namespace std;

#include "dump.hpp"
#include "cpu.hpp"
#include "alu.hpp"


DecodedOp decode(Byte op) {
    return {
        .high = (Byte)((op & 0xF0) >> 4), // Старші 4 біти
        .low = (Byte)(op & 0x0F)          // Молодші 4 біти
    };
}



// Ваші — case для групи 0x1_ і dump_regs().

void step(CPU& cpu) {
    if (cpu.halted) {
        cout << "halted\n";
        return;
    }
    //  -- cpu.mem - це сам вказівник
    //  ~ cpu.mem = ...                                         | переміщення
    //  ~ cpu.mem++ / cpu.mem-- / cpu.mem += ... / cpu.mem -=   | переміщення через арифметику
    //  ~ *cpu.mem                                              | взяти значення
    Byte op = mem_get(*cpu.mem, cpu.pc);

    DecodedOp dop = decode(op);

    switch(dop.high){
        case GRP_IO:{
            switch(dop.low){
                case OP_HALT:
                    cpu.halted = true;
                    cpu.pc++;          // розмір HALT з таблиці — 1
                    break;
                case OP_NOP:
                    cpu.pc++;
                    break;
                default:
                    cpu.pc++;          // поки що як NOP
                    break;
            }

            break;
        }
        case GRP_ALU:{
            switch(dop.low){
                case OP_ADD:{
                    cout << "\n" 
                        << "ADD("<< static_cast<int>(cpu.a) << ", " << static_cast<int>(cpu.b) << ") = " 
                        << static_cast<int>(ADD(cpu.a, cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }

                case OP_SUB:{
                    cout << "\n"
                        << "SUB("<< static_cast<int>(cpu.a) << ", " << static_cast<int>(cpu.b) << ") = "
                        << static_cast<int>(SUB(cpu.a, cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }
                
                case OP_AND:{
                    cout << "\n"
                        << "AND = " << to_bin(AND(cpu.a, cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }

                case OP_OR:{
                    cout << "\n"
                        << "OR = " << to_bin(OR(cpu.a, cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }
                
                case OP_XOR:{
                    cout << "\n"
                        << "XOR = " << to_bin(XOR(cpu.a, cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }

                case OP_NOT:{
                    cout << "\n"
                        << "NOT(a) = " << to_bin(NOT(cpu.a, cpu.f))
                        << flags_state(cpu) << "\n"
                        << "NOT(b) = " << to_bin(NOT(cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n"
                        ;
                    cpu.pc++;
                    break;
                }
                
                case OP_SHL: {
                    cout << "\n"
                        << "SHL(a) = " << to_bin(SHL(cpu.a, cpu.f))
                        << flags_state(cpu) << "\n"
                        << "SHL(b) = " << to_bin(SHL(cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }
                
                case OP_SHR: {
                    cout << "\n"
                        << "SHR(a) = " << to_bin(SHR(cpu.a, cpu.f))
                        << flags_state(cpu) << "\n"
                        << "SHR(b) = " << to_bin(SHR(cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }

                case OP_INC:{
                    cout << "\n"
                        << "INC(a) = " << to_bin(INC(cpu.a, cpu.f))
                        << flags_state(cpu) << "\n"
                        << "INC(b) = " << to_bin(INC(cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }
                
                case OP_DEC:{
                    cout << "\n"
                        << "DEC(a) = " << to_bin(DEC(cpu.a, cpu.f))
                        << flags_state(cpu) << "\n"
                        << "DEC(b) = " << to_bin(DEC(cpu.b, cpu.f))
                        << flags_state(cpu) << "\n\n";
                    cpu.pc++;
                    break;
                }

                default:
                    cpu.pc++;          // поки що як NOP
                    break;
            }
            break;
        }
        default:
            cpu.pc++;          // поки що як NOP
            break;
    }
}

void dump_regs(const CPU& cpu) {
    cout << "PC = " << "0x" << hex << cpu.pc << dec << "\n";
    cout << "A = "; show_byte(cpu.a);
    cout << "B = "; show_byte(cpu.b);
    cout << 
        "Z: " << cpu.f.z << "\n" <<
        "N: " << cpu.f.n << "\n" <<
        "C: " << cpu.f.c << "\n";
}

inline const char* bit(bool b) {
    return b ? "1" : "0";
}
string flags_state(const CPU& cpu) {
    return "   |   Z: " + string(bit(cpu.f.z)) + "  " +
           "N: " + string(bit(cpu.f.n)) + "  " +
           "C: " + string(bit(cpu.f.c));
}