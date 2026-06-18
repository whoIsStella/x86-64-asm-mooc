#ifndef NEGATE_ALL_H
#define NEGATE_ALL_H

/*
 * negate_all — negate every element of arr in-place.
 *
 * After the call, arr[i] == -(original arr[i]) for all i in [0, n).
 * Implement using the negq instruction via GCC extended inline assembly.
 */
void negate_all(long *arr, long n);

#endif /* NEGATE_ALL_H */
