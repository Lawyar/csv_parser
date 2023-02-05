#include <gtest/gtest.h>

#include <BinOp.hpp>

using csv::BinOp;

using namespace std::string_literals;

TEST(BinOp_Test, TestCTorIntPos) {
    EXPECT_NO_THROW(BinOp bOp(1, 2, csv::OpType::ADD));
}

TEST(BinOp_Test, TestCTorIntNeg) {
    EXPECT_NO_THROW(BinOp bOp(-1, -2, csv::OpType::DIV));
}

TEST(BinOp_Test, TestInvStrCTor1) {
    EXPECT_THROW(BinOp("abc"s), csv::BinOpConstructionErr);
}

TEST(BinOp_Test, TestInvStrCTor2) {
    EXPECT_EQ(BinOp("a + c"s).ConstructionStatus(), csv::ConstructionStatus::UNCONSTRUCTED);
}

TEST(BinOp_Test, TestInvStrCTor3) {
    EXPECT_EQ(BinOp("2 + c"s).ConstructionStatus(), csv::ConstructionStatus::LHS_CONSTR);
}

TEST(BinOp_Test, TestInvStrCTor4) {
    EXPECT_EQ(BinOp("b+6"s).ConstructionStatus(), csv::ConstructionStatus::RHS_CONSTR);
}

TEST(BinOp_Test, TestInvStrCTor5) {
    EXPECT_THROW(BinOp("112"s), csv::BinOpConstructionErr);
}

TEST(BinOp_Test, TestStrCtor) {
    EXPECT_NO_THROW(BinOp("2+8"s));
}

TEST(BinOp_Test, TestStrCtorSpacing) {
    EXPECT_NO_THROW(BinOp("8 / 2"s));
}

TEST(BinOp_Test, TestPosNegSub) {
    const int v1 = 127, v2 = -234;
    const csv::OpType op = csv::OpType::SUB;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 - v2);
}

TEST(BinOp_Test, TestPosNegAdd) {
    const int v1 = 127, v2 = -234;
    const csv::OpType op = csv::OpType::ADD;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 + v2);
}

TEST(BinOp_Test, Test2) {
    const int v1 = 127, v2 = -234;
    const csv::OpType op = csv::OpType::ADD;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 + v2);
}

TEST(BinOp_Test, TestPosNegMul) {
    const int v1 = 127, v2 = -234;
    const csv::OpType op = csv::OpType::MUL;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 * v2);
}

TEST(BinOp_Test, TestPosNegDiv) {
    const int v1 = 127, v2 = -234;
    const csv::OpType op = csv::OpType::DIV;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 / v2);
}

TEST(BinOp_Test, TestPosPosAdd) {
    const int v1 = 127, v2 = 234;
    const csv::OpType op = csv::OpType::ADD;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 + v2);
}

TEST(BinOp_Test, TestNegPosAdd) {
    const int v1 = -127, v2 = 234;
    const csv::OpType op = csv::OpType::ADD;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 + v2);
}

TEST(BinOp_Test, TestNegNegAdd) {
    const int v1 = -127, v2 = -234;
    const csv::OpType op = csv::OpType::ADD;
    BinOp bop(v1, v2, op);
    EXPECT_EQ(bop.GetExpressionResult(), v1 + v2);
}

TEST(BinOp_Test, TestAddOnStrCTor) {
    int v1 = 8628, v2 = 322;
    std::string expr("-8628+-322"s);
    BinOp bop(expr);
    EXPECT_EQ(bop.GetExpressionResult(), -v1 + -v2);
}

TEST(BinOp_Test, TestSubOnStrCTor) {
    int v1 = 8628, v2 = 322;
    std::string expr("-8628--322"s);
    BinOp bop(expr);
    EXPECT_EQ(bop.GetExpressionResult(), -v1 - -v2);
}

TEST(BinOp_Test, TestMulOnStrCTor) {
    int v1 = 8628, v2 = 322;
    std::string expr("-8628*-322"s);
    BinOp bop(expr);
    EXPECT_EQ(bop.GetExpressionResult(), -v1 * -v2);
}

TEST(BinOp_Test, TestDivOnStrCTor) {
    int v1 = 8628, v2 = 322;
    std::string expr("-8628/-322"s);
    BinOp bop(expr);
    EXPECT_EQ(bop.GetExpressionResult(), -v1 / -v2);
}

TEST(BinOp_Test, CheckCellStr) {
    std::string expr("-8628/-322"s);
    const BinOp bop(expr);
    EXPECT_EQ(bop.ToString(), expr);
}

TEST(BinOp_Test, CheckCellStrSpaced) {
    std::string expr("   8628 + 322   "s);
    const BinOp bop(expr);
    std::erase_if(expr, isspace);
    EXPECT_EQ(bop.ToString(), expr);
}

TEST(BinOp_Test, CheckCellStrAfterRhsReset) {
    std::string lhs = "8628"s, sign = "+"s, rhs = "322"s;
    std::string expr = lhs + sign + rhs;
    BinOp bop(expr);
    int newRhs = 900;
    bop.SetRhs(newRhs);
    std::string newExp = lhs + sign + std::to_string(newRhs);
    EXPECT_EQ(bop.ToString(), newExp);
}

TEST(BinOp_Test, CheckCellStrAfterLhsReset) {
    std::string lhs = "8628"s, sign = "+"s, rhs = "322"s;
    std::string expr = lhs + sign + rhs;
    BinOp bop(expr);
    int newLhs = 900;
    bop.SetLhs(newLhs);
    std::string newExp = std::to_string(newLhs) + sign + rhs;
    EXPECT_EQ(bop.ToString(), newExp);
}

TEST(BinOp_Test, CheckCellStrAfterSignReset) {
    std::string lhs = "8628"s, sign = "+"s, rhs = "322"s;
    std::string expr = lhs + sign + rhs;
    BinOp bop(expr);
    csv::OpType newOp = csv::OpType::SUB;
    bop.SetOp(newOp);
    std::string newExp = lhs + '-' + rhs;
    EXPECT_EQ(bop.ToString(), newExp);
}
