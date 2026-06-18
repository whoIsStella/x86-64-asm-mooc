#include "factorial_recursive.h"
#include "ctest.h"

TEST(factorial_zero) {
    ASSERT_EQ_INT(1, factorial(0));
}

TEST(factorial_one) {
    ASSERT_EQ_INT(1, factorial(1));
}

TEST(factorial_five) {
    ASSERT_EQ_INT(120, factorial(5));
}

TEST(factorial_ten) {
    ASSERT_EQ_INT(3628800, factorial(10));
}

int main(void) {
    RUN(factorial_zero);
    RUN(factorial_one);
    RUN(factorial_five);
    RUN(factorial_ten);
    return ctest_report();
}
