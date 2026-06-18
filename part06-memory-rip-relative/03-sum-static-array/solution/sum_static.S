.intel_syntax noprefix

/* Static array of longs in .rodata, accessed via RIP-relative addressing. */
.section .rodata
.align 8
static_array:
    .quad 10, 20, 30, 40, 50
static_array_end:

.text
.globl sum_static
.type sum_static, @function
sum_static:
    # Load the address of static_array via RIP-relative lea.
    lea rdi, [rip + static_array]
    lea rsi, [rip + static_array_end]
    xor rax, rax                # accumulator = 0
.Lloop:
    cmp rdi, rsi
    jge .Ldone
    add rax, qword ptr [rdi]
    add rdi, 8
    jmp .Lloop
.Ldone:
    ret
.size sum_static, .-sum_static
