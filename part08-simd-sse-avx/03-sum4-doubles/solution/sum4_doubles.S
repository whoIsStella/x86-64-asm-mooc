.intel_syntax noprefix
.text
.globl sum4_doubles
.type sum4_doubles, @function
/* double sum4_doubles(const double *p)
 * SysV AMD64: p=rdi, return double in xmm0
 *
 * Strategy:
 *   movupd xmm0, [rdi]    — load p[0] and p[1] into xmm0 (packed double, unaligned)
 *   movupd xmm1, [rdi+16] — load p[2] and p[3] into xmm1
 *   addpd  xmm0, xmm1     — xmm0 = { p[0]+p[2], p[1]+p[3] }
 *   movhlps xmm1, xmm0    — copy high 64 bits of xmm0 into low 64 bits of xmm1
 *   addsd  xmm0, xmm1     — xmm0[0] += xmm1[0]  =>  xmm0[0] = p[0]+p[1]+p[2]+p[3]
 *
 * The scalar result sits in the low 64 bits of xmm0 — exactly where SysV expects
 * a double return value.
 */
sum4_doubles:
    movupd  xmm0, [rdi]         /* xmm0 = { p[0], p[1] } */
    movupd  xmm1, [rdi + 16]    /* xmm1 = { p[2], p[3] } */
    addpd   xmm0, xmm1          /* xmm0 = { p[0]+p[2], p[1]+p[3] } */
    movhlps xmm1, xmm0          /* xmm1[low] = xmm0[high] = p[1]+p[3] */
    addsd   xmm0, xmm1          /* xmm0[low] = (p[0]+p[2]) + (p[1]+p[3]) */
    ret
.size sum4_doubles, .-sum4_doubles
