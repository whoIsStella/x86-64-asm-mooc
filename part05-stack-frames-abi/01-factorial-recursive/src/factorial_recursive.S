.intel_syntax noprefix
.text
.globl factorial
.type factorial, @function
factorial:
    # TODO: implement factorial(n) recursively.
    # SysV AMD64: n in rdi, return in rax.
    # Base case: n <= 1 returns 1.
    # Recursive case: save rdi (and align stack!), call factorial(n-1),
    #   then multiply rax by the saved n.
    # Remember: rsp must be 16-byte aligned before any call instruction.
    xor rax, rax
    ret
.size factorial, .-factorial
