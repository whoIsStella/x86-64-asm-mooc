#include "my_memcpy.h"
#include "ctest.h"
#include <string.h>

TEST(copy_zero_bytes) {
    char dst[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    char src[4] = {0x11, 0x22, 0x33, 0x44};
    my_memcpy(dst, src, 0);
    /* dst must be unchanged */
    ASSERT_EQ_INT((unsigned char)0xAA, (unsigned char)dst[0]);
    ASSERT_EQ_INT((unsigned char)0xBB, (unsigned char)dst[1]);
}

TEST(copy_one_byte) {
    char dst[4] = {0x00, 0x00, 0x00, 0x00};
    char src[4] = {0x42, 0x00, 0x00, 0x00};
    my_memcpy(dst, src, 1);
    ASSERT_EQ_INT(0x42, (unsigned char)dst[0]);
}

TEST(copy_several_bytes) {
    char dst[8] = {0};
    const char src[] = "abcdef";
    my_memcpy(dst, src, 6);
    ASSERT_EQ_INT(0, memcmp(dst, src, 6));
}

TEST(copy_does_not_overrun) {
    char dst[8];
    const char src[] = "hi";
    memset(dst, 0xFF, sizeof(dst));
    my_memcpy(dst, src, 3); /* "hi\0" */
    ASSERT_EQ_INT('h',  (unsigned char)dst[0]);
    ASSERT_EQ_INT('i',  (unsigned char)dst[1]);
    ASSERT_EQ_INT('\0', (unsigned char)dst[2]);
    /* byte past the copy must be untouched */
    ASSERT_EQ_INT(0xFF, (unsigned char)dst[3]);
}

int main(void) {
    RUN(copy_zero_bytes);
    RUN(copy_one_byte);
    RUN(copy_several_bytes);
    RUN(copy_does_not_overrun);
    return ctest_report();
}
