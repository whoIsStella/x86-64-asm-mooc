#include "echo.h"
#include "ctest.h"

TEST(returns_small_positive) {
    ASSERT_EQ_INT(7, echo(7));
}

TEST(returns_zero) {
    ASSERT_EQ_INT(0, echo(0));
}

TEST(returns_negative) {
    ASSERT_EQ_INT(-123, echo(-123));
}

TEST(returns_large_value) {
    ASSERT_EQ_INT(9000000000L, echo(9000000000L));
}

int main(void) {
    RUN(returns_small_positive);
    RUN(returns_zero);
    RUN(returns_negative);
    RUN(returns_large_value);
    return ctest_report();
}
