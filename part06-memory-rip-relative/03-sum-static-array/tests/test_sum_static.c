#include "sum_static.h"
#include "ctest.h"

/* The assembly source defines the array {10, 20, 30, 40, 50}.
 * Sum = 150. */
TEST(known_constant_sum) {
    ASSERT_EQ_INT(150, sum_static());
}

TEST(result_is_positive) {
    ASSERT_TRUE(sum_static() > 0);
}

int main(void) {
    RUN(known_constant_sum);
    RUN(result_is_positive);
    return ctest_report();
}
