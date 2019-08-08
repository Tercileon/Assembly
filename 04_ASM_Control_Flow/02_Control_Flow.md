<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" rel="Return to TOC"> Return to TOC </a>

# Control Flow

### Line Labels

* Global and Local

```nasm
global_label:
    ; stuff
.local_label:
    ; more stuff
```

### Everybody jmp .around

* jmp provides an unconditional branch, or tranfer of execution to the target

```nasm
.label1:
    xor rax, rax
    inc rax
    mov rcx, rax
    jmp .label2
    mov rsp, rax        ; never gets executed
.label2:
    shl rcx, 3          ; execution continues here...
    xchg rcx, rax
    ret
```

### call and ret

* Similar to jmp, but with a few key differences
* Functionally equivalent to: `push rip` followed by a `jmp X`
* Typically indicates a funciton call

```nasm
mov rax, 1
call label1     ; push RIP, jump to label 1
jmp label2

label1:
    ror rax, 1
    ret         ; returns control returns to "jmp label2"
label2:
    ; .....
```

#### More on ret

* Pops the return pointer off the stack and jumps to it
* Used to return the last point of execution (as shown on previous slide)

* **Let's break this example down.**
![](/imgs/crazy_stack.png)

* **What's happening?**
    * Call pushes the return address onto the stack, this allows ret to return to that address (aka the location we were before call)
    * Then call performs an unconditional jump to the location indiciated by the label operand
    * At which point we preserve the current frame pointer (rbp/ebp) by pushing it
    * Then we move the current stack pointer (rsp/esp) into the now pushed frame pointer (rbp/ebp)
    * Then we perform our actions
    * Then we ret
        * On return, we pop the old RBP then pop the ret pointer off the stack (that was placed there by call) and jump to where it's last point of execution is. (Effectivly a pop rip)
        * In short, this pops off the return address that we stored on the stack via call, then performs an unconditional jump to that location

    * In comparison, think of it as a normal C function:
        * We call that function, a stack frame is created and things are done in that function
        * When all is said and done, we return the value and continue where we left off in main
        * These are two different locations in the program, thus two different locations in memory

### A Side Note About Functions

* Typically store the stack pointer ((E|R)SP) at the top of the function
* If stored, must be (re)stored before returning
    * If we don't, our stack location will be off
    * If left at the top of the stack, we will return **ONTO** the stack
* This is not always done, as in **FPO** (Frame Pointer Optimization/Omission)
  
* Functions will be covered in more depth later

```nasm
myfunc:
    mov rbp, rsp
    push rbp
    ; ...
    pop rbp
    ret
```

## Conditional Control Flow: Comparisons

### cmp

* Compares two values by subtraction (e.g., `sub op1, op2`)
* Sets flags to indicate whether the values were equal, or if one was larger
* Flags set by this instruction: **CF, OF, SF, ZF, AF and PF**
* This does not actually modify the values
* **Uses:** Checking if one register is less than/equal to/greater than another reg/value

* Example:

```nasm
xor rax, rax
cmp rax, 0      ; they're equal! The ZF is now set
```

### test

* Compares two values by doing a bitwise AND
* The **SF, PF and ZF** get set by this operation
* Again, this does not save result anywhere
* Often used to test whether or not a register is 0
* **Uses:** Great for checking if a bit is set in a register or other comparisons needing bitwise checks

* Example:

```nasm
mov rax, 1
test rax, rax       ; the ZF is set to 0, as the result isn't 0

; ...

xor rax, rax
test rax, rax       ; the ZF is now 1
```

### jcc

* A large set of conditional branch instructions
* Most execute based on the value of one or more flags
* Some more common jumps:
    * **je** or **jz** - Jump if Equal (or Jump if Zero)
    * **jne** or **jnz** - Jump if Not Equal (or Not Zero)
    * **ja** - Jump if Above (if the operand compared previously is greater)
    * **jb** or **jc** - Jump if Below (or Jump if Carry)
    * Many othters - refer to the Intel manual for a comprehensive list

##### Example 1

* A simple check to see if the result of an operation is 0:

```nasm
xor rax, rax
test rax, rax
; Becase the zero flag is set here, we jump to the end
jz .end
mov rsi, rax        ; not executed due to jmp
; ...
.end:
    ret
```

##### Example 2

* A simple loop:

```nasm
mov rcx, 10        ; set our loop count to 10
xor rax, rax       ; set rax to 0
; This evaluates to: 10 + 9 + 8 _ ... + 1 + 0

.continue:
    add rax, rcx    ; add the current value of rcx to rax
    dec rcx         ; subtract 1 from rcx
    test rcx, rcx   ; check to see if rcx is 0
    jnz .continue   ; jump back to .continue, if rcx isn't 0

ret
```

### loop

* A simple macro for `dec rcx/test rcx, rcx/jnz <target>`
* Expects ECX/RCX to be populated with a counter variable
* The loop from the previous slide could be re-written to this:

```nasm
mov rcx, 10
xor rax, rax

.continue: 
    add rax, rcx
    loop .continue

ret
```

---
# Lab 7

<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/tree/master/04_ASM_Control_Flow/Lab_7" rel="Continue to Lab 7"> Continue to Lab 7 </a>
