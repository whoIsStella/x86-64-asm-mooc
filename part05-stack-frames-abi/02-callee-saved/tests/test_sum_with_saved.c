#include "sum_with_saved.h"
#include "ctest.h"

TEST(sum_all_positive) {
    ASSERT_EQ_INT(10, sum_with_saved(1, 2, 3, 4));
}

TEST(sum_with_zeros) {
    ASSERT_EQ_INT(0, sum_with_saved(0, 0, 0, 0));
}

TEST(sum_with_negatives) {
    ASSERT_EQ_INT(0, sum_with_saved(-5, -3, 4, 4));
}

TEST(sum_large_values) {
    ASSERT_EQ_INT(100, sum_with_saved(10, 20, 30, 40));
}

int main(void) {
    RUN(sum_all_positive);
    RUN(sum_with_zeros);
    RUN(sum_with_negatives);
    RUN(sum_large_values);
    return ctest_report();
}
