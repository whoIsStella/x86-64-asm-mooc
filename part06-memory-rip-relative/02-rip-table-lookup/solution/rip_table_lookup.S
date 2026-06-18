.intel_syntax noprefix

/* Lengths of weekday names: Mon(6) Tue(7) Wed(9) Thu(8) Fri(6) Sat(8) Sun(6) */
.section .rodata
.align 4
weekday_lengths:
    .int 6, 7, 9, 8, 6, 8, 6

.text
.globl weekday_len
.type weekday_len, @function
weekday_len:
    # edi = day (0=Mon .. 6=Sun)
    # Bounds check: 0 <= day <= 6
    cmp edi, 0
    jl  .Lout_of_range
    cmp edi, 6
    jg  .Lout_of_range
    # RIP-relative load from .rodata table
    lea rax, [rip + weekday_lengths]
    movsx eax, dword ptr [rax + rdi*4]
    ret
.Lout_of_range:
    mov eax, -1
    ret
.size weekday_len, .-weekday_len
