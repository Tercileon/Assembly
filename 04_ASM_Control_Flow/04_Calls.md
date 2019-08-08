<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" rel="Return to TOC"> Return to TOC </a>

# Function Calling Conventions

## Calling Conventions: x86

* **Microsoft** -- many calling conventions exist for x86
    * Different implications for how arguments get passed
    * Different implications for stack cleanup after function returns
    * Name mangling is often used to differentiate
    * Different than sys v (what most unix systems use)
* **System V x86 Calling Convention**
    * Most POSIX-compliant and (POSIX-like) platforms abide by this
        * Such as Linux, Solaris, BSD, OSX, etc
        * Also called **cdecl**
* Other calling conventions

### Microsoft Conventions

#### stdcall

* Indicated to compiler (from C) by _stdcall prefix
* Arguments pushed on the stack (in order from right to left)
* The function being called (the **"callee"**) cleans up the space allocated
* Name gets decorated with an appended "@X", where X is the number of bytes to allocate (num args *4)

##### Standard call in action -- Stack Cleanup:

```nasm
; Equiv: void __stdcall myfunc(int a, int b)
_myfunc@8:
    ; do stuff
    ret 8       ; we've cleaned up 8 bytes

; Equiv: int __stdcall myfunc2(int a)
_myfunc2@4:
    ; do stuff
    mov eax, 1
    ret 4
```

##### Standard call in action -- Accessing Parameters:

* If EBP hasn't been pushed to the stack:

```nasm
_myfunc@8:
    mov eax, [esp + 4]      ; param 1 -above the return pointer
    mov ecx, [esp + 8]      ; param 2 -above param 1
    ; do stuff
    ret 8
```

* There is a difference in how things are done if EBP has been pushed to stack or not... we need to acocunt for EBP in order to not fetch return address rather than argument

```nasm
_myfunc@8:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]      ; above both the ret ptr and old ebp
    mov ecx, [ebp + 12]     
    pop ebp
    ret 8
```

#### cdecl

* This is also the System V calling convention (e.g., what most non-Microsoft patforms use)
* Parameters passed in the same fashion as in stdcall
* Stack cleanup is different, the calling function (e.g., caller) is responsible for cleanup
    * So just ret and if you created caller, add esp with however many bytes were passed for cleanup
* No real name mangling, aside from a leading underscore `_`

```nasm
; callee
_myfunc:
    push ebp
    mov ebp, esp
    ; do stuff
    pop ebp
    ret

; caller
_caller:
    ; ...
    push 2      ; arg 2
    push 1      ; arg 1
    call _myfunc
    add esp, 8  clean up
    ; ...
```

* Notice how we don't cleanup the callee
* We do cleanup in caller though after call
* See how the arguments are passed?

#### fastcall

* First two arguments (from left to right) passed via registers (**ECX** and **EDX**) automatically
* Remaining arguments pushed on the stack (right to left, as with cdecl and stcall)
* Cleanup is performed by the callee (as with stdcall)
* Name mangling is similar to stdcall, but an additional `@` is prepended (e.g., `_@myfunc@8`)

### Other Conventions

#### thiscall

* "Special" convention used for C++ non-static member functions
* Defines a method of passing "this" pointer (which allows those functions access to specific instances of a class)
* Slight difference between Microsoft and System V
    * **Microsoft**: The "this" pointer is passed ECX, other parameters work like stdcall
    * **System V**: Works like cdecl, but the "this" pointer is the first argument to the function
* C++ name mangling is a more complex topic (and somewhat compiler dependent)


## Calling Conventions: x64

