# M1 — ALU як функції, перевірені руками. 

Для тестування `alu.cpp` було створено файл `test_alu.cpp` з окремою функцією `main()` для тестування функцій `ADD`, `AND`, `SHL`.
Для запуску цього файлу, необхідно змінити `CMakeLists.txt`:
```
add_executable(ember
    
    #   --- MAIN DECLARATIONS
    #src/main.cpp       # Коментуємо основний main()
    src/test_alu.cpp    # Підключаємо наш тестовий test_alu.cpp з власним main()
    #   ----------------------
    
    
    src/memory.cpp
    src/dump.cpp
    src/cpu.cpp
    src/alu.cpp
)
```
## Тест 1
Вхідні дані:
```
A = 100 = 0b01100100
B = 200 = 0b11001000
```

Виведення:

```
--- ADD test
result=44  Z=0 N=0 C=1

--- AND test
  A = 0b01100100
  B = 0b11001000
A&B = 0b01000000
Z=0 N=0 C=0

--- SHL test
     A = 0b01100100
SHL(A) = 0b11001000
Z=0 N=1 C=0
```

## Тест 2
Вхідні дані:
```
A = 255 = 0b11111111
B =   1 = 0b00000001
```

Виведення:

```
--- ADD test
result=0  Z=1 N=0 C=1

--- AND test
  A = 0b11111111
  B = 0b00000001
A&B = 0b00000001
Z=0 N=0 C=0

--- SHL test
     A = 0b11111111
SHL(A) = 0b11111110
Z=0 N=1 C=1
```

## Тест 3
Вхідні дані:
```
A =  14 = 0b00001110
B =  44 = 0b00101100
```

Виведення:

```
--- ADD test
result=58  Z=0 N=0 C=0

--- AND test
  A = 0b00001110
  B = 0b00101100
A&B = 0b00001100
Z=0 N=0 C=0

--- SHL test
     A = 0b00001110
SHL(A) = 0b00011100
Z=0 N=0 C=0
```




# M2 — закодувати, завантажити, step. 
## Встановлення значень у регістри 
```
❯ ./build/ember
ember 0.1 - 4096 bytes of memory you can see. Type `help`.
ember> reg a 200
ember> reg b 100
ember> regs
PC = 0x0
A = 200
B = 100
Z: 0
N: 0
C: 0
ember> 
```
## Встановлення команд через `set`: ADD (16), HALT (0)
```
ember> set 0 16
ember> set 1 0
ember> get 0
16  0x10  0b00010000  '.'
ember> get 1
0  0x0  0b00000000  '.'
ember> 
```

## Виконання операції `ADD` через `step`
```
ember> step

ADD(200, 100) = 44   |   Z: 0  N: 0  C: 1

ember>
```

## Встановлення стану `HALT` через `step`

```
ember> step
ember> step
halted
ember> step
halted
ember> step
halted
ember> 
```


# M3 — програма, яку видно. 
## `reg a 7`, `reg b 1`, байти [AND, HALT]
```
ember> reg a 7
ember> reg b 1
ember> set 0 18
ember> set 1 0
ember> get 0
18  0x12  0b00010010  '.'
ember> get 1
0  0x0  0b00000000  '.'
ember> regs
PC = 0x0
A = 7  0x7  0b00000111  '.'
B = 1  0x1  0b00000001  '.'
Z: 0
N: 0
C: 0
ember> step

AND = 0b00000001   |   Z: 0  N: 0  C: 0

ember> step
ember> step
halted
ember> 
```

## Cвоя послідовність із трьох інструкцій: [OR, XOR, SHL]. 
```
ember> reg a 7
ember> reg b 1 
ember> set 0 19
ember> set 1 20
ember> set 2 22
ember> regs
PC = 0x0
A = 7  0x7  0b00000111  '.'
B = 1  0x1  0b00000001  '.'
Z: 0
N: 0
C: 0
ember> step

OR = 0b00000111   |   Z: 0  N: 0  C: 0

ember> step

XOR = 0b00000110   |   Z: 0  N: 0  C: 0

ember> step

SHL(a) = 0b00001110   |   Z: 0  N: 0  C: 0
SHL(b) = 0b00000010   |   Z: 0  N: 0  C: 0

ember> step
ember> step
halted
ember> 
```

# M4 — розбирати масками, а не магією. 
Додано структуру:
```cpp
struct DecodedOp {
    Byte high;  // Старший півбайт
    Byte low;   // Молодший півбайт 
};
```
Оп-коди розбито на групи (`GRP_*`) та коди операцій (`OP_*`):
```cpp
const Byte GRP_IO  = 0x0;
const Byte GRP_ALU = 0x1;

const Byte OP_HALT = 0x0;  //  Stop VM (exit)   0
const Byte OP_NOP  = 0x1;  //  No operation     1

const Byte OP_ADD  = 0x0;  //  +    16
const Byte OP_SUB  = 0x1;  //  -    17
const Byte OP_AND  = 0x2;  //  &&   18
const Byte OP_OR   = 0x3;  //  ||   19
const Byte OP_XOR  = 0x4;  //  %2   20
const Byte OP_NOT  = 0x5;  //  !    21
const Byte OP_SHL  = 0x6;  //  <<   22
const Byte OP_SHR  = 0x7;  //  >>   23
const Byte OP_INC  = 0x8;  //  ++   24
const Byte OP_DEC  = 0x9;  //  --   25
```

Програма працює так само, як і раніше:
```
❯ ./build/ember
ember 0.1 - 4096 bytes of memory you can see. Type `help`.
ember> reg a 1
ember> reg b 2
ember> regs
PC = 0x0
A = 1  0x1  0b00000001  '.'
B = 2  0x2  0b00000010  '.'
Z: 0
N: 0
C: 0
ember> set 0 16
ember> set 1 17
ember> set 2 18
ember> set 3 1
ember> set 4 20
ember> set 5 24
ember> step

ADD(1, 2) = 3   |   Z: 0  N: 0  C: 0

ember> step    

SUB(1, 2) = 255   |   Z: 0  N: 1  C: 1

ember> step

AND = 0b00000000   |   Z: 1  N: 0  C: 0

ember> step
ember> step

XOR = 0b00000011   |   Z: 0  N: 0  C: 0

ember> step

INC(a) = 0b00000010   |   Z: 0  N: 0  C: 0
INC(b) = 0b00000011   |   Z: 0  N: 0  C: 0

ember> step
ember> step
halted
ember> step
halted
ember> step
halted
ember> 
```