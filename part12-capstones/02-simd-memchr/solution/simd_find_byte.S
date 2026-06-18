/* simd_find_byte — SSE2 16-byte-at-a-time byte search.
 *
 * long simd_find_byte(const unsigned char *s, unsigned long n, unsigned char c)
 *   Returns index of first byte equal to c, or -1 if not found.
 *
 * Strategy:
 *   1. Broadcast c into xmm1 (all 16 lanes).
 *   2. Vector loop: while n >= 16, load 16 unaligned bytes, pcmpeqb,
 *      pmovmskb -> 16-bit mask; if nonzero, bsf finds the first match.
 *   3. Scalar tail: check remaining < 16 bytes one at a time.
 *
 * SysV AMD64 ABI:
 *   rdi = const unsigned char *s
 *   rsi = unsigned long n
 *   rdx = unsigned char c  (zero-extended into edx)
 *   return long in rax
 */

.intel_syntax noprefix
.text
.globl simd_find_byte
.type simd_find_byte, @function

simd_find_byte:
    /* Broadcast c (low byte of edx) into all 16 bytes of xmm1.
     * movd:       xmm1 = [c, 0, 0, ..., 0]  (15 zero bytes)
     * punpcklbw:  xmm1 = [c,c, 0,0, 0,0, 0,0, ...]  (interleave low 8 with themselves)
     * punpcklwd:  xmm1 = [c,c,c,c, 0,0,0,0, ...]    (interleave low 4 words)
     * pshufd 0:   xmm1 = [c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c]  (broadcast dword 0)
     */
    movd      xmm1, edx
    punpcklbw xmm1, xmm1
    punpcklwd xmm1, xmm1
    pshufd    xmm1, xmm1, 0

    /* rcx = byte index so far */
    xor     rcx, rcx

.Lvec_loop:
    cmp     rsi, 16
    jb      .Ltail              /* fewer than 16 bytes left: scalar tail */

    movdqu  xmm0, [rdi]         /* load 16 unaligned bytes */
    pcmpeqb xmm0, xmm1          /* xmm0[i] = 0xFF if s[i]==c, else 0 */
    pmovmskb eax, xmm0          /* eax bit i = MSB of xmm0 byte i */
    test    eax, eax
    jnz     .Lfound_vec         /* at least one match */

    add     rdi, 16
    add     rcx, 16
    sub     rsi, 16
    jmp     .Lvec_loop

.Lfound_vec:
    bsf     eax, eax            /* eax = index of lowest set bit = first match */
    add     rax, rcx            /* absolute index = chunk_offset + bit_pos */
    ret

.Ltail:
    /* Scalar scan of remaining rsi bytes */
    test    rsi, rsi
    jz      .Lnotfound

.Ltail_loop:
    movzx   eax, byte ptr [rdi]
    cmp     al, dl              /* compare with c (dl = low byte of rdx) */
    je      .Lfound_scalar
    inc     rdi
    inc     rcx
    dec     rsi
    jnz     .Ltail_loop

.Lnotfound:
    mov     rax, -1
    ret

.Lfound_scalar:
    mov     rax, rcx
    ret

.size simd_find_byte, .-simd_find_byte
