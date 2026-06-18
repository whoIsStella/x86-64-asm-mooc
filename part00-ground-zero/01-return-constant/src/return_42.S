.intel_syntax noprefix
.text
.globl return_42
.type return_42, @function
return_42:
    # TODO: put 42 into the return register rax, then return.
    # The line below returns 0, so the test starts RED. Change the 0 to 42.
    mov rax, 0
    ret
.size return_42, .-return_42
