#if 0

#include <gtest/gtest.h>

#include <NumericBinOp.hpp>

using csv::NumericBinOp;
using csv::NumericCell;
using csv::NumericOp_T;

TEST(NumericNumericOp_Test, TestCTor) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::ADD;
    const NumericBinOp binOp(lhs, rhs, opT);

    EXPECT_TRUE(binOp.GetLhs() == lhs);
    EXPECT_TRUE(binOp.GetRhs() == rhs);
    EXPECT_TRUE(binOp.GetOpType() == opT);
}

TEST(NumericNumericOp_Test, TestEq) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::ADD, invOpT = NumericOp_T::DIV;
    const NumericBinOp binOp(lhs, rhs, opT);

    EXPECT_TRUE(binOp.GetLhs() != (lhs + lhs));
    EXPECT_TRUE(binOp.GetRhs() != (rhs * rhs));
    EXPECT_TRUE(binOp.GetOpType() != invOpT);
}

TEST(NumericNumericOp_Test, TestAdd) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::ADD;
    const NumericBinOp binOp(lhs, rhs, opT);

    const NumericCell expectedVal = lhsVal + rhsVal;
    const auto evalVal = binOp.Evaluate();
    EXPECT_TRUE(expectedVal == *evalVal);
}

TEST(NumericNumericOp_Test, TestSub) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::SUB;
    const NumericBinOp binOp(lhs, rhs, opT);

    const NumericCell expectedVal = lhsVal - rhsVal;
    const auto evalVal = binOp.Evaluate();
    EXPECT_TRUE(expectedVal == *evalVal);
}

TEST(NumericNumericOp_Test, TestMul) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::MUL;
    const NumericBinOp binOp(lhs, rhs, opT);

    const NumericCell expectedVal = lhsVal * rhsVal;
    const auto evalVal = binOp.Evaluate();
    EXPECT_TRUE(expectedVal == *evalVal);
}

TEST(NumericNumericOp_Test, TestDiv) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::DIV;
    const NumericBinOp binOp(lhs, rhs, opT);

    const NumericCell expectedVal = lhsVal / rhsVal;
    const auto evalVal = binOp.Evaluate();
    EXPECT_TRUE(expectedVal == *evalVal);
}

TEST(NumericNumericOp_Test, TestClone) {
    constexpr int lhsVal = 32, rhsVal = 7;
    const NumericCell lhs(lhsVal), rhs(rhsVal);
    constexpr NumericOp_T opT = NumericOp_T::DIV;
    const NumericBinOp binOp(lhs, rhs, opT);
    auto binOpClone = binOp.Clone();

    EXPECT_TRUE(*binOpClone == binOp);
}

#endif
