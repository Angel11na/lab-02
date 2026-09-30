#include <iostream>

#include "cpu.hpp"
#include "alu.hpp"


// Ваші — case для групи 0x1_ і dump_regs().

void step(CPU& cpu) {
    if (cpu.halted) {
        std::cout << "halted\n";
        return;
    }
    //  -- cpu.mem - це сам вказівник
    //  ~ cpu.mem = ...                                         | переміщення
    //  ~ cpu.mem++ / cpu.mem-- / cpu.mem += ... / cpu.mem -=   | переміщення через арифметику
    //  ~ *cpu.mem                                              | взяти значення
    Byte op = mem_get(*cpu.mem, cpu.pc);

    switch (op) {
        case OP_HALT:
            cpu.halted = true;
            cpu.pc += 1;          // розмір HALT з таблиці — 1
            break;
        case OP_NOP:
            cpu.pc += 1;
            break;
        
        // ВАШЕ: case OP_ADD і решта групи 0x1_. Кожен — виклик функції з alu.cpp,
        // прапорці в cpu.f і cpu.pc += розмір із ISA.uk.md.
        case OP_ADD:
            
        

        default:
            cpu.pc += 1;          // поки що як NOP; у Lab 4 це стане помилкою
            break;
    }
}

void dump_regs(const CPU& cpu) {

}