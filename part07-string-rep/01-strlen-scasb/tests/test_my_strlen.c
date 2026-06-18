#include "my_strlen.h"
#include "ctest.h"

TEST(empty_string) {
    ASSERT_EQ_UINT(0UL, my_strlen(""));
}

TEST(single_char) {
    ASSERT_EQ_UINT(1UL, my_strlen("a"));
}

TEST(hello) {
    ASSERT_EQ_UINT(5UL, my_strlen("hello"));
}

TEST(longer_string) {
    ASSERT_EQ_UINT(13UL, my_strlen("hello, world!"));
}

int main(void) {
    RUN(empty_string);
    RUN(single_char);
    RUN(hello);
    RUN(longer_string);
    return ctest_report();
}
