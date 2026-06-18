#include "checked_add.h"
#include "ctest.h"
#include <limits.h>

TEST(normal_add_no_overflow) {
    long result = 0;
    int overflow = checked_add(10, 20, &result);
    ASSERT_EQ_INT(30, result);
    ASSERT_EQ_INT(0, overflow);
}

TEST(zero_add_no_overflow) {
    long result = 0;
    int overflow = checked_add(0, 0, &result);
    ASSERT_EQ_INT(0, result);
    ASSERT_EQ_INT(0, overflow);
}

TEST(negative_add_no_overflow) {
    long result = 0;
    int overflow = checked_add(-5, -3, &result);
    ASSERT_EQ_INT(-8, result);
    ASSERT_EQ_INT(0, overflow);
}

TEST(long_max_plus_one_overflows) {
    long result = 0;
    int overflow = checked_add(LONG_MAX, 1, &result);
    ASSERT_EQ_INT(1, overflow);
}

TEST(long_min_minus_one_overflows) {
    long result = 0;
    int overflow = checked_add(LONG_MIN, -1, &result);
    ASSERT_EQ_INT(1, overflow);
}

TEST(mixed_sign_no_overflow) {
    long result = 0;
    int overflow = checked_add(LONG_MAX, -1, &result);
    ASSERT_EQ_INT(LONG_MAX - 1, result);
    ASSERT_EQ_INT(0, overflow);
}

int main(void) {
    RUN(normal_add_no_overflow);
    RUN(zero_add_no_overflow);
    RUN(negative_add_no_overflow);
    RUN(long_max_plus_one_overflows);
    RUN(long_min_minus_one_overflows);
    RUN(mixed_sign_no_overflow);
    return ctest_report();
}
