.intel_syntax noprefix
.text
.globl reverse_copy
.type reverse_copy, @function
reverse_copy:
    # TODO: copy n bytes from src to dst in forward order.
    # dst in rdi, src in rsi, n in rdx.
    # IMPORTANT: if you use std, you MUST restore DF with cld before ret.
    # The SysV ABI requires DF to be clear on function return.
    # This stub intentionally omits cld after std — tests will fail.
    std
    # ... (incomplete: no actual copy, and DF left set)
    ret
.size reverse_copy, .-reverse_copy
