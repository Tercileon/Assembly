|[Table of Contents](/00-Table-of-Contents.md)|
|---|

---

# Introduction to Assembly Programming

```nasm
content:
    jmp .introduction

.introduction:
    mov rax, HowToASM
    jmp .basic_operations

.basic_operations:
    call .arithmetic
    call .bit_operations
    mov rcx, DataTypes
    jmp .control_flow

.control_flow:
    jmp .hardware_essentials
    
.hardware_essentials:
    mov rax, Memory
    mov rcx, Interrupts
    call FloatingPoint
    call Simd
    call .systems_programming

.systems_programming:
    ret
```

### Objectives

* Understand the relationship between assembly language and opcodes
* Understand byte ordering, as it pertains to Assembly programming
* Identify x86(_64) General Purpose Registers
* Perform basic memory access operations
* Begin debuggin with the GNU Source-Level Debugger (GDB)
* Understand basic data sizes and types with regard to x86(_64)

---

|[Next Topic](/02_Intro_to_ASM/01_Computer_Basics.md)|
|---|
