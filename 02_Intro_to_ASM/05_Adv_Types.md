<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" rel="Return to TOC"> Return to TOC </a>

# Advanced Types and Concepts

## Structures

* NASM provides a data structure concept for convenience in hanlding complex data types
* More of a macro than something representative of a C-style struct
    * So try not to compare this to a C-style struct too much
* Very useful for keeping track of local variables or parameters (among other things)

```nasm
struc MyStruct
    .field1         resd 1      ; field1's size is 1 dword
    .field2         resd 1      ; field2's size is 1 dword
    .field3         resq 1      ; field3's size is 1 qword
    .next           resd 1      ; next's size is 1 dword... address to next node in linked-list (if this were a linked list)
endstruc

; ...
; Let's assume rdi points to MyStruct
; This will be equivalent to: mov rax, [rdi+8]
mov rax, [rdi + MyStruct.field3]

; Assuming this is a linked list
mov rdi, [rdi + MyStruct.next]

; After the instruction above is ran... we are now on the next node. 
```

---

## Array Iteration

* Iterating through an array requires knowing the size of the elements within it. 
* To iterate through an array, you simply dereference the address and add the amount of bytes to the next element. 

```nasm
; assume rsi is storing the address to an array of characters
mov rax, [rsi]      ; this gives us the first character
mov rax, [rsi+1]    ; this gives us the second character
mov rax, [rsi+5]    ; this gives us the sixth character
mov rax, [rsi]      ; this still gives us the first character

; there is also this method, not recommended if it can be avoided
inc rsi             ; this will set rsi to the second character
mov rax, [rsi]      ; this will give us the second character

; The above works great, now let's assume it's a array of ints
; ints are generally 4 bytes
; We can use another method to allow for itteration

mov rax, [rsi]          ; still grabs first int
mov rcx, 2              ; let's grab third element, by setting a count
mov rax, [rsi+rcx*4]         ; this is essientially rcx * 4 (so count x size) and adding it to the array's address

; As well as with characters, there is this method
add rsi, 4          ; next iteration
mov rax, [rsi]      ; next itterations value
add rsi, 4
mov rax, [rsi]      ; third value
; ...
```

<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/03_ASM_Basic_Operations/README.md" rel="Continue to Next Topic"> Continue to Next Topic </a>


