#ifndef RIP_TABLE_LOOKUP_H
#define RIP_TABLE_LOOKUP_H

/* Return the length of the weekday name for day 0..6 (Mon=0, Sun=6).
 * Returns -1 for any out-of-range value. */
int weekday_len(int day);

#endif
