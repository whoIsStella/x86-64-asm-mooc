.intel_syntax noprefix
.text
.globl sum4_doubles
.type sum4_doubles, @function
/* double sum4_doubles(const double *p)
 * SysV AMD64: p=rdi, return double in xmm0
 * TODO: load p[0..1] into xmm0 and p[2..3] into xmm1 using movupd,
 *       add the two pairs with addpd (packed double),
 *       then add the two lanes of xmm0 together with addsd to get the scalar sum.
 *       Return the result in xmm0 (scalar slot).
 */
sum4_doubles:
    xorpd xmm0, xmm0    /* stub: always return 0.0 */
    ret
.size sum4_doubles, .-sum4_doubles
