.intel_syntax noprefix
.text
.globl return_42
.type return_42, @function
return_42:
    mov rax, 42
    ret
.size return_42, .-return_42
