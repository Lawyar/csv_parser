#include <gtest/gtest.h>

#include <Cell.hpp>

using namespace std::string_literals;

using csv::Cell;

TEST(Cell_Test, TestCopyCTor) {
    const std::string str = "flashbang"s;
    const Cell c1{ str };
    EXPECT_NO_THROW(Cell{ c1 });
}

TEST(Cell_Test, TestMoveCTor) {
    const std::string str = "Maria de La Vid"s;
    Cell c1{ str };
    EXPECT_NO_THROW(Cell{ std::move(c1) });
}

TEST(Cell_Test, TestCTorStr) {
    const std::string str = "stack overflow"s;
    EXPECT_NO_THROW(Cell{ str });
}

TEST(Cell_Test, TestMoveCTorStr) {
    std::string str = "design the nature"s;
    EXPECT_NO_THROW(Cell{ std::move(str) });
}

TEST(Cell_Test, TestDefaultCTor) {
    EXPECT_NO_THROW(Cell cell);
}

TEST(Cell_Test, TestIsEqualTrue) {
    const std::string str = " "s;
    const Cell c1(str);
    const Cell c2;
    EXPECT_EQ(c1, c2);
}

TEST(Cell_Test, TestIsEqualFalse) {
    const std::string str = "       "s;
    const Cell c1(str);
    const Cell c2;
    EXPECT_NE(c1, c2);
}

TEST(Cell_Test, TestToString) {
    const std::string str = "Ivan Genadyevich"s;
    const Cell c1(str);
    EXPECT_EQ(c1.ToString(), str);
}

TEST(Cell_Test, TestStrDataOnChange) {
    const std::string str = "Braziliy Maikovizcky"s;
    const std::string newStr = "cplusplus"s;
    Cell c1(str);
    c1.StrData() = newStr;
    EXPECT_EQ(c1.ToString(), newStr);
}

TEST(Cell_Test, TestStrCast) {
    const std::string str = "vitamin"s;
    const Cell c1(str);
    const std::string castedCell = c1;
    EXPECT_EQ(castedCell, str);
}

TEST(Cell_Test, TestCopyAssign) {
    const std::string str = "flashbang"s;
    const Cell c1{ str };
    const Cell c2 = c1;
    EXPECT_EQ(c2.ToString(), c1.ToString());
}

TEST(Cell_Test, TestMoveAssign) {
    const std::string str = "flashbang"s;
    Cell c1{ str };
    const Cell c2 = std::move(c1);
    EXPECT_EQ(str, c2.ToString());
}

TEST(Cell_Test, TestCopyAssignStr) {
    const std::string str = "flashbang"s;
    const Cell c1 = str;
    EXPECT_EQ(str, c1.ToString());
}

TEST(Cell_Test, TestMoveAssignStr) {
    std::string str = "flashbang"s;
    const auto strCopy = str;
    const Cell c1 = std::move(str);
    EXPECT_EQ(strCopy, c1.ToString());
}

TEST(Cell_Test, TestClone) {
    const std::string str = "vitamin"s;
    const Cell c1(str);
    const auto c2 = c1.Clone();
    EXPECT_EQ(*c2, c1);
}
