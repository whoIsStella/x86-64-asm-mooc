#include "packed_byte_eq.h"
#include "ctest.h"

TEST(all_equal) {
    unsigned char a[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    unsigned char b[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    ASSERT_EQ_INT(16, count_equal_bytes(a, b));
}

TEST(none_equal) {
    unsigned char a[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned char b[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    ASSERT_EQ_INT(0, count_equal_bytes(a, b));
}

TEST(some_equal) {
    /* positions 0,2,4,6,8,10,12,14 are equal — 8 matches */
    unsigned char a[16] = {5,  0, 5,  0, 5,  0, 5,  0, 5,  0, 5,  0, 5,  0, 5,  0};
    unsigned char b[16] = {5, 99, 5, 99, 5, 99, 5, 99, 5, 99, 5, 99, 5, 99, 5, 99};
    ASSERT_EQ_INT(8, count_equal_bytes(a, b));
}

TEST(one_equal) {
    unsigned char a[16] = {42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned char b[16] = {42,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    ASSERT_EQ_INT(1, count_equal_bytes(a, b));
}

int main(void) {
    RUN(all_equal);
    RUN(none_equal);
    RUN(some_equal);
    RUN(one_equal);
    return ctest_report();
}
