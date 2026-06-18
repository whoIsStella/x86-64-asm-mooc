#include <stdio.h>
#include "../../vendor/ctest/ctest.h"

/* Declaration of the function under test (broken or fixed version). */
long broken_abi(long a, long b);

TEST(returns_a_times_2_plus_b_simple) {
    /* 3*2 + 4 = 10 */
    ASSERT_EQ_INT(10, broken_abi(3, 4));
}

TEST(returns_a_times_2_plus_b_zero_b) {
    /* 5*2 + 0 = 10 */
    ASSERT_EQ_INT(10, broken_abi(5, 0));
}

TEST(returns_a_times_2_plus_b_zero_a) {
    /* 0*2 + 7 = 7 */
    ASSERT_EQ_INT(7, broken_abi(0, 7));
}

TEST(returns_a_times_2_plus_b_negative) {
    /* (-2)*2 + 3 = -1 */
    ASSERT_EQ_INT(-1, broken_abi(-2, 3));
}

int main(void) {
    RUN(returns_a_times_2_plus_b_simple);
    RUN(returns_a_times_2_plus_b_zero_b);
    RUN(returns_a_times_2_plus_b_zero_a);
    RUN(returns_a_times_2_plus_b_negative);
    return ctest_report();
}
