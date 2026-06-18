.intel_syntax noprefix
.text
.globl array_sum
.type array_sum, @function
array_sum:
    # rdi = pointer to array, rsi = n (unsigned long)
    # rax = accumulator (return value)
    # rcx = index i
    xor rax, rax          # sum = 0
    xor rcx, rcx          # i = 0
.Lloop:
    cmp rcx, rsi          # i < n ?
    jae .Ldone            # if i >= n (unsigned), exit
    mov r8, [rdi + rcx*8] # load a[i]
    add rax, r8           # sum += a[i]
    inc rcx               # i++
    jmp .Lloop
.Ldone:
    ret
.size array_sum, .-array_sum
