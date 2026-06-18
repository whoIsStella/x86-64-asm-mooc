#include "simd_find_byte.h"
#include "ctest.h"

/* Tests for simd_find_byte — covers all structural cases. */

TEST(match_at_index_zero) {
    /* First byte is the target. */
    const unsigned char s[] = "Axyz0123456789abcdef";
    ASSERT_EQ_INT(0, simd_find_byte(s, 20, 'A'));
}

TEST(match_within_first_16) {
    /* Match at index 7 — within the first vector chunk. */
    const unsigned char s[] = "0123456X89abcdef01234567";
    ASSERT_EQ_INT(7, simd_find_byte(s, 24, 'X'));
}

TEST(match_beyond_16_bytes) {
    /* Match at index 30 — forces at least two full 16-byte iterations.
     * Buffer is 48 bytes: 30 'a's, then 'Z', then 17 'b's. */
    unsigned char buf[48];
    for (int i = 0; i < 48; i++) buf[i] = 'a';
    buf[30] = 'Z';
    ASSERT_EQ_INT(30, simd_find_byte(buf, 48, 'Z'));
}

TEST(match_in_scalar_tail) {
    /* Buffer length 19 (not a multiple of 16).
     * Match is at index 17 — in the scalar tail after one 16-byte chunk. */
    unsigned char buf[19];
    for (int i = 0; i < 19; i++) buf[i] = 0x55;
    buf[17] = 0xAA;
    ASSERT_EQ_INT(17, simd_find_byte(buf, 19, 0xAA));
}

TEST(no_match_returns_minus_one) {
    /* Target byte not present at all. */
    const unsigned char s[] = "abcdefghijklmnopqrstuvwxyz012345";
    ASSERT_EQ_INT(-1, simd_find_byte(s, 32, 0xFF));
}

TEST(empty_buffer_returns_minus_one) {
    /* n == 0: nothing to search. */
    const unsigned char s[] = "X";
    ASSERT_EQ_INT(-1, simd_find_byte(s, 0, 'X'));
}

int main(void) {
    RUN(match_at_index_zero);
    RUN(match_within_first_16);
    RUN(match_beyond_16_bytes);
    RUN(match_in_scalar_tail);
    RUN(no_match_returns_minus_one);
    RUN(empty_buffer_returns_minus_one);
    return ctest_report();
}
