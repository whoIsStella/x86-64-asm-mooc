#include "sum_to_n.h"
#include "ctest.h"

TEST(sum_to_0) {
    ASSERT_EQ_INT(0, sum_to_n(0));
}

TEST(sum_to_1) {
    ASSERT_EQ_INT(1, sum_to_n(1));
}

TEST(sum_to_5) {
    ASSERT_EQ_INT(15, sum_to_n(5));
}

TEST(sum_to_10) {
    ASSERT_EQ_INT(55, sum_to_n(10));
}

TEST(sum_to_100) {
    ASSERT_EQ_INT(5050, sum_to_n(100));
}

int main(void) {
    RUN(sum_to_0);
    RUN(sum_to_1);
    RUN(sum_to_5);
    RUN(sum_to_10);
    RUN(sum_to_100);
    return ctest_report();
}