* Only one convention for each (Mostly... there are oddballs like vectorcall, but we won't discuss those)
* **thiscall** on x64 (both conventions) passes the "this" pointer as an implicit first argument (as it does for System V x86)
* Both conventions work similarly to **_fastcall**, passing arguments in registers (though the registers differ between platforms)

### Microsoft x64 Calling Convention

* Uses 4 registers to pass the first 4 parameters (RCX, RDX, R8, R9)
* Floating point values are passed via SIMD registers (XMM0-3... we'll talk more about this later)
* Remaining values are added to the stack
* Caller's responsibility to clean up (as with _cdecl)
  
#### Shadow Space

* x64 Calling conventions require stack allocation for passed variables
* Intent is to allow funciton being called to immediately spill registers (if desired)
* Windows API requires space to be allocated for 4 registers (regardless of function parameter count)
* Additional arguments (beyond 4) are added via the stack
    * But in the location they would normally occur at if all parameters were passed that way
    * Example: param 5 would begin at [rsp + 0x20]
* Caller must create the stack allocation for passed variables

##### Microsoft x64 Calling Convention

* **No parameters:**
  
```nasm
callee:
    ; ...
    ret

caller:
    sub rsp, 0x20       ; 8 * 4 - for register spillage
    call callee
    add rsp, 0x20       ; cleanup
```

* **5 or more parameters:**

```nasm
; caller
sub rsp, 0x28           ; space to store 5 params
mov rcx, 0x41           ; param 1 = A
mov rdx, 0x42           ; param 2 = B
mov r8, 0x43            ; param 3 = C
mov r9, 0x44            ; param 4 = D
mov [rsp + 0x20], 0x45  ; param 5 = E
call myfunc             ; callee
add rsp, 0x28           ; cleanup
```

* Some additoinal reading on MS x64 calling convention:
    * [MS x64 Calling Convention](https://blogs.msdn.microsoft.com/oldnewthing/20040114-00/?p=41053/)

### System V x64 Calling Convention

* Similar to the Microsoft calling convention, but more values are passed via registers
* The first 6 arguments are passed via register (RDI, RSI, RDX, RCX, R8 and R9)
* Floating point arguments go in SIMD registers (XMM0-7)
* Additional arguments are pushed onto the stack
* Shadow space is not required, but the stack must remain 16-byte aligned
* Red zone optimization provides free stack space for leaf functions

#### Red Zone

* Allows use of the next 128 bytes below RSP without modifying stack pointer
* Further function calls WILL clober space
    * Because of this, Red Zone use is most suitable for leaf functions
    * Safe from interrupt handlers, etc
    * **Leaf Functions** are simply functions that do not call other functions

##### System V x64 Example 

* **Calling strlen**

```nasm
extern strlen       ; more to come on this

; ensure NULL termination!
mystring db "this is a string", 0x00    ; more to come on this

call_strlen:
    mov rdi, mystring
    call strlen
    ret
```

### Return Values

* Typically, the value returned at the end of the function call will be stored in RAX 9for x64) or EAX (for x86)

### Register Preservation

#### x86

* Volatile: EAX, ECX and EDX don't need to be saved during a function call
* All others must be preserved
* What does this mean?
    * Volitle registers are scratch registers and are not gurenteed to retain their values after a function call (they are presumed by the caller to be destoryed across a call)
    * Nonvolatile registers are required to retain their values across a function call and must be saved by the calle if used
    * This is done by the compiler automatically via a push onto the callers stack frame to preserve non-volitle registers, unless you built the caller. Then preserve where needed. 

#### x64

* **Windows:** Volatile Registers (don't need to be reserved by callee)
    * RAX, RCX, RDX, R8, R9, R10 and R11
    * XMMO-3 and 5
    * All others need to be preserved by the callee
* **System V:**
    * Most registers are volatile (need to be preserved by caller if the values are to be retained)
    * Exception: RBP, RBX and R12-15 are non-volatile (must be preserved by callee)

* This is all important because you need to know when and how to preserve registers as you build callers and callees. 

### Additional Links

* [More on both x64 calling conventions](https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/)

---
# Lab 9 - Windows Functions Lab

* Edit using instructions on how to setup Visual Studio

<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/tree/master/04_ASM_Control_Flow/Lab_9" rel="Continue to Lab 9"> Continue to Lab 9 </a>
