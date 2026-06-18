#include "lea_scale_add.h"
#include "ctest.h"

TEST(computes_positive_values) {
    ASSERT_EQ_INT(42, lea_scale_add(10, 2));
}

TEST(computes_zero_index) {
    ASSERT_EQ_INT(23, lea_scale_add(7, 0));
}

TEST(computes_negative_base) {
    ASSERT_EQ_INT(20, lea_scale_add(-20, 3));
}

TEST(computes_negative_index) {
    ASSERT_EQ_INT(8, lea_scale_add(16, -3));
}

int main(void) {
    RUN(computes_positive_values);
    RUN(computes_zero_index);
    RUN(computes_negative_base);
    RUN(computes_negative_index);
    return ctest_report();
}
