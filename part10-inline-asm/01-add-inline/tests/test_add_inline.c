#include "add_inline.h"
#include "ctest.h"

TEST(add_one_plus_two) {
    ASSERT_EQ_INT(3, add_inline(1, 2));
}

TEST(add_negative_and_positive) {
    ASSERT_EQ_INT(-2, add_inline(-5, 3));
}

TEST(add_zeros) {
    ASSERT_EQ_INT(0, add_inline(0, 0));
}

TEST(add_large_positives) {
    ASSERT_EQ_INT(300, add_inline(100, 200));
}

TEST(add_two_negatives) {
    ASSERT_EQ_INT(-30, add_inline(-10, -20));
}

int main(void) {
    RUN(add_one_plus_two);
    RUN(add_negative_and_positive);
    RUN(add_zeros);
    RUN(add_large_positives);
    RUN(add_two_negatives);
    return ctest_report();
}
