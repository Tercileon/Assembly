<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" rel="Return to TOC"> Return to TOC </a>

# Section 1.2: Assembly Basics & Memory

Now that we understand some basic computer concepts, we can hop into Assembly with a bit more understanding of some of it's underlying concepts. 

## Understanding Assembly

### What is assembly? 
Assembly provides "instructions" (aka human-friendly) that map to "opcodes" (aka processor-friendly). Assembly is typically very hardware-specific. 

### Why use assembly?
There are a number of reasons to use assembly. The most common reason is performance. Rather than letting the compiler come up with possibly long and drawn out assembly on compilation, create the asm yourself for better optimization (where it applies). Assembly also exploses hardware features that may not have been avalaible. Lastly, another reason to use assembly is that some operations are easier to express than in higher level languages such as C. 

### Assembly Instructions and Opcodes
#### Operands
Assembly code typically consist of an instruction of some kind and some operands. Operands can consist of several things, such as *Registers*, *Memory Addresses*, and *Immediate (literal) Values*. There are also other data types and some prefixes (which modify what the instruction does). We will dive deeply into a ton of all of the above. 

#### Opcodes
Opcodes are one or more bytes that the processor decodes (and executes). Typically opcodes translate directly from assembly language instructions, thus the syntax is slightly complicated. Opcodes can be different sizes depending on the system architype. 

#### Instructions
* This set of instructions:
 ```nasm
mov eax, 0x01
ret
 ```
 * Becomes:
```
0xb8 0x01 0x00 0x00 0x00
0xc3
```

### Assemblers and Syntax
There are a number of different assemblers to choose from. With different assemblers comes different syntaxes. There are some other slight differences and quirks depending on the Assembler you choose. Here are some of the different assemblers to choose from:
* GAS: The GNU Assembler
* NASM/YASM: The Netwide Assembler/Yet Another Assembler (a rewrite of NASM)
* MASM: The Microsoft Assembler

**We will be using NASM on this course which uses Intel Syntax**

#### Syntax Differences
* Intel Syntax (Used by NASM/YASM and others):
```nasm
mov eax, 0x01
```
* AT&T Syntax (Used by GAS and others)
```
movl $0x01, %eax
```
* Other syntaxes do exist

---

### Byte Ordering
**Byte ordering** determines the order in which bytes appear in memory. As Americans (and even humans in most cases), we are conditioned to read things left to right. Computers are not the same though. They can read data in any which way. In our case, we are only concerned with how a computer determines the order to read bytes in memory. 

* **Big Endian** stores the most significant bytes (or largest) value first. 
    * So for instance, the memory address: 0x10203040 would appear as... 0x10 0x20 0x30 0x40

* **Little Endian** on the other hand stores the least significant bytes (or smallest) firsst. 
    * For instance, the memory address: 0x10203040 would appear as... 0x40, 0x30, 0x20, 0x10
    * **Little Endian** is what x86(_64) uses. 
    * Again, least significant byte (not bit) is what appears first. 
    * In memory, this address:
        ```
        0xdeadbeef
        ```
    * Becomes:
        ```
        0xefbeadde
        ```
    #### Breakdown
    | **Initial:** | 0xde | 0xad | 0xbe | 0xef |
    | **Memory:** | 0xef | 0xbe | 0xad | 0xde | 

### Memory
When talking about memory, we need to understand first that there are multiple different types of memory components. These memory components vary in access speed. Most higher level languages (Such as C or Python) abstract this concept away so that the developer is not very exposed to it. Assembly on the other hand gives you more control (some things are still hidden on modern systems)

#### Memory: Fastest to Slowest
1. Registers
2. Cache (L1/L2/L3)
3. System Memory (RAM) 
4. Disk (HDD/SDD/etc) 
                      
#### Virtual Memory
Virtual Memory is a feature of modern operating systems that add a bit of abstraction from the hardware. Most addressing deals with virtual addresses, that is to say, if we want to access an address we do so by utilizing virtual addresses. These addresses are translated (via the lookup table) to physical addresses. 

    **Additional Features of Virtual Memory:**
    * More than one "view" of of a physical memory address can exist (in different processes). That means we can access the same physical memory address through the use of multiple virtual addresses. 
    * Each user mode process appears to have a full range of addressable memory and resources
    * Most modern OS's support paging. 

#### Memory: Process Memory Layout
**Below is a very high level view of the Process Memory Layout:**

![](/imgs/process_mem.png)

* Stack segments typically grow from high memory addresses to low.
    * I know many of us may have forgotten what the stack was, but no need to worry. We will go very deep and technical on the stack in the next section. 
* Modules in the diagram above indicate executable files loaded into the file space. This includes:
    * Glibc (specifically the .so containing the libc code)
    * kernel32.dll
    * Currently running executable
* There are also the HEAP sections and anonymous mappings
* Kernel Memory
* Other Items

---

### Registers
Assembly programming gives us total control over access to registers. We are also given access to special hardware instructions on the processor. Some registers are general purpose (can store any type of data) while others are more specialized. These specialized registers can contain: status codes, flags, or be associated to specific hardware. Registers are limited in number and that number depends on a number of factors to include chip and architecture. 

#### General Purpose Registers
General Purpose Registers give us access to subregisters. Depending on the processor, registers will have a set maximum size, different naming conventions, etc. The larger the size, the more subregisters we have. Let's break it down a bit further: 
* There are four main type of register sizes: 64bit/32bit/16bit/8bit.
    * If you have a 64bit system, you have access to 64bit registers and their subregisters
        * The subregisters of a 64bit system are simply: 32bit/16bit/8bit. 
    * The same is for any size
