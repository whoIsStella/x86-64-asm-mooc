#ifndef SUM4_DOUBLES_H
#define SUM4_DOUBLES_H

/* Sum four consecutive doubles stored at p[0..3].
 * Returns p[0] + p[1] + p[2] + p[3].
 * The return value is a double, which the SysV AMD64 ABI passes back in xmm0.
 */
double sum4_doubles(const double *p);

#endif
