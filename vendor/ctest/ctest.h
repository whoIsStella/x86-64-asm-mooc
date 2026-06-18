/*
 * ctest.h — a tiny, self-contained, single-header C unit-test framework.
 *
 * Vendored into c-mooc so the repository builds and runs with ZERO external
 * dependencies and NO network access. (We chose this over Unity/CMocka so the
 * harness is auditable in ~120 lines; the trade-off is fewer features.)
 *
 * Usage:
 *
 *     #include "ctest.h"
 *
 *     TEST(addition_works) {
 *         ASSERT_EQ_INT(2 + 2, 4);
 *     }
 *
 *     int main(void) {
 *         RUN(addition_works);
 *         return ctest_report();   // nonzero exit if any test failed
 *     }
 *
 * Macros:
 *   TEST(name)             - declare a test function `void name(void)`.
 *   RUN(name)              - run a declared test, tracking pass/fail.
 *   ASSERT_TRUE(cond)      - fail the current test if cond is false.
 *   ASSERT_FALSE(cond)     - fail the current test if cond is true.
 *   ASSERT_EQ_INT(a, b)    - fail if (long long)a != (long long)b.
 *   ASSERT_EQ_UINT(a, b)   - fail if (unsigned long long)a != b.
 *   ASSERT_EQ_STR(a, b)    - fail if strcmp(a, b) != 0.
 *   ASSERT_EQ_DBL(a, b, e) - fail if fabs(a - b) > e.
 *   ASSERT_NULL(p)         - fail if p != NULL.
 *   ASSERT_NOT_NULL(p)     - fail if p == NULL.
 *
 * An assertion failure marks the test failed and RETURNS from the test
 * function (it does not abort the process), so remaining tests still run.
 */
#ifndef CTEST_H
#define CTEST_H

#include <math.h>
#include <stdio.h>
#include <string.h>

/* Global counters. `static` so each test executable owns its own copy. */
static int ctest_tests_run = 0;
static int ctest_tests_failed = 0;
static int ctest_current_failed = 0; /* set by an assertion in the running test */

#define CTEST_FAIL_(fmt, ...)                                                   \
    do {                                                                        \
        ctest_current_failed = 1;                                              \
        fprintf(stderr, "    FAIL %s:%d: " fmt "\n", __FILE__, __LINE__,        \
                __VA_ARGS__);                                                   \
        return;                                                                 \
    } while (0)

#define TEST(name) static void name(void)

#define RUN(name)                                                               \
    do {                                                                        \
        ctest_current_failed = 0;                                              \
        ctest_tests_run++;                                                     \
        printf("RUN  %s\n", #name);                                            \
        name();                                                                \
        if (ctest_current_failed) {                                            \
            ctest_tests_failed++;                                              \
            printf("FAIL %s\n", #name);                                        \
        } else {                                                               \
            printf("OK   %s\n", #name);                                        \
        }                                                                       \
    } while (0)

#define ASSERT_TRUE(cond)                                                       \
    do {                                                                        \
        if (!(cond))                                                            \
            CTEST_FAIL_("ASSERT_TRUE(%s)", #cond);                             \
    } while (0)

#define ASSERT_FALSE(cond)                                                      \
    do {                                                                        \
        if (cond)                                                               \
            CTEST_FAIL_("ASSERT_FALSE(%s)", #cond);                            \
    } while (0)

#define ASSERT_EQ_INT(a, b)                                                     \
    do {                                                                        \
        long long ctest_a_ = (long long)(a);                                    \
        long long ctest_b_ = (long long)(b);                                    \
        if (ctest_a_ != ctest_b_)                                               \
            CTEST_FAIL_("ASSERT_EQ_INT(%s, %s): %lld != %lld", #a, #b,          \
                        ctest_a_, ctest_b_);                                    \
    } while (0)

#define ASSERT_EQ_UINT(a, b)                                                    \
    do {                                                                        \
        unsigned long long ctest_a_ = (unsigned long long)(a);                  \
        unsigned long long ctest_b_ = (unsigned long long)(b);                  \
        if (ctest_a_ != ctest_b_)                                               \
            CTEST_FAIL_("ASSERT_EQ_UINT(%s, %s): %llu != %llu", #a, #b,         \
                        ctest_a_, ctest_b_);                                    \
    } while (0)

#define ASSERT_EQ_STR(a, b)                                                     \
    do {                                                                        \
        const char *ctest_a_ = (a);                                             \
        const char *ctest_b_ = (b);                                             \
        if (strcmp(ctest_a_, ctest_b_) != 0)                                    \
            CTEST_FAIL_("ASSERT_EQ_STR(%s, %s): \"%s\" != \"%s\"", #a, #b,      \
                        ctest_a_, ctest_b_);                                    \
    } while (0)

#define ASSERT_EQ_DBL(a, b, eps)                                                \
    do {                                                                        \
        double ctest_a_ = (a);                                                  \
        double ctest_b_ = (b);                                                  \
        if (fabs(ctest_a_ - ctest_b_) > (eps))                                  \
            CTEST_FAIL_("ASSERT_EQ_DBL(%s, %s): %g != %g (eps %g)", #a, #b,     \
                        ctest_a_, ctest_b_, (double)(eps));                     \
    } while (0)

#define ASSERT_NULL(p)                                                          \
    do {                                                                        \
        if ((p) != NULL)                                                        \
            CTEST_FAIL_("ASSERT_NULL(%s)", #p);                                \
    } while (0)

#define ASSERT_NOT_NULL(p)                                                      \
    do {                                                                        \
        if ((p) == NULL)                                                        \
            CTEST_FAIL_("ASSERT_NOT_NULL(%s)", #p);                            \
    } while (0)

/* Print a summary and return a process exit code (0 = all passed). */
static int ctest_report(void) {
    printf("\n--------------------------------------------------\n");
    printf("%d test(s) run, %d passed, %d failed\n", ctest_tests_run,
           ctest_tests_run - ctest_tests_failed, ctest_tests_failed);
    return ctest_tests_failed == 0 ? 0 : 1;
}

#endif /* CTEST_H */

