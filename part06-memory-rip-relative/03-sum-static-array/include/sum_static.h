#ifndef SUM_STATIC_H
#define SUM_STATIC_H

/* Return the sum of a fixed array defined in the assembly source's own
 * .data/.rodata section, loaded via RIP-relative addressing. */
long sum_static(void);

#endif
