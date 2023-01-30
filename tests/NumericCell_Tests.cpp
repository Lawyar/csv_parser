#include <gtest/gtest.h>

#include <NumericCell.hpp>

#include <memory>

using csv::NumericCell;

TEST(NumericCell_Test, ValueCTor) {
    constexpr double initVal = 32.;
    const NumericCell nCell(initVal);
    EXPECT_DOUBLE_EQ(nCell.GetVal(), initVal);
}

TEST(NumericCell_Test, CopyCTor) {
    constexpr double initVal = -900.;
    const NumericCell nCell1(initVal);
    const NumericCell nCell2 = nCell1;
    EXPECT_TRUE(nCell2 == nCell1);
}

TEST(NumericCell_Test, CheckIsEqualFalse) {
    constexpr double initVal1 = -2900.;
    constexpr double initVal2 = 12900.;
    const NumericCell nC1(initVal1);
    const NumericCell nC2(initVal2);
    EXPECT_FALSE(nC1.IsEqual(nC2));
}

TEST(NumericCell_Test, CheckIsEqualTrue) {
    constexpr double initVal = 58934.;
    const NumericCell nC1(initVal);
    const NumericCell nC2(initVal);
    EXPECT_TRUE(nC1 == nC2);
}

TEST(NumericCell_Test, CheckIsEqualBaseFalse) {
    constexpr double initVal1 = 473598;
    constexpr double initVal2 = 58934.;
    std::unique_ptr<csv::Cell> nBC1 = std::make_unique<NumericCell>(initVal1);
    std::unique_ptr<csv::Cell> nBC2 = std::make_unique<NumericCell>(initVal2);
    EXPECT_TRUE(*nBC1 != *nBC2);
}

TEST(NumericCell_Test, CheckIsEqualBaseTrue) {
    constexpr double initVal1 = 4356473598;
    constexpr double initVal2 = 4356473598;
    std::unique_ptr<csv::Cell> nBC1 = std::make_unique<NumericCell>(initVal1);
    std::unique_ptr<csv::Cell> nBC2 = std::make_unique<NumericCell>(initVal2);
    EXPECT_TRUE(nBC1->IsEqual(*nBC2));
}

TEST(NumericCell_Test, CheckClone) {
    std::unique_ptr<csv::Cell> cell = std::make_unique<NumericCell>(1024);
    auto cloneCell = cell->Clone();
    EXPECT_TRUE(*cloneCell == *cell);
}

TEST(NumericCell_Test, CheckPlusEqNCNC) {
    constexpr double initVal1 = 12900.;
    constexpr double initVal2 = 6900.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 += nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 + initVal2);
}

TEST(NumericCell_Test, CheckPlusEqNCDouble) {
    constexpr double initVal1 = 12900.;
    constexpr double initVal2 = 6900.;
    NumericCell nC1(initVal1);
    nC1 += initVal2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 + initVal2);
}

TEST(NumericCell_Test, CheckSubEqNCNC) {
    constexpr double initVal1 = 12900.;
    constexpr double initVal2 = 6900.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 -= nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 - initVal2);
}

TEST(NumericCell_Test, CheckMultEqNCNC) {
    constexpr double initVal1 = 150.;
    constexpr double initVal2 = 20.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 *= nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 * initVal2);
}

TEST(NumericCell_Test, CheckDivEqNCNC) {
    constexpr double initVal1 = 146.;
    constexpr double initVal2 = 20.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 /= nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 / initVal2);
}

TEST(NumericCell_Test, CheckPlusNCNC) {
    constexpr double initVal1 = 12900.;
    constexpr double initVal2 = 6900.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 + nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 + initVal2);
}

TEST(NumericCell_Test, CheckSubNCNC) {
    constexpr double initVal1 = 12900.;
    constexpr double initVal2 = 6900.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 - nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 - initVal2);
}

TEST(NumericCell_Test, CheckMultNCNC) {
    constexpr double initVal1 = 150.;
    constexpr double initVal2 = 20.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 * nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 * initVal2);
}

TEST(NumericCell_Test, CheckDivNCNC) {
    constexpr double initVal1 = 146.;
    constexpr double initVal2 = 20.;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 / nC2;
    EXPECT_DOUBLE_EQ(nC1, initVal1 / initVal2);
}
