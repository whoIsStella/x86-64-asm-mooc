#include "signed_unsigned_cmp.h"
#include "ctest.h"
#include <limits.h>

TEST(equal_values) {
    ASSERT_EQ_INT(0, cmp3(0, 0));
    ASSERT_EQ_INT(0, cmp3(42, 42));
    ASSERT_EQ_INT(0, cmp3(-7, -7));
}

TEST(positive_less_than) {
    ASSERT_EQ_INT(-1, cmp3(1, 2));
    ASSERT_EQ_INT(-1, cmp3(0, 1));
}

TEST(positive_greater_than) {
    ASSERT_EQ_INT(1, cmp3(2, 1));
    ASSERT_EQ_INT(1, cmp3(1, 0));
}

TEST(negative_less_than_positive) {
    /* Signed: -1 < 1. Unsigned: -1 would be ULONG_MAX > 1. */
    ASSERT_EQ_INT(-1, cmp3(-1, 1));
    ASSERT_EQ_INT(-1, cmp3(-100, 0));
}

TEST(positive_greater_than_negative) {
    ASSERT_EQ_INT(1, cmp3(1, -1));
    ASSERT_EQ_INT(1, cmp3(0, -100));
}

TEST(large_negative_less_than_small_positive) {
    /* LONG_MIN is the most negative signed value; unsigned it is ULONG_MAX/2+1. */
    ASSERT_EQ_INT(-1, cmp3(LONG_MIN, 0));
    ASSERT_EQ_INT(-1, cmp3(LONG_MIN, LONG_MAX));
    ASSERT_EQ_INT(1, cmp3(LONG_MAX, LONG_MIN));
}

int main(void) {
    RUN(equal_values);
    RUN(positive_less_than);
    RUN(positive_greater_than);
    RUN(negative_less_than_positive);
    RUN(positive_greater_than_negative);
    RUN(large_negative_less_than_small_positive);
    return ctest_report();
}
