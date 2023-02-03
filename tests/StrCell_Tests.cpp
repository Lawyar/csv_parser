#include <gtest/gtest.h>

#include <StrCell.hpp>

#include <memory>

using csv::StrCell;
using namespace std::literals::string_literals;

TEST(StrCell_Test, ValueCTor) {
    const std::string initVal = "32"s;
    const StrCell sCell(initVal);
    EXPECT_EQ(sCell.GetVal(), initVal);
}

TEST(StrCell_Test, CopyCTor) {
    const std::string initVal = "-900"s;
    const StrCell sCell1(initVal);
    const StrCell sCell2 = sCell1;
    EXPECT_TRUE(sCell2 == sCell1);
}

TEST(StrCell_Test, CheckIsEqualFalse) {
    const std::string initVal1 = "-2900"s;
    const std::string initVal2 = "12900"s;
    const StrCell nC1(initVal1);
    const StrCell nC2(initVal2);
    EXPECT_FALSE(nC1.IsEqual(nC2));
}

TEST(StrCell_Test, CheckIsEqualTrue) {
    const std::string initVal = "58934"s;
    const StrCell nC1(initVal);
    const StrCell nC2(initVal);
    EXPECT_TRUE(nC1 == nC2);
}

TEST(StrCell_Test, CheckIsEqualBaseFalse) {
    const std::string initVal1 = "473598"s;
    const std::string initVal2 = "58934"s;
    std::unique_ptr<csv::Cell> nBC1 = std::make_unique<StrCell>(initVal1);
    std::unique_ptr<csv::Cell> nBC2 = std::make_unique<StrCell>(initVal2);
    EXPECT_TRUE(*nBC1 != *nBC2);
}

TEST(StrCell_Test, CheckIsEqualBaseTrue) {
    const std::string initVal1 = "4356473598"s;
    const std::string initVal2 = "4356473598"s;
    std::unique_ptr<csv::Cell> nBC1 = std::make_unique<StrCell>(initVal1);
    std::unique_ptr<csv::Cell> nBC2 = std::make_unique<StrCell>(initVal2);
    EXPECT_TRUE(nBC1->IsEqual(*nBC2));
}

TEST(StrCell_Test, CheckClone) {
    std::unique_ptr<csv::Cell> cell = std::make_unique<StrCell>("1024"s);
    auto cloneCell = cell->Clone();
    EXPECT_TRUE(*cloneCell == *cell);
}
