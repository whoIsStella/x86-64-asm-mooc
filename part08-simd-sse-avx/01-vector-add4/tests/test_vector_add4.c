#include "vector_add4.h"
#include "ctest.h"

/* Use exact integer-valued floats so sums are bit-exact — no -lm needed. */

TEST(adds_positive_floats) {
    float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float b[4] = {5.0f, 6.0f, 7.0f, 8.0f};
    float dst[4] = {0};
    add4_floats(dst, a, b);
    ASSERT_EQ_DBL(dst[0],  6.0, 0.0);
    ASSERT_EQ_DBL(dst[1],  8.0, 0.0);
    ASSERT_EQ_DBL(dst[2], 10.0, 0.0);
    ASSERT_EQ_DBL(dst[3], 12.0, 0.0);
}

TEST(adds_zeros) {
    float a[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float b[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float dst[4] = {1.0f, 1.0f, 1.0f, 1.0f};  /* should be overwritten */
    add4_floats(dst, a, b);
    ASSERT_EQ_DBL(dst[0], 0.0, 0.0);
    ASSERT_EQ_DBL(dst[1], 0.0, 0.0);
    ASSERT_EQ_DBL(dst[2], 0.0, 0.0);
    ASSERT_EQ_DBL(dst[3], 0.0, 0.0);
}

TEST(adds_mixed_signs) {
    float a[4] = { 10.0f, -3.0f,  7.0f, 0.0f};
    float b[4] = {-10.0f,  3.0f, -7.0f, 0.0f};
    float dst[4] = {0};
    add4_floats(dst, a, b);
    ASSERT_EQ_DBL(dst[0], 0.0, 0.0);
    ASSERT_EQ_DBL(dst[1], 0.0, 0.0);
    ASSERT_EQ_DBL(dst[2], 0.0, 0.0);
    ASSERT_EQ_DBL(dst[3], 0.0, 0.0);
}

TEST(dst_can_alias_a) {
    float a[4] = {2.0f, 4.0f, 6.0f, 8.0f};
    float b[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    add4_floats(a, a, b);   /* dst == a */
    ASSERT_EQ_DBL(a[0], 3.0, 0.0);
    ASSERT_EQ_DBL(a[1], 5.0, 0.0);
    ASSERT_EQ_DBL(a[2], 7.0, 0.0);
    ASSERT_EQ_DBL(a[3], 9.0, 0.0);
}

int main(void) {
    RUN(adds_positive_floats);
    RUN(adds_zeros);
    RUN(adds_mixed_signs);
    RUN(dst_can_alias_a);
    return ctest_report();
}
