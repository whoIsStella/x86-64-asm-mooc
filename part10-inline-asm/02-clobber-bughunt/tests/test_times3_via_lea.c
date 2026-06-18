#include "times3_via_lea.h"
#include "ctest.h"

TEST(times3_one) {
    ASSERT_EQ_INT(3, times3_via_lea(1));
}

TEST(times3_five) {
    ASSERT_EQ_INT(15, times3_via_lea(5));
}

TEST(times3_zero) {
    ASSERT_EQ_INT(0, times3_via_lea(0));
}

TEST(times3_negative) {
    ASSERT_EQ_INT(-12, times3_via_lea(-4));
}

TEST(times3_large) {
    ASSERT_EQ_INT(300, times3_via_lea(100));
}

int main(void) {
    RUN(times3_one);
    RUN(times3_five);
    RUN(times3_zero);
    RUN(times3_negative);
    RUN(times3_large);
    return ctest_report();
}
