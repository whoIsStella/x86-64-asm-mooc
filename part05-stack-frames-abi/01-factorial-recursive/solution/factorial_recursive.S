.intel_syntax noprefix
.text
.globl factorial
.type factorial, @function
factorial:
    # Recursive factorial(n): returns n! for n >= 0.
    # On entry: rsp % 16 == 8 (return address was pushed by caller's call).
    #
    # We push rdi (8 bytes) to save n across the recursive call.
    # After the push, rsp % 16 == 0, so we sub 8 more to restore 16-byte
    # alignment before the call instruction (rsp % 16 must be 0 at the
    # call site so that on entry to the callee rsp % 16 == 8).
    #
    # Stack layout at call site:
    #   [rsp+8]  = saved n (rdi)
    #   [rsp+0]  = 8-byte alignment pad
    #   caller's return address is above our frame

    # Base case: if n <= 1, return 1.
    cmp rdi, 1
    jle .Lbase

    # Recursive case.
    push rdi            # save n; rsp now 16-byte aligned after this push
                        # (was 8 mod 16 on entry, minus 8 = 0 mod 16)
    sub rsp, 8          # alignment pad so call sees rsp%16==0 -> on callee entry rsp%16==8

    lea rdi, [rdi - 1]  # n - 1
    call factorial

    # rax = factorial(n-1); restore n from stack.
    add rsp, 8          # remove alignment pad
    pop rdi             # restore n
    imul rax, rdi       # rax = n * factorial(n-1)
    ret

.Lbase:
    mov rax, 1
    ret
.size factorial, .-factorial
