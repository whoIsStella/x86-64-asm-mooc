.intel_syntax noprefix
.text
.globl add_two
.type add_two, @function
add_two:
    # TODO: return a + b. SysV AMD64 passes a in rdi, b in rsi, return in rax.
    # The line below returns 0, so the test starts RED. Replace it: copy a into
    # rax with `mov`, then `add` b into it. (See this exercise's README.)
    mov rax, 0
    ret
.size add_two, .-add_two
