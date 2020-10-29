#include "gtest/gtest.h"
#include "../evaluate_prefix.h"
#include "../evaluate_postfix.h"

TEST(evaluate_prefix, 1) {
    Expression exp("+ 2 3");
    ASSERT_EQ(exp.evaluate(), 5);
}
TEST(evaluate_prefix, 2) {
    Expression exp("- * + 3 2 6 1");
    ASSERT_EQ(exp.evaluate(), 29);
}

TEST(evaluate_prefix, 3) {
    Expression exp("+*~1 3 8");
    ASSERT_EQ(exp.evaluate(), 5);
}

TEST(evaluate_prefix, 4) {
    Expression exp("-+3^2 5 1");
    ASSERT_EQ(exp.evaluate(), 34);
}

TEST(evaluate_prefix, 5) {
    Expression exp("+~3*^3-3 1 2");
    ASSERT_EQ(exp.evaluate(), 15);
}
TEST(evaluate_prefix, 6) {
    Expression exp("~ * ^ 2 3 3 ");
    ASSERT_EQ(exp.evaluate(), -24);
}

TEST(evaluate_postfix, 1) {
    IPExpression exp("3 2 4 * 1 - +");
    ASSERT_EQ(exp.evaluate(), 10);
}

TEST(evaluate_postfix, 2) {
    IPExpression exp("3 2 ^ 4 7 * - 9 3 1 - * +");
    ASSERT_EQ(exp.evaluate(), -1);
}

TEST(evaluate_postfix, 3) {
    IPExpression exp("2 3 4 5 - * + 2 3 ^ -");
    ASSERT_EQ(exp.evaluate(), -9);
}

TEST(evaluate_postfix, 4) {
    IPExpression exp(" 3 12 11 - ^ ~ 4 1 + 7 * - 9 3 2 1 - ^ * +  ");
    ASSERT_EQ(exp.evaluate(), -11);
}