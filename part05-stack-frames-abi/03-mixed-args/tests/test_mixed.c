#include "mixed.h"
#include "ctest.h"

TEST(mixed_basic) {
    long val = 7;
    ASSERT_EQ_INT(17, mixed(4, &val, 6));
}

TEST(mixed_zero_pointer) {
    long val = 0;
    ASSERT_EQ_INT(10, mixed(5, &val, 5));
}

TEST(mixed_negative_args) {
    long val = -3;
    ASSERT_EQ_INT(-4, mixed(-1, &val, 0));
}

TEST(mixed_pointer_value_dominates) {
    long val = 100;
    ASSERT_EQ_INT(101, mixed(0, &val, 1));
}

int main(void) {
    RUN(mixed_basic);
    RUN(mixed_zero_pointer);
    RUN(mixed_negative_args);
    RUN(mixed_pointer_value_dominates);
    return ctest_report();
}
