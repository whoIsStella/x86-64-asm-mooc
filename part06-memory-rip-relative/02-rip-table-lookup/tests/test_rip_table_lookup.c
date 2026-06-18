#include "rip_table_lookup.h"
#include "ctest.h"

/* Weekday names (Mon=0..Sun=6):
 * Monday(6), Tuesday(7), Wednesday(9), Thursday(8),
 * Friday(6), Saturday(8), Sunday(6) */

TEST(monday_len) {
    ASSERT_EQ_INT(6, weekday_len(0));
}

TEST(tuesday_len) {
    ASSERT_EQ_INT(7, weekday_len(1));
}

TEST(wednesday_len) {
    ASSERT_EQ_INT(9, weekday_len(2));
}

TEST(thursday_len) {
    ASSERT_EQ_INT(8, weekday_len(3));
}

TEST(friday_len) {
    ASSERT_EQ_INT(6, weekday_len(4));
}

TEST(saturday_len) {
    ASSERT_EQ_INT(8, weekday_len(5));
}

TEST(sunday_len) {
    ASSERT_EQ_INT(6, weekday_len(6));
}

TEST(negative_out_of_range) {
    ASSERT_EQ_INT(-1, weekday_len(-1));
}

TEST(too_large_out_of_range) {
    ASSERT_EQ_INT(-1, weekday_len(7));
}

int main(void) {
    RUN(monday_len);
    RUN(tuesday_len);
    RUN(wednesday_len);
    RUN(thursday_len);
    RUN(friday_len);
    RUN(saturday_len);
    RUN(sunday_len);
    RUN(negative_out_of_range);
    RUN(too_large_out_of_range);
    return ctest_report();
}