* Sub registers are **NOT** their own register. They simply act as a way of only modifying a certain number of bits of the total size register, depending on the processor. So if we have a 64bit CPU and access the 18bit subregister of one of the 64bit registers, only the lower 18bits get accessed/modified. There are of course exceptions to higher/lower, etc. Which we will cover later. 
    * Keep that in mind when modfying a subregister. You will modify that many bits in the actual register too. 
* x86(_64) contains many more registers than just x86. But not all of those registers have subregisters. 

### x86(_64) Registers

| **64bit** | **32bit** | **16bit** | **8bit high/low** |
 :--- | :--- | :--- | :--- |
| rax | eax | ax | ah/al | 
| rcx | ecx | cx | ch/cl | 
| rdx | edx | dx | dh/dl | 
| rdi | edi | N/A | N/A |
| rsi | esi | N/A | N/A | 

* There are other registers:
    * rbp/ebp: Base Pointer 
    * rsp/esp: Stack Pointer (More to come on both of these)
    * rip/eip: Instruction Pointer (or Program Counter) 
    * Additional x86(_64) registers: r8-r15

### Register Data and Pointers 
* General Purpose Registers can contain up to pointer-sized amounts of data (4 bytes on 32bit, 8 on 64bit)
* They can also contain memory addresses (pointers) to blocks of data residing elsewhere in the process. 
* Addresses can be manipulated via addition, subtraction, multiplication, etc
* Square brackets dereference (Access the data stored at the memory address) 
    * Example:
    ```nasm
    ; a register we will be acting on whatever is directly stored in it (address or data)
    rax
    
    ; a register that we assume has an address to some data
    ; We are attempting to access that data and manipulate it
    [rax]
    ```

    * Let's do another example:
    ```nasm
    mov rax, 0xc0ffee   ; a memory address, hopefully valid! (What happens if it's not?)
    mov [rax], 100      ; now we store some data in that address

    ; now let's copy that address to another register
    mov rcx, rax        ; Both rax and rcx point to the same location, right?
    ```

    ![](/imgs/dereference.png)

    * Now let's copy the data stored at the address, and put it into RCX

    ```nasm
    mov rcx, [rcx]
    ```

    ![](/imgs/dereference2.png)

    * How does this work? 
        * RCX is currently holding an address. To be even more specific, RCX's data is a numeric value... 
        * We tell the assembler that RCX's data, though numeric, represents a address and that we want to access it. That's where the dereference blocks come in []. 
        * The assembler then says: Okay, this is an address. Let me access it. 
        * After the assembler accesses it... we grab the data that's at that address and pull it out and store it back into RCX... replacing the address. 
        * In summary:
            * [UNCHANGED] the address itself (It's no longer being pointed to by RCX though)
            * [UNCHANGED] the data that's at the address (We stored 100 in there, but never acted on it since)
            * [CHANGED] the value stored in RCX (to whatever data was in the address)
    * What happens if you try to mov a dereferenced address value into a dereferenced address value?

---

## Instructions 

#### NOP 
* Does nothing (Kinda sorta)
* Used for padding/alignment and timing reasons
* Idempotent instruction (does not affect anything else in the system)
* 1 byte NOP instruction translates to opcode 0x90 (more to come on this)

### Memory Access
We'll begin looking at instructions to copy and access data from various locations in memory. Additionally, we will begin examining address calculation

#### mov instruction
* The mov instruction moves a small block of memory from a source (right hand operand) to the destination (left hand operand)
* Amount of data can be specified (will go over later)
* Basic usage:

```nasm
mov rax, 0x01           ; immediate - rax is now 1
mov rax, rcx            ; register - rax is now a copy of rcx
mov rax, [rbx]          ; memory - rbx is treated as pointer, it's data is copied into rax
mov rax, qword [rbx + 8]; copying a quad word (8 bytes) into rax
```

* Notice the repeated usage of "copy"? Just because the instruction is "mov", doesn't mean we are moving anything.

#### lea instruction
* Load Effective Address Instruction 
* Calculates an address, but does not attempt to access it
* This is useful when wanting to use address calculation (ex: [rdx+4]) but not wanting to change the address
* For example:

```nasm
; calculate the address by taking the address of what rdx points at, /
; and adding 8 bytes to it (prehaps indexing into an array?)
; NOTE: We are just calculating the addressses, not changing them!

lea rax, [rdx + 8]
mov rax, [rax]          ; this will access whatever was in rdx + 8

; what's different from above vs

mov rax [rdx, + 8]

; or...
add rdx, 8
mov rax, [rdx]
```

#### xchg instruction
* Exchange instruction
* Exchanges the values provided atomically. 
    * In other words, it **SWAPS** the values. 

```nasm
xchg rax, rcx   ; exchange two register values
; exchange a register value with a value stored in memory
xchg rax, [rcx]

; live example
mov rax, 10
mov rcx, 20

xchg rax, rcx   ; what is the value or rax and rcx now?
mov rcx, 0xdeadbeef     ; setting rcx to a address
mov [rcx], 0
xchg rax, [rcx] ; what is the value of rax and rcx now?
```

---
<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/02_Intro_to_ASM/03_Debugging_ASM_pt1.md" rel="Continue to Next Topic"> Continue to Next Topic </a>
