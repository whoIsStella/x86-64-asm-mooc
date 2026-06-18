.intel_syntax noprefix
.text
.globl reverse_copy
.type reverse_copy, @function
reverse_copy:
    # SysV AMD64: dst in rdi, src in rsi, n in rdx
    #
    # This function copies n bytes from src to dst in forward order.
    # It demonstrates correct direction-flag (DF) discipline:
    #
    #   * The SysV ABI specifies that DF MUST be clear (0) on both
    #     function entry and function exit.
    #   * If you ever use std to set DF, you MUST restore it with cld
    #     before returning — failing to do so corrupts subsequent callers
    #     that use string instructions (including C library functions like
    #     memcmp, strlen, strcpy).
    #
    # This solution uses rep movsb (forward copy, DF=0) which is
    # straightforward and ABI-correct.  The pedagogical point is contrast
    # with the stub, which calls std but never restores DF.
    #
    mov rcx, rdx    # rcx = n
    cld             # DF=0: forward copy (explicit; ABI requires it)
    rep movsb       # copy rcx bytes [rsi]->[rdi], both advancing
    # DF is still 0 here — correct ABI state on exit.
    ret
.size reverse_copy, .-reverse_copy
