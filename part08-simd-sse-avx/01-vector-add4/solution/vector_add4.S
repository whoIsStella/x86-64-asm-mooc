.intel_syntax noprefix
.text
.globl add4_floats
.type add4_floats, @function
/* void add4_floats(float *dst, const float *a, const float *b)
 * SysV AMD64: dst=rdi, a=rsi, b=rdx
 *
 * movups: move unaligned packed single-precision (128-bit / 4 floats).
 * addps:  add packed single-precision — all 4 lanes simultaneously.
 */
add4_floats:
    movups xmm0, [rsi]      /* xmm0 = a[0..3] */
    movups xmm1, [rdx]      /* xmm1 = b[0..3] */
    addps  xmm0, xmm1       /* xmm0 = a[0..3] + b[0..3] */
    movups [rdi], xmm0      /* dst[0..3] = xmm0 */
    ret
.size add4_floats, .-add4_floats
