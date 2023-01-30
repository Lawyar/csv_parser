#include <gtest/gtest.h>

#include <StrBinOp.hpp>

using namespace std::literals::string_literals;

using csv::StrBinOp;
using csv::StrCell;
using csv::StrOp_T;

TEST(StrBinOp_Test, TestCTor) {
    const std::string lhsVal = "32."s, rhsVal = "7."s;
    const StrCell lhs(lhsVal), rhs(rhsVal);
    constexpr StrOp_T opT = StrOp_T::ADD;
    const StrBinOp binOp(lhs, rhs, opT);

    EXPECT_TRUE(binOp.GetLhs() == lhs);
    EXPECT_TRUE(binOp.GetRhs() == rhs);
    EXPECT_TRUE(binOp.GetOpType() == opT);
}

TEST(StrBinOp_Test, TestEq) {
    const std::string lhsVal = "32."s, rhsVal = "7."s;
    const StrCell lhs(lhsVal), rhs(rhsVal);
    constexpr StrOp_T opT = StrOp_T::ADD;
    const StrBinOp binOp(lhs, rhs, opT);

    EXPECT_TRUE(binOp.GetLhs() != (lhs + lhs));
    EXPECT_TRUE(binOp.GetRhs() != (rhs + rhs));
}

TEST(StrBinOp_Test, TestAdd) {
    const std::string lhsVal = "32."s, rhsVal = "7."s;
    const StrCell lhs(lhsVal), rhs(rhsVal);
    constexpr StrOp_T opT = StrOp_T::ADD;
    const StrBinOp binOp(lhs, rhs, opT);

    const StrCell expectedVal = lhsVal + rhsVal;
    const auto evalVal = binOp.Evaluate();
    EXPECT_TRUE(expectedVal == *evalVal);
}

TEST(StrBinOp_Test, TestClone) {
    const std::string lhsVal = "32."s, rhsVal = "7."s;
    const StrCell lhs(lhsVal), rhs(rhsVal);
    constexpr StrOp_T opT = StrOp_T::ADD;
    const StrBinOp binOp(lhs, rhs, opT);
    auto binOpClone = binOp.Clone();

    EXPECT_TRUE(*binOpClone == binOp);
}
