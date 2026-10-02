#include <exception>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "cpu.hpp"
#include "dump.hpp"
#include "memory.hpp"

// Turn a word into a number. Accepts decimal (65) and hex (0x41).
// Returns false if the word is not a number at all.
static bool parse_number(const string& word, long& out);
static void print_help();

//  Command functions
void cmd_get(Memory& mem, istringstream& words);
void cmd_set(Memory& mem, istringstream& words);
void cmd_inc(Memory& mem, istringstream& words);
void cmd_reg(CPU& cpu, istringstream& words);

int main() {
    Memory mem; // 4096 bytes
    CPU cpu;

    cpu.mem = &mem; //  прив'язка процесора до пам'яті, & значить - "працює з пам'яттю напряму"

    cout << "ember 0.1 - 4096 bytes of memory you can see. Type `help`.\n";

    string line;
    while (true) {
        cout << "ember> ";

        // getline reads whole line. It returns false at end of input (Ctrl-D)
        if (!getline(cin, line)) {
            cout << '\n';
            break;
        }

        // Split the line into words
        istringstream words(line);
        string cmd;

        words >> cmd;

        if (cmd.empty()) {
            continue; // the user just pressed Enter
        } else if (cmd == "quit" || cmd == "exit") {
            break;
        } else if (cmd == "help") {
            print_help();
        } else if (cmd == "dump") {
            dump(mem);
        } else if (cmd == "get") {
            cmd_get(mem, words);
        } else if (cmd == "set") {
            cmd_set(mem, words);
        } else if (cmd == "inc") {
            cmd_inc(mem, words);
        } else if (cmd == "reg") {
            cmd_reg(cpu, words);
        } else if (cmd == "regs") {
            dump_regs(cpu);
        } else if(cmd == "step") {
            step(cpu);
        }
        else {
            cout << "unknown command: " << cmd << " (try `help`)\n";
        }
    }

    return 0; // 0 means "success" to the operating system
}

static bool parse_number(const string& word, long& out) {
    try {
        size_t used = 0;
        // base 0 means: look at the prefix. "0x41" is hex, "65" is decimal.
        out = stol(word, &used, 0);
        return used == word.size(); // reject things like "12abc"
    } catch (...) {
        return false;
    }
}

static void print_help() {
    cout << "commands:\n"
         << "  dump                     print all " << MEM_SIZE << " bytes\n"
         << "  get <addr>               show one byte four ways\n"
         << "  set <addr> <val>         write one byte (dec or 0x hex)\n"
         << "  inc <addr>               increment value and overwrite\n"
         << "  reg <a|b> <0..255>       set CPU register <a|b> value\n"
         << "  regs                     show current CPU state\n"
         << "  step                     perform one CPU instruction\n"
         << "  help                     this list\n"
         << "  quit                     leave\n";
}

//  =============================================================================
//  ==============  COMMANDS
//
void cmd_get(Memory& mem, istringstream& words) {
    string a;
    long addr = 0;
    if (!(words >> a) || !parse_number(a, addr)) {
        cout << "usage: get <addr>\n";
    } else if (addr < 0) {
        cout << "address must not be negative\n";
    } else {
        show_byte(mem_get(mem, static_cast<size_t>(addr)));
    }
}

void cmd_set(Memory& mem, istringstream& words) {
    string a, v;
    long addr = 0, value = 0;
    if (!(words >> a) || !(words >> v) || !parse_number(a, addr) || !parse_number(v, value)) {
        cout << "usage: set <addr> <value>\n";
    } else if (addr < 0) {
        cout << "address must not be negative\n";
    } else if (value < 0 || value > 255) {
        // A cell holds ONE byte. 256 does not fit. Lab 1, theory 3.
        cout << "a byte is 0..255, got " << value << '\n';
    } else if (!mem_set(mem, static_cast<size_t>(addr), static_cast<Byte>(value))) {
        cout << "address " << addr << " is outside 0.." << MEM_SIZE - 1 << '\n';
    }
}

void cmd_inc(Memory& mem, istringstream& words) {
    string a;
    long addr = 0;

    if (!(words >> a) || !parse_number(a, addr)) {
        cout << "usage: inc <addr>\n";
    } else if (addr < 0) {
        cout << "address must not be negative\n";
    } else {
        bool result = inc(mem, addr);

        if (!result) {
            cout << "Error during cmd: inc <addr>, addr = " << addr << "\n";
        }
    }
}

void cmd_reg(CPU& cpu, istringstream& words) {
    string r, v;
    long value = 0;
    
    if (
        !(words >> r) || !(words >> v) ||   //  чи достатньо елементів у команді?
        !(r == "a" || r == "b") ||          //  r є "а" або "b"?
        !parse_number(v, value) ||          //  чи v є цілим числом?
        value < 0 || value > 255            //  чи v в межах 0-255
    ) {
        cout << "usage: reg <a|b> <0..255>\n";
        return;
    }
    
    cpu.a = (r == "a") ? (Byte)value : cpu.a;
    cpu.b = (r == "b") ? (Byte)value : cpu.b;
}