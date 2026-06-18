#include "byte_scan.h"
#include "ctest.h"

TEST(hit_at_start) {
    unsigned char buf[] = {0xAA, 0x01, 0x02, 0x03};
    ASSERT_EQ_INT(0, find_byte(buf, 4, 0xAA));
}

TEST(hit_in_middle) {
    unsigned char buf[] = {0x01, 0x02, 0x42, 0x04};
    ASSERT_EQ_INT(2, find_byte(buf, 4, 0x42));
}

TEST(hit_at_end) {
    unsigned char buf[] = {0x01, 0x02, 0x03, 0xFF};
    ASSERT_EQ_INT(3, find_byte(buf, 4, 0xFF));
}

TEST(miss_returns_minus_one) {
    unsigned char buf[] = {0x01, 0x02, 0x03, 0x04};
    ASSERT_EQ_INT(-1, find_byte(buf, 4, 0x99));
}

TEST(empty_buffer_miss) {
    unsigned char buf[] = {0x42};
    ASSERT_EQ_INT(-1, find_byte(buf, 0, 0x42));
}

int main(void) {
    RUN(hit_at_start);
    RUN(hit_in_middle);
    RUN(hit_at_end);
    RUN(miss_returns_minus_one);
    RUN(empty_buffer_miss);
    return ctest_report();
}
