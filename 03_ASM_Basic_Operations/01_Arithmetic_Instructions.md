<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" rel="Return to TOC"> Return to TOC </a>

# Arithmetic Instructions

![](/imgs/math.jpg)

## The add and sub Instructions

* **Description:**
    * Adds and subtracts arbitrary values. The destination (where the result is stored) is the first value provided.(The left value)
* **Basic Use:**
    * We can use a combination of registers and immediates as operands: 

```nasm
mov rax, 1
add rax, 2      ; rax now contains 3
sub rax, 1      ; rax now contains 2
mov rcx, 2
add rax, rcx    ; as above, rax now contains 4
sub rax, rcx    ; rax is now back to 2
```

---

## The mul Instruction

* **Description:**
    * Allow multiplication of arbitrary values. Takes a single argument, multiples rax/eax/ax (depending on operand size) by *src (whatever follows mul instruction)*. Result is stored in rax/eax/ax. 
* **Basic Use:**

```nasm
mov eax, 10
mov ecx, 10
mul ecx             ; rax now contains 100

mov rax, 5
mov rcx, 7
mul rcx             ; rax now contains 35
```

---

### Mul: Storing Results
* Results are stored in the source (possible), or in a combination of registers in the configuration below:

| **Operand Size** | **First Source** | **Destination** |
| :--- | :--- | :--- |
| byte | al | ax |
| word | ax | dx:ax | 
| dword | eax | edx:eax |
| qword | rax | rdx:rax |

---

## The div Instruction

* **Description:**
    * As with mul, div takes a single argument, and divides the value stored in the dividend register(s) by it. This is typically AX/EAX/RAX (and the *dx equivalents), but may vary a bit depending on the size.
    * RDX is also needed. RDX is where the remainder will be stored. This register will need to be set to 0 before division can take place. Otherwise you'll get a SIGFPE. 
    * **Tl;Dr:** RAX/src (src = rcx in this case). Results stored in RAX, remainder stored in RDX. 
* **Basic Use:**

```nasm
; clearing the register where the
; high bits would be stored, we're only using what's in rax!
mov rdx, 0
mov rax, 10
mov rcx, 2
div rcx         ; rax now contains 5
```

### Div: Storing Results
* Where to retrieve the results of a div from depends on the size of the arguments. The table below illustrates this relationship:

| **Maximum** | **Dividend** | **Quotient** | **Remainder** |
 :--- | :--- | :--- | :--- |
| byte/word | ax | al | ah |
| word/dword | dx:ax | ax | dx |
| dword/qword | edx:eax | eax | edx |
| dqword/qword | rdx:rax | rax | rdx |

---

## inc and dec

* **Description:**
    * Adds or subtracts one from the provided register, storing the result in place.
* **Basic Use:**

```nasm
mov rax, 1      ; rax now contains 1
inc rax         ; rax now contains 2
inc rax         ; rax now contains 3
dec rax         ; rax now contains 2
```

---

<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/03_ASM_Basic_Operations/02_The_Stack.md" > Continue to Lab 3 </a>
