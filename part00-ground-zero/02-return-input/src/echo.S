.intel_syntax noprefix
.text
.globl echo
.type echo, @function
echo:
    # TODO: return the argument unchanged.
    # The first argument arrives in rdi; the return value must be in rax.
    # The stub ignores rdi and returns 0, so the test starts RED.
    mov rax, 0
    ret
.size echo, .-echo
