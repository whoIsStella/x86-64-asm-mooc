/* simd_find_byte stub — returns -1 always so hit-tests fail RED.
 *
 * SysV AMD64 ABI:
 *   rdi = const unsigned char *s
 *   rsi = unsigned long n
 *   rdx = unsigned char c  (zero-extended in rdx)
 *   return long index (or -1) in rax
 *
 * TODO: implement SSE2 16-byte-at-a-time scan:
 *   1. Broadcast c into all 16 lanes of an XMM register
 *      (movd + punpcklbw + pshuflw/pshufhw, or movd + punpcklbw twice + pshufd)
 *   2. While n >= 16: movdqu 16 bytes, pcmpeqb, pmovmskb, test; if hit: bsf
 *   3. Scalar tail for remaining < 16 bytes
 *   4. Return -1 if not found
 */

.intel_syntax noprefix
.text
.globl simd_find_byte
.type simd_find_byte, @function
simd_find_byte:
    /* TODO: implement SSE2 16-byte-at-a-time scan.
     * SysV AMD64: s in rdi, n in rsi, c in rdx, return index or -1 in rax. */
    mov rax, -1
    ret
.size simd_find_byte, .-simd_find_byte
