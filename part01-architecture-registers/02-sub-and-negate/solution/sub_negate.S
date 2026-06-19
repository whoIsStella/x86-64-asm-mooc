.intel_syntax noprefix
.text
.globl sub_negate
.type sub_negate, @function
sub_negate:
    mov rax, rdi
    sub rax, rsi
    ret
.size sub_negate, .-sub_negate
