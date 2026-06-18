.intel_syntax noprefix
.text
.globl find_byte
.type find_byte, @function
find_byte:
    # rdi = s, rsi = n, rdx = target (byte)
    # Returns index of first matching byte, or -1 if not found.
    xor rcx, rcx                # i = 0
.Lloop:
    cmp rcx, rsi                # if i >= n, done
    jge .Lnot_found
    movzx eax, byte ptr [rdi + rcx]   # load s[i] (zero-extend)
    cmp al, dl                  # s[i] == target?
    je  .Lfound
    inc rcx
    jmp .Lloop
.Lfound:
    mov rax, rcx                # return i
    ret
.Lnot_found:
    mov rax, -1
    ret
.size find_byte, .-find_byte
