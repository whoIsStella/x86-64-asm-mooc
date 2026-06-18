#include "bit_ops.h"
#include "ctest.h"

TEST(zero_input) {
    /* popcnt(0) = 0, rol(0, anything) = 0; result = 0 */
    ASSERT_EQ_UINT(0UL, popcount_and_rotate(0UL, 0));
    ASSERT_EQ_UINT(0UL, popcount_and_rotate(0UL, 5));
    ASSERT_EQ_UINT(0UL, popcount_and_rotate(0UL, 63));
}

TEST(all_ones_byte_rotate_8) {
    /* x = 0xFF:
     *   popcnt(0xFF) = 8
     *   rol(0xFF, 8) = 0xFF00
     *   result = 8 + 0xFF00 = 0xFF08
     */
    ASSERT_EQ_UINT(0xFF08UL, popcount_and_rotate(0xFFUL, 8));
}

TEST(single_bit_rotate_63) {
    /* x = 1:
     *   popcnt(1) = 1
     *   rol(1, 63) = 0x8000000000000000  (bit wraps to MSB)
     *   result = 1 + 0x8000000000000000 = 0x8000000000000001
     */
    ASSERT_EQ_UINT(0x8000000000000001UL, popcount_and_rotate(1UL, 63));
}

TEST(rotate_by_zero) {
    /* rol(x, 0) = x; result = popcnt(x) + x */
    /* x = 0xFF: popcnt = 8, rol = 0xFF, result = 8 + 255 = 263 */
    ASSERT_EQ_UINT(263UL, popcount_and_rotate(0xFFUL, 0));
}

TEST(all_bits_set) {
    /* x = 0xFFFFFFFFFFFFFFFF:
     *   popcnt = 64
     *   rol(0xFFFF..., any) = 0xFFFF... (all ones, rotation is identity)
     *   result = 64 + 0xFFFFFFFFFFFFFFFF
     *          = 0xFFFFFFFFFFFFFFFF + 64  (wraps around mod 2^64)
     *          = 63  (0xFFFF...FF = -1 unsigned; -1 + 64 + 1 = 64, but mod 2^64: 63)
     * Careful: 0xFFFFFFFFFFFFFFFF + 64 = 0x10000000000000003F -> low 64 bits = 0x3F = 63
     */
    ASSERT_EQ_UINT(63UL, popcount_and_rotate(0xFFFFFFFFFFFFFFFFUL, 7));
}

int main(void) {
    RUN(zero_input);
    RUN(all_ones_byte_rotate_8);
    RUN(single_bit_rotate_63);
    RUN(rotate_by_zero);
    RUN(all_bits_set);
    return ctest_report();
}
