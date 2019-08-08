bits 64

global first_func, second_func, third_func

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; INSTRUCTIONS
; -Set the flags via by arithmetic operation
; -Then set the flags manually*
; *You will need to comment out the previous solution 


first_func:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Set the carry flag.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

second_func:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Set the overflow flag.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

third_func:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Set both the carry and overflow
;  flags.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret


