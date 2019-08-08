<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" > Return to TOC </a>

# Negative Numbers and Bitwise

## Negative Numbers

### Two's Complement

* You may remember this from C, we touched on it slightly. 
* Negative numbers of the x86(_64) platform are represented via Two's Complement
* In short, two's complement is just a way to tell between negative and positive numbers on the binary level
* Positive numbers remain mostly unchanged from what we have learned in previous courses. 0011 for instance is 3. 
* Negative numbers on the other hand use the "complement" of positive numbers. So instead of starting at 0000... negative numbers start at 1111. The 1s and 0s are flipped. 
* If the left most bit is 0, then the number is positive. 1 is negative. 

---

* To get the negative version of a number... take the positive number, subtract by 1, then invert. 
* This may be hard to understand at first, but let's look at it via positive numbers first. Use the decimal to bin chart below as reference.  
    * 3 = 0011
    * Let's get -3
    * Subtract 1 from 3 (3-1= 2)  (2 = 0010)
    * Invert: -3 = (1101) aka 0010 inverted is 1101

* **Let's take a look at another example!**
    * 4 = 0100 (we want -4)
    * Subtract 1: 3 = 0011
    * Invert: 1100 = -4

| **Decimal** | **Positive Bin** | **Negative Bin** |
| :-- | :-- | :-- |
| 1 | 0001 | 1111 |
| 2 | 0010 | 1110 |
| 3 | 0011 | 1101 |
| 4 | 0100 | 1100 |

--- 

### Two's Complement Pros

* Simplified addition operations
* Unified add/sub

* **Example: Adding 2 and -1**

```
Carry Row:    11
              1111
            + 0010
              ----
              0001
```

### Two's Complement Cons

* There aren't too many downsides to Two's Complement. The biggest downside, is that signed numbers have a smaller range in order to account for the extra bit that determines sign. 
---

## Sub Registers and Sign Extending

* When copying smaller data into a register, sign extending may be used (rather than zero extending)
* Sign extending preserves the "signed" attributes of the data being copied
* The movsx instruction (just like movzx) handles this

### The movsx Instruction

* **movsx**
* **Description**
    * Must like movzx, movsx can be used to move data into a portion of a larger register, while preserving its sign

---

## Bitwise Operations

### Bit Shifting

* **Two unsigned shift operations:**
    * **shl** - shift left
    * **shr** - shift right
* Shifting moves the bits in the register over the direction (left or right) and number of bits specified
* Bits that fall off the end (and overflow) will disappear, except for the last one, which ends up in the carry flag (more to come on this)
* Extra space is padded with 0's

#### Left Shift

* The following snippet of assembly:

```nasm
mov rax, 1
shl rax, 1
shl rax, 3
```

* Can be modeled by the following table:

| **Decimal** | **Binary** | **State** |
| :--- | :--- | :--- | 
| 1 | 00000001 | Initial |
| 2 | 00000010 | shl rax, 1 |
| 16 | 00010000 | shl rax, 3 |

#### Right Shift

* Similarly, the following snippet of assembly:

```nasm
mov rax, 32
shr rax, 1
shr rax, 4
```

* Can be modeled by the following table:

| **Decimal** | **Binary** | **State** |
| :--- | :--- | :--- | 
| 32 | 00100000 | Initial |
| 16 | 00010000 | shr rax, 1 |
| 1 | 00000001 | shr rax, 3 |

---

### Binary and/or

* **and** can be used to determine whether or not one or more bits are set on
* **or** will tell you if the bit is set on at least one place
* Both take two operands, left will hold the result after the operation completes
* Use:

```nasm
mov rax, 1              ; rax contains 00000001
mov rcx, 5              ; rcx contains 00000101

and rax, rcx            ; rax contains 00000001
or rax, rcx             ; rax contains 00000101
```

#### And Table

| **Set** | **Binary** |
| :--- | :--- |
| First | 01010011 |
| Second | 01000010 |
| Result | 01000010 |

#### Or Table

| **Set** | **Binary** |
| :--- | :--- |
| First | 01010011 |
| Second | 01001010 |
| Result | 01011010 |

### Binary Not

* Inverts the bits in a given register
* **Example:**

```nasm
mov rax, 0              ; rax now contains 00000000
not rax                 ; rax is now all 1's (or 0xffffffff)
```

* Similarly: 

```nasm
mov rcx, 1              ; rcx now contains 1 (8bit: 00000001)
not rcx                 ; rcx now contains 0xfffffffe (8bit: 11111110)
```

### XOR

* **XOR** yields 1 only if the bit is set in either the source or the destination, but not both
* Any value XOR'd with itself is 0 (Make sense now?)
* 0 XOR'd with any value is that value
* For numbers A, B and C, if A ^ B = C, then C ^ A = B, C ^ B = A

#### XOR Table

| **Assembly** | **First Value** | **Second Value** | **Result** |
| :--- | :--- | :--- | :--- |  
| xor rax, rax | 01010011 | 01010011 | 00000000 |
| xor rax, rcx | 01000010 | 01001010 | 00001000 | 
| xor rcx, rax | 01001010 | 00001000 | 01000010 |

### Rotating Bits

* The values in the register are rotated the indicated number of places to the right or left
* Bits that are rotated off the end of the register are moved back to the other side. 
* **Instruction:**

```nasm
mov rax, 1      ; rax contains 1 (00000001)
rol rax, 1      ; rax contains 2 (00000010)
ror rax, 1      ; rax contains 1 (00000001)
ror rax, 1      ; rax now looks like (10000000)
```

### Signed Bit Operations

* Shift operations that are signed aware exist (SAR for right and SAL for left)
* Work in the same fashion as shr/shl, except for how bits shifted off the end are treated (bits still disappear, but the sign of the resulting value is retained)

---

## Lab 5

<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/tree/master/03_ASM_Basic_Operations/Lab_5" > Continue to Lab 5 </a>
