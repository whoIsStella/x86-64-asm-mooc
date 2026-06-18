.intel_syntax noprefix
.text
.globl weekday_len
.type weekday_len, @function
weekday_len:
    # TODO: use RIP-relative lea to load from .rodata table.
    # day in edi; return length in eax or -1 for out-of-range.
    mov eax, -1
    ret
.size weekday_len, .-weekday_len
