#include "crc32.h"
#include "ctest.h"

/* Standard test vectors for CRC-32 (IEEE 802.3 / zlib). */

TEST(empty_input_is_zero) {
    /* crc32("", 0) == 0x00000000 */
    ASSERT_EQ_UINT(0x00000000U, crc32(NULL, 0));
}

TEST(canonical_check_value) {
    /* The official CRC-32 check value: crc32("123456789", 9) == 0xCBF43926 */
    const unsigned char *msg = (const unsigned char *)"123456789";
    ASSERT_EQ_UINT(0xCBF43926U, crc32(msg, 9));
}

TEST(single_zero_byte) {
    /* crc32("\x00", 1) == 0xD202EF8D */
    const unsigned char data[] = {0x00};
    ASSERT_EQ_UINT(0xD202EF8DU, crc32(data, 1));
}

TEST(single_byte_0xFF) {
    /* crc32("\xff", 1) == 0xFF000000 */
    const unsigned char data[] = {0xFF};
    ASSERT_EQ_UINT(0xFF000000U, crc32(data, 1));
}

TEST(hello_world) {
    /* crc32("hello world", 11) == 0x0D4A1185 */
    const unsigned char *msg = (const unsigned char *)"hello world";
    ASSERT_EQ_UINT(0x0D4A1185U, crc32(msg, 11));
}

int main(void) {
    RUN(empty_input_is_zero);
    RUN(canonical_check_value);
    RUN(single_zero_byte);
    RUN(single_byte_0xFF);
    RUN(hello_world);
    return ctest_report();
}
