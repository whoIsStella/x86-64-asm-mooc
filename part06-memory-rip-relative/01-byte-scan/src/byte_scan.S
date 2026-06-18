.intel_syntax noprefix
.text
.globl find_byte
.type find_byte, @function
find_byte:
    # TODO: scan s[0..n-1] for target; return index or -1.
    # SysV AMD64: s=rdi, n=rsi, target=rdx (byte), return rax.
    mov rax, -1
    ret
.size find_byte, .-find_byte
