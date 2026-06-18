#include "sum4_doubles.h"
#include "ctest.h"

/* Use exact integer-valued doubles so results are bit-exact. */

TEST(sum_of_one_to_four) {
    double p[4] = {1.0, 2.0, 3.0, 4.0};
    ASSERT_EQ_DBL(sum4_doubles(p), 10.0, 0.0);
}

TEST(sum_of_zeros) {
    double p[4] = {0.0, 0.0, 0.0, 0.0};
    ASSERT_EQ_DBL(sum4_doubles(p), 0.0, 0.0);
}

TEST(sum_with_negatives) {
    double p[4] = {10.0, -3.0, -3.0, -4.0};
    ASSERT_EQ_DBL(sum4_doubles(p), 0.0, 0.0);
}

TEST(sum_large_values) {
    double p[4] = {100.0, 200.0, 300.0, 400.0};
    ASSERT_EQ_DBL(sum4_doubles(p), 1000.0, 0.0);
}

int main(void) {
    RUN(sum_of_one_to_four);
    RUN(sum_of_zeros);
    RUN(sum_with_negatives);
    RUN(sum_large_values);
    return ctest_report();
}
