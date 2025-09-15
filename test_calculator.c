#include "unity.h"
#include "calculator.h"

void setUp(void) {}
void tearDown(void) {}

void test_add_pos(void) {
    TEST_ASSERT_EQUAL_INT(5, add(2, 3));
}

void test_add_neg(void) {
    TEST_ASSERT_EQUAL_INT(1, add(3, -2));
}

void test_add_both_neg(void) {
    TEST_ASSERT_EQUAL_INT(-5, add(-2, -3));
}

void test_add_zero(void) {
    TEST_ASSERT_EQUAL_INT(7, add(7, 0));
    TEST_ASSERT_EQUAL_INT(-4, add(0, -4));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_pos);
    RUN_TEST(test_add_neg);
    RUN_TEST(test_add_both_neg);
    RUN_TEST(test_add_zero);
    UNITY_END();
    return 0;
}