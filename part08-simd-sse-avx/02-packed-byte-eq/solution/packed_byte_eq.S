.intel_syntax noprefix
.text
.globl count_equal_bytes
.type count_equal_bytes, @function
/* int count_equal_bytes(const unsigned char *a, const unsigned char *b)
 * SysV AMD64: a=rdi, b=rsi, return in rax (int)
 *
 * Strategy:
 *   movdqu  — load 16 bytes unaligned (double quadword)
 *   pcmpeqb — compare 16 byte lanes: 0xFF where equal, 0x00 where not
 *   pmovmskb— extract bit 7 of each byte into a 16-bit integer in a GP reg
 *   popcnt  — count the set bits (one per equal byte position)
 */
count_equal_bytes:
    movdqu  xmm0, [rdi]         /* xmm0 = a[0..15] */
    movdqu  xmm1, [rsi]         /* xmm1 = b[0..15] */
    pcmpeqb xmm0, xmm1          /* xmm0[i] = 0xFF if a[i]==b[i], else 0x00 */
    pmovmskb eax, xmm0          /* eax = 16-bit mask: bit i set iff xmm0 byte i has bit 7 set */
    popcnt  eax, eax            /* eax = number of set bits = number of equal bytes */
    ret
.size count_equal_bytes, .-count_equal_bytes
