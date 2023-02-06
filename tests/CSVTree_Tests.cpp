#include <gtest/gtest.h>

#include <CSVTree.hpp>
#include <CSVRow.hpp>

using namespace std::string_literals;

using csv::CSVTree;
using csv::CSVRow;

TEST(CSVTree_Test, CheckPrint) {
    const std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    std::unique_ptr<csv::Cell> c11 = std::make_unique<csv::Cell>("A"s), c12 = std::make_unique<csv::Cell>("B"s), c13 = std::make_unique<csv::Cell>("C"s);
    std::unique_ptr<csv::Cell> c21 = std::make_unique<csv::Cell>("D"s), c22 = std::make_unique<csv::Cell>("E"s), c23 = std::make_unique<csv::Cell>("F"s);
    std::unique_ptr<csv::Cell> c31 = std::make_unique<csv::Cell>("G"s), c32 = std::make_unique<csv::Cell>("H"s), c33 = std::make_unique<csv::Cell>("I"s);
    std::vector<std::unique_ptr<csv::Cell>> rC1;
    rC1.push_back(std::move(c11));
    rC1.push_back(std::move(c12));
    rC1.push_back(std::move(c13));
    std::vector<std::unique_ptr<csv::Cell>> rC2;
    rC2.push_back(std::move(c21));
    rC2.push_back(std::move(c22));
    rC2.push_back(std::move(c23));
    std::vector<std::unique_ptr<csv::Cell>> rC3;
    rC3.push_back(std::move(c31));
    rC3.push_back(std::move(c32));
    rC3.push_back(std::move(c33));

    const CSVRow r1{ 1, std::move(rC1) };
    const CSVRow r2{ 2, std::move(rC2) };
    const CSVRow r3{ 3, std::move(rC3) };

    const std::vector<CSVRow> treeData = { r1, r2, r3 };

    const CSVTree tree{ header, treeData };
    tree.Print();
}

TEST(CSVTree_Test, CheckPush) {
    const std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    std::unique_ptr<csv::Cell> c11 = std::make_unique<csv::Cell>("A"s), c12 = std::make_unique<csv::Cell>("B"s), c13 = std::make_unique<csv::Cell>("C"s);
    std::unique_ptr<csv::Cell> c21 = std::make_unique<csv::Cell>("D"s), c22 = std::make_unique<csv::Cell>("E"s), c23 = std::make_unique<csv::Cell>("F"s);
    std::unique_ptr<csv::Cell> c31 = std::make_unique<csv::Cell>("G"s), c32 = std::make_unique<csv::Cell>("H"s), c33 = std::make_unique<csv::Cell>("I"s);
    std::vector<std::unique_ptr<csv::Cell>> rC1;
    rC1.push_back(std::move(c11));
    rC1.push_back(std::move(c12));
    rC1.push_back(std::move(c13));
    std::vector<std::unique_ptr<csv::Cell>> rC2;
    rC2.push_back(std::move(c21));
    rC2.push_back(std::move(c22));
    rC2.push_back(std::move(c23));
    std::vector<std::unique_ptr<csv::Cell>> rC3;
    rC3.push_back(std::move(c31));
    rC3.push_back(std::move(c32));
    rC3.push_back(std::move(c33));

    CSVRow r1{ 1, std::move(rC1) };
    CSVRow r2{ 2, std::move(rC2) };
    CSVRow r3{ 3, std::move(rC3) };

    CSVTree tree{ header, std::vector<CSVRow>()};
    tree.PushRow(r1);
    tree.PushRow(r2);
    tree.PushRow(r3);

    std::vector<CSVRow> vecRows{std::move(r1), std::move(r2), std::move(r3)};
    auto vecRowsIt = vecRows.begin();
    const auto vecRowsItEnd = vecRows.end();

    for (auto itTree = tree.begin(), itTreeEnd = tree.end();
        (itTree != itTreeEnd) && (vecRowsIt != vecRowsItEnd);
        ++itTree, ++vecRowsIt) {
        //std::equal(itTree)
        EXPECT_EQ((*itTree)[0], (*vecRowsIt)[0]);
        EXPECT_EQ((*itTree)[1], (*vecRowsIt)[1]);
        EXPECT_EQ((*itTree)[2], (*vecRowsIt)[2]);
    }
}
