#include "return_42.h"
#include "ctest.h"

TEST(returns_forty_two) {
    ASSERT_EQ_INT(42, return_42());
}

TEST(is_stable_across_calls) {
    ASSERT_EQ_INT(42, return_42());
    ASSERT_EQ_INT(42, return_42());
}

int main(void) {
    RUN(returns_forty_two);
    RUN(is_stable_across_calls);
    return ctest_report();
}
