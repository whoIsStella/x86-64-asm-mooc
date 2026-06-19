#include "sub_negate.h"
#include "ctest.h"

TEST(basic_subtraction) {
    ASSERT_EQ_INT(7, sub_negate(10, 3));
}

TEST(result_is_negative) {
    ASSERT_EQ_INT(-5, sub_negate(0, 5));
}

TEST(both_negative_same_value) {
    ASSERT_EQ_INT(0, sub_negate(-3, -3));
}

TEST(larger_minus_smaller) {
    ASSERT_EQ_INT(-100, sub_negate(100, 200));
}

int main(void) {
    RUN(basic_subtraction);
    RUN(result_is_negative);
    RUN(both_negative_same_value);
    RUN(larger_minus_smaller);
    return ctest_report();
}
