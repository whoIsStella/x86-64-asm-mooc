#include "array_sum_loop.h"
#include "ctest.h"

TEST(empty_array) {
    long arr[] = {1, 2, 3};
    ASSERT_EQ_INT(0, array_sum(arr, 0));
}

TEST(single_element) {
    long arr[] = {42};
    ASSERT_EQ_INT(42, array_sum(arr, 1));
}

TEST(several_positives) {
    long arr[] = {1, 2, 3, 4, 5};
    ASSERT_EQ_INT(15, array_sum(arr, 5));
}

TEST(mixed_signs) {
    long arr[] = {10, -3, 7, -4};
    ASSERT_EQ_INT(10, array_sum(arr, 4));
}

TEST(all_negative) {
    long arr[] = {-1, -2, -3};
    ASSERT_EQ_INT(-6, array_sum(arr, 3));
}

int main(void) {
    RUN(empty_array);
    RUN(single_element);
    RUN(several_positives);
    RUN(mixed_signs);
    RUN(all_negative);
    return ctest_report();
}
