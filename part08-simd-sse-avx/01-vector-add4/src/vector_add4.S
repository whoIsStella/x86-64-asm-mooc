.intel_syntax noprefix
.text
.globl add4_floats
.type add4_floats, @function
/* void add4_floats(float *dst, const float *a, const float *b)
 * SysV AMD64: dst=rdi, a=rsi, b=rdx
 * TODO: load 4 packed floats from a and b into xmm registers,
 *       add them with addps, and store the result into dst.
 *       Use movups (unaligned) for both loads and the store.
 */
add4_floats:
    xor eax, eax        /* stub: do nothing, leave dst untouched */
    ret
.size add4_floats, .-add4_floats
