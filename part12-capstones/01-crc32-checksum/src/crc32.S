/* CRC-32 (IEEE 802.3) stub — returns 0 (wrong) so tests fail RED.
 *
 * SysV AMD64 ABI:
 *   rdi = const unsigned char *data
 *   rsi = unsigned long len
 *   return unsigned int in eax (rax zero-extended)
 *
 * TODO: implement the reflected CRC-32 bit-by-bit algorithm:
 *   1. crc = 0xFFFFFFFF
 *   2. for each byte b in data[0..len-1]:
 *        crc ^= b
 *        for bit in 0..7:
 *            if (crc & 1): crc = (crc >> 1) ^ 0xEDB88320
 *            else:         crc >>= 1
 *   3. return crc ^ 0xFFFFFFFF
 */

.intel_syntax noprefix
.text
.globl crc32
.type crc32, @function
crc32:
    /* TODO: implement CRC-32 (IEEE 802.3, poly 0xEDB88320, reflected).
     * SysV AMD64: data in rdi, len in rsi, return unsigned int in eax. */
    xor eax, eax
    ret
.size crc32, .-crc32
