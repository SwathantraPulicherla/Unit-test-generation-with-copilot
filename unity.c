#include <stdio.h>
#include "unity.h"

static int tests_run = 0;
static int tests_failed = 0;

void UNITY_BEGIN(void) {
    tests_run = 0;
    tests_failed = 0;
    printf("==== Unity Test Framework ====\n");
}

void UNITY_END(void) {
    printf("==== Tests run: %d, Failures: %d ====\n", tests_run, tests_failed);
}

void RUN_TEST(void (*test)(void)) {
    tests_run++;
    test();
}

void TEST_ASSERT_EQUAL_INT(int expected, int actual) {
    if (expected != actual) {
        printf("Test failed: expected %d but got %d\n", expected, actual);
        tests_failed++;
    }
}