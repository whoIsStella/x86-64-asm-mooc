#ifndef TIMES3_VIA_LEA_H
#define TIMES3_VIA_LEA_H

/*
 * times3_via_lea — return x * 3.
 *
 * Must be implemented using leaq in GCC extended inline assembly.
 * No multiplication instruction is permitted.
 */
long times3_via_lea(long x);

#endif /* TIMES3_VIA_LEA_H */
