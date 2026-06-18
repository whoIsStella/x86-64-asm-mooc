#include "classify_sign.h"
#include "ctest.h"

TEST(negative_large) {
    ASSERT_EQ_INT(-1, classify(-100));
}

TEST(negative_one) {
    ASSERT_EQ_INT(-1, classify(-1));
}

TEST(zero) {
    ASSERT_EQ_INT(0, classify(0));
}

TEST(positive_one) {
    ASSERT_EQ_INT(1, classify(1));
}

TEST(positive_large) {
    ASSERT_EQ_INT(1, classify(42));
}

int main(void) {
    RUN(negative_large);
    RUN(negative_one);
    RUN(zero);
    RUN(positive_one);
    RUN(positive_large);
    return ctest_report();
}
