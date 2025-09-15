#ifndef UNITY_H
#define UNITY_H

void UNITY_BEGIN(void);
void UNITY_END(void);
void RUN_TEST(void (*test)(void));
void TEST_ASSERT_EQUAL_INT(int expected, int actual);

#endif // UNITY_H