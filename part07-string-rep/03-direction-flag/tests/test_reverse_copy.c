#include "reverse_copy.h"
#include "ctest.h"
#include <string.h>

TEST(copy_single_byte) {
    unsigned char dst[1] = {0};
    const unsigned char src[1] = {0x42};
    reverse_copy(dst, src, 1);
    ASSERT_EQ_INT(0x42, dst[0]);
}

TEST(copy_matches_src) {
    unsigned char dst[5] = {0};
    const unsigned char src[] = {1, 2, 3, 4, 5};
    reverse_copy(dst, src, 5);
    ASSERT_EQ_INT(0, memcmp(dst, src, 5));
}

TEST(copy_zero_bytes) {
    unsigned char dst[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    const unsigned char src[4] = {0x11, 0x22, 0x33, 0x44};
    reverse_copy(dst, src, 0);
    /* dst unchanged */
    ASSERT_EQ_INT(0xAA, dst[0]);
}

/* Verify that the direction flag is clear after the call so that
   subsequent C library calls (e.g. memcmp) work correctly. */
TEST(direction_flag_clear_after_call) {
    unsigned char dst[4] = {0};
    const unsigned char src[4] = {10, 20, 30, 40};
    reverse_copy(dst, src, 4);
    /* Use memcmp — it relies on DF==0.  If DF were still set, memcmp
       would malfunction and this comparison would fail. */
    ASSERT_EQ_INT(0, memcmp(dst, src, 4));
}

int main(void) {
    RUN(copy_single_byte);
    RUN(copy_matches_src);
    RUN(copy_zero_bytes);
    RUN(direction_flag_clear_after_call);
    return ctest_report();
}
