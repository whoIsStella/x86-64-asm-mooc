/* CRC-32 (IEEE 802.3) — reflected bitwise implementation.
 *
 * Polynomial: 0xEDB88320 (reflected form of 0x04C11DB7)
 * Init:        0xFFFFFFFF
 * Final XOR:   0xFFFFFFFF
 *
 * Standard check value: crc32("123456789", 9) == 0xCBF43926
 *
 * SysV AMD64 ABI:
 *   rdi = const unsigned char *data
 *   rsi = unsigned long len
 *   return unsigned int in eax (upper 32 bits of rax zeroed by movl)
 */

.intel_syntax noprefix
.text
.globl crc32
.type crc32, @function

/* unsigned int crc32(const unsigned char *data, unsigned long len) */
crc32:
    /* ecx = crc accumulator, initialized to 0xFFFFFFFF */
    mov     ecx, 0xFFFFFFFF

    test    rsi, rsi
    jz      .Ldone              /* len == 0: return ~0xFFFFFFFF == 0 */

    /* r8 = one-past-end pointer */
    lea     r8, [rdi + rsi]

.Lbyte_loop:
    /* XOR next byte into low byte of crc */
    movzx   eax, byte ptr [rdi]
    xor     ecx, eax
    inc     rdi

    /* 8 bit-iterations.
     * Trick: the lsb of crc selects whether to XOR in the polynomial.
     *   mov edx, ecx   ; copy
     *   and edx, 1     ; isolate lsb
     *   neg edx        ; 0 -> 0, 1 -> 0xFFFFFFFF (two's complement)
     *   shr ecx, 1     ; shift
     *   and edx, poly  ; mask poly only if lsb was 1
     *   xor ecx, edx   ; conditionally apply poly
     */
    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    mov     edx, ecx
    and     edx, 1
    neg     edx
    shr     ecx, 1
    and     edx, 0xEDB88320
    xor     ecx, edx

    cmp     rdi, r8
    jb      .Lbyte_loop

.Ldone:
    /* Final XOR: flip all bits, then zero-extend into rax */
    not     ecx
    mov     eax, ecx
    ret
.size crc32, .-crc32
