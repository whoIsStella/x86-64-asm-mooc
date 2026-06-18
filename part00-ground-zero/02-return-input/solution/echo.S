.intel_syntax noprefix
.text
.globl echo
.type echo, @function
echo:
    mov rax, rdi
    ret
.size echo, .-echo
