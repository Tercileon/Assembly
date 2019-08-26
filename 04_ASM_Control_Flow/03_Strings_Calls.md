|[Table of Contents](/00-Table-of-Contents.md)|
|---|

---

## String Instructions

* What a "string" means to x86(_64)
    * Really just a string of bytes
    * No particular qualms about terminators (e.g., '0')
* Several prefixes and a flag that will modify behavior (more on those later)
* All of them have the unit to move/copy/initialize/scan/append to the end (e.g, scasb, vs scasw vs scads, etc)

### Common Features:

* **RSI** (or **ESI**, in x86) is treated as a pointer to the beginning of the "source"
* **RDI** (or **EDI**, in x86) is treated as a pointer to the beginning of the "destination"
* **RCX** (or **ECX**, in x86) is assumed to hold the count, if needed
* **RAX** (or **EAX**, in x86) is assumed to hold the value to evaluate, if needed (e.g., store, compare against, etc)
* Typically increments source and/or destination register pointers by the amount of data operated on (e.g., movsb would add 1 to both RSI and RDI, where movsd would add 4)

### Common String Instructions

* **Scan String** -- `scas(b/w/d/q)`
    * scans a string located at RDI for value found in RAX/EAX/AX/AL (depending on size used), and increments the pointer 
* **Store String** -- `stos(b/w/d/q)`
    * initializes the string located at RDI to the value pointed at by RAX/EAX/AX/AL (depending on size used) and increments the pointer. 
* **Load String** -- `lods(b/w/d/q)`
    * copies the value from RSI into RAX/EAX/AX/AL, and increments the pointer
* **Move String** -- `movs(b/w/d/q)`
    * copies data from RSI into RDI, and increments both pointers
* **Compare String** -- `cmps(b/w/d/q)`
    * compares the values stored at RSI and RDI, and increments the pointer, updating the RFLAGS (or EFLAGS) register with the result

### Prefixes

* Several instruction prefixes are available to modify behavior -- looping the instruction over a section of memory
* All of them tend to use RCX/ECX/etc as a termination condition - decrementing each instruciton
* In short, **this controls how often we repeat**

* Some prefixes avaliable:
    * `REP` -- continue performing the action RCX times
    * `REPNE` -- continue performing the action RCX times, or until the FLAGS register indicated the operands were equal
        * In short, **REPeat while Not Equal**
    * `REPE` -- continue performing the action RCX times, or until the FLAGS register indicates the operands were not equal
        * In short, **REPeat while Equal**
* Often used by compilers to essentially inline C string functions (such as strlen, memset, memcpy, etc...)

#### Prefix Examples

* **Unconditional**

```nasm
xor rax, rax            ; rax is now 0
mov rcx, 20             ; rcx now contains 20
mov rdi, _my_string_buf

rep stosb               ; Continue to store 0 till rcx is 0
```

* **Conditional**

```nasm
xor rax, rax
mov rcx, 20
; assume the buffer below contains a string
mov rdi, _my_populated_buf

repne scasb         ; continue until we hit a NULL byte
; RCX now contains the number of bytes we scanned... in a way. 
; Subtracting the original RCX against the new RCX will get you the count
```

#### The Direction Flag

* Controls the direction buffers are traversed when using the REP* prefixes
* If set during execution, an operation, ALWAYS clear after (or crashes likely to occur)
* **CLD** will increment lowest to highest
* **STD** will decrement highest to lowest

```nasm
std     ; the direction flag as been set
; do stuff here
cld     ; clear the direction flag, continue operations
```

**Complete Performance Lab:** 8

---

|[Next Topic](/04_ASM_Control_Flow/Lab_8)|
|---|
