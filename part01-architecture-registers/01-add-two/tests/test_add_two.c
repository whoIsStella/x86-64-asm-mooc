#include "add_two.h"
#include "ctest.h"

TEST(adds_positive_values) {
    ASSERT_EQ_INT(5, add_two(2, 3));
}

TEST(adds_negative_values) {
    ASSERT_EQ_INT(-9, add_two(-4, -5));
}

TEST(adds_mixed_sign_values) {
    ASSERT_EQ_INT(4, add_two(10, -6));
}

TEST(handles_zero) {
    ASSERT_EQ_INT(42, add_two(42, 0));
}

int main(void) {
    RUN(adds_positive_values);
    RUN(adds_negative_values);
    RUN(adds_mixed_sign_values);
    RUN(handles_zero);
    return ctest_report();
}
