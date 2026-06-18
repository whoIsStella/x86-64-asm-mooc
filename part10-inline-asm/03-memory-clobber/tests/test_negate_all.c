#include "negate_all.h"
#include "ctest.h"

TEST(negate_positive_values) {
    long arr[] = {1, 2, 3};
    negate_all(arr, 3);
    ASSERT_EQ_INT(-1, arr[0]);
    ASSERT_EQ_INT(-2, arr[1]);
    ASSERT_EQ_INT(-3, arr[2]);
}

TEST(negate_negative_values) {
    long arr[] = {-4, -5, -6};
    negate_all(arr, 3);
    ASSERT_EQ_INT(4, arr[0]);
    ASSERT_EQ_INT(5, arr[1]);
    ASSERT_EQ_INT(6, arr[2]);
}

TEST(negate_zero_stays_zero) {
    long arr[] = {0};
    negate_all(arr, 1);
    ASSERT_EQ_INT(0, arr[0]);
}

TEST(negate_mixed_signs) {
    long arr[] = {10, -20, 30, -40};
    negate_all(arr, 4);
    ASSERT_EQ_INT(-10, arr[0]);
    ASSERT_EQ_INT(20,  arr[1]);
    ASSERT_EQ_INT(-30, arr[2]);
    ASSERT_EQ_INT(40,  arr[3]);
}

TEST(negate_empty_array) {
    /* n=0: nothing to do, should not crash */
    long arr[] = {99};
    negate_all(arr, 0);
    ASSERT_EQ_INT(99, arr[0]);   /* untouched */
}

int main(void) {
    RUN(negate_positive_values);
    RUN(negate_negative_values);
    RUN(negate_zero_stays_zero);
    RUN(negate_mixed_signs);
    RUN(negate_empty_array);
    return ctest_report();
}
