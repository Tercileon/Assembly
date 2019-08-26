|[Table of Contents](/00-Table-of-Contents.md)|
|---|

---

# Flags

When we talk about flags in assembly, we are refering to a register that contain a variety of bits representing state and status information. This register varies in size, but many portions (in newer processors) aren't used. 

| **FLAG** | **Size** |
| :--- | :--- |
| FLAGS | 16 bits |
| EFLAGS | 32 bits |
| RFLAGS | 64 bits |

![](/imgs/eflags.png)

---

## Flags we Care About Now

### Zero Flag (ZF)

* Set when an operation that sets the zero flag produces a zero- includes arithmetic and bitshift operations
* In otherwise, this flag gets set if an arthmetic result is zero

### Carry Flag (CF)

* Set when an arithmetic borrow or carry occurs during add/sub - e.g. the result of an add would have set bit 33 (in x86), or bit 65 (in x86_64)
    * Also set with some bitshift operations (such as when a bit falls of the end in a shr/shl)
    * This deals with **unsigned** numbers
    * Can happen when two unsigned numbers were added and the result is larger than the "capacity" of register where it is saved
        * Ex: We add two 8 bit numbers and the saved result is larger than the 8 bit register we store it in
    * Also set when two unsigned numbers were subtracted and we subtract the larger one from the smaller one

### Overflow Flag (OF)

* Indicates that sign bit of the result of an operation is different than the sign bits of the operands
    * Ex: Adding two large positive numbers ends up producing a negative result (due to overflow)
    * Ex: If we subtract two numbers that are smaller than register size (-129 for 8bit)
    * This applies to **signed numbers**

### Sign Flag (SF)

* Set to indicate the result of an operation is negative

## Accessing the Flags

* Can be set and checked manually
    * Some have special instructions for set and clear (which we'll talk about later)
    * Flag register can be accessed and set manually via pushf(d|q)/popf(d|q)
    * Refer to below (pushf popf)

## pushf and popf

* **Description**
    * Pushes the flag register (or the first 16 bits... eflags(32 bits) or rflags(64 bits) if pushfd or pushfq) onto the stack, and pops the value on top of the stack into the flags register (or eflags/rflags)
    * Higher 32 bits in rflags are reserved
        * Thus we can just handle rflags as eflags, doesn't make a difference
    * In reality, the flags we will be accessing are within the first 16 bits

* **Basic Use**

```nasm
pushf       ; flags have been pushed to the stack
; ... do stuff
popf        ; flags have been restored
```

* **How does this really work?**

    * First you specify how much of the flags you want to push onto the stack (pushf)
    * From there, you can pop those back off into a register (pop reg, rax for example)
    * From there you can modify the value in that register
    * From there you can push that register back onto the stack (pushf)
    * Finally you can pop the flag off, taking the new value with it. (popf)

---
**Complete Performance Lab:** 6

|[Lab 6](/04_ASM_Control_Flow/Lab_6/README.md)|
|---|
