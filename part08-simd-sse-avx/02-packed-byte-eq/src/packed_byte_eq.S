.intel_syntax noprefix
.text
.globl count_equal_bytes
.type count_equal_bytes, @function
/* int count_equal_bytes(const unsigned char *a, const unsigned char *b)
 * SysV AMD64: a=rdi, b=rsi, return in rax (int)
 * TODO: load 16 bytes from a and b with movdqu, compare with pcmpeqb,
 *       extract the high bit of each byte with pmovmskb, then
 *       count the set bits (popcount) to get the number of equal positions.
 */
count_equal_bytes:
    xor eax, eax    /* stub: always return 0 */
    ret
.size count_equal_bytes, .-count_equal_bytes
