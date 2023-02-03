#include <gtest/gtest.h>

#include <NumericCell.hpp>

#include <memory>

using csv::NumericCell;

TEST(NumericCell_Test, ValueCTor) {
    constexpr int initVal = 32;
    const NumericCell nCell(initVal);
    EXPECT_EQ(nCell.GetVal(), initVal);
}

TEST(NumericCell_Test, CopyCTor) {
    constexpr int initVal = -900;
    const NumericCell nCell1(initVal);
    const NumericCell nCell2 = nCell1;
    EXPECT_TRUE(nCell2 == nCell1);
}

TEST(NumericCell_Test, CheckIsEqualFalse) {
    constexpr int initVal1 = -2900;
    constexpr int initVal2 = 12900;
    const NumericCell nC1(initVal1);
    const NumericCell nC2(initVal2);
    EXPECT_FALSE(nC1.IsEqual(nC2));
}

TEST(NumericCell_Test, CheckIsEqualTrue) {
    constexpr int initVal = 58934;
    const NumericCell nC1(initVal);
    const NumericCell nC2(initVal);
    EXPECT_TRUE(nC1 == nC2);
}

TEST(NumericCell_Test, CheckIsEqualBaseFalse) {
    constexpr int initVal1 = 473598;
    constexpr int initVal2 = 58934;
    std::unique_ptr<csv::Cell> nBC1 = std::make_unique<NumericCell>(initVal1);
    std::unique_ptr<csv::Cell> nBC2 = std::make_unique<NumericCell>(initVal2);
    EXPECT_TRUE(*nBC1 != *nBC2);
}

TEST(NumericCell_Test, CheckIsEqualBaseTrue) {
    constexpr int initVal1 = 435647398;
    constexpr int initVal2 = 435647398;
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
    constexpr int initVal1 = 12900;
    constexpr int initVal2 = 6900;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 += nC2;
    EXPECT_EQ(nC1, initVal1 + initVal2);
}

TEST(NumericCell_Test, CheckPlusEqNCint) {
    constexpr int initVal1 = 12900;
    constexpr int initVal2 = 6900;
    NumericCell nC1(initVal1);
    nC1 += initVal2;
    EXPECT_EQ(nC1, initVal1 + initVal2);
}

TEST(NumericCell_Test, CheckSubEqNCNC) {
    constexpr int initVal1 = 12900;
    constexpr int initVal2 = 6900;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 -= nC2;
    EXPECT_EQ(nC1, initVal1 - initVal2);
}

TEST(NumericCell_Test, CheckMultEqNCNC) {
    constexpr int initVal1 = 150;
    constexpr int initVal2 = 20;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 *= nC2;
    EXPECT_EQ(nC1, initVal1 * initVal2);
}

TEST(NumericCell_Test, CheckDivEqNCNC) {
    constexpr int initVal1 = 146;
    constexpr int initVal2 = 20;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 /= nC2;
    EXPECT_EQ(nC1, initVal1 / initVal2);
}

TEST(NumericCell_Test, CheckPlusNCNC) {
    constexpr int initVal1 = 12900;
    constexpr int initVal2 = 6900;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 + nC2;
    EXPECT_EQ(nC1, initVal1 + initVal2);
}

TEST(NumericCell_Test, CheckSubNCNC) {
    constexpr int initVal1 = 12900;
    constexpr int initVal2 = 6900;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 - nC2;
    EXPECT_EQ(nC1, initVal1 - initVal2);
}

TEST(NumericCell_Test, CheckMultNCNC) {
    constexpr int initVal1 = 150;
    constexpr int initVal2 = 20;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 * nC2;
    EXPECT_EQ(nC1, initVal1 * initVal2);
}

TEST(NumericCell_Test, CheckDivNCNC) {
    constexpr int initVal1 = 146;
    constexpr int initVal2 = 20;
    NumericCell nC1(initVal1);
    NumericCell nC2(initVal2);
    nC1 = nC1 / nC2;
    EXPECT_EQ(nC1, initVal1 / initVal2);
}
