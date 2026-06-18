#include "branchless_max.h"
#include "ctest.h"

TEST(positive_a_greater) {
    ASSERT_EQ_INT(10, imax(10, 3));
}

TEST(positive_b_greater) {
    ASSERT_EQ_INT(7, imax(2, 7));
}

TEST(negative_a_greater) {
    ASSERT_EQ_INT(-1, imax(-1, -5));
}

TEST(negative_b_greater) {
    ASSERT_EQ_INT(-2, imax(-9, -2));
}

TEST(equal_values) {
    ASSERT_EQ_INT(4, imax(4, 4));
}

TEST(mixed_signs) {
    ASSERT_EQ_INT(5, imax(-3, 5));
}

int main(void) {
    RUN(positive_a_greater);
    RUN(positive_b_greater);
    RUN(negative_a_greater);
    RUN(negative_b_greater);
    RUN(equal_values);
    RUN(mixed_signs);
    return ctest_report();
}
