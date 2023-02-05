#include <gtest/gtest.h>

#include <CSVTree.hpp>
#include <CSVRow.hpp>

using namespace std::string_literals;

#if 0
using Row = std::unordered_map<std::string, std::string>;
using Tree = std::unordered_map<size_t, Row>;

class CSVRow {
    size_t index_;
    std::vector<std::string> rowData_;
};
#endif 

#if 0
TEST(Tree_Exp, Indexing) {
    Tree t;
    std::string cN1 = " ", cN2 = "A", cN3 = "B";
    size_t ind1 = 1, ind2 = 5, ind3 = 2;
    std::string t1N2 = "a1", t1N3 = "b1";
    std::string t2N2 = "a2", t2N3 = "b2";
    std::string t3N2 = "a3", t3N3 = "b3";
    Row title{ {cN1, cN1}, {cN2, cN2}, {cN3, cN3}};
    Row r1{ {cN2, t1N2}, {cN3, t1N3} };
    Row r2{ {cN2, t2N2}, {cN3, t2N3} };
    Row r3{ {cN2, t3N2}, {cN3, t3N3} };

    t.insert({ ind1, r1 });
    t.insert({ ind2, r2 });
    t.insert({ ind3, r3 });
    std::cout << '|' << cN1 << "|" << cN2 << "|" << cN3 << '|' << std::endl;
    for (auto& it : t) {
        std::cout << '|' << it.first << '|';
        for (auto& it2 : it.second) {
            std::cout << it2.second << '|';
        }
        std::cout << std::endl;
    }
}
#endif

using csv::CSVTree;
using csv::CSVRow;

TEST(Tree_Exp, CheckPrint) {
    const std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    const CSVRow r1{ {1, {"LL"s, "LEV"s, "TU"s}} };
    const CSVRow r2{ {2, {"VM"s, "EL"s, "AL"s}} };
    const CSVRow r3{ {3, {"LOW"s, "VIR"s, "MAC"s }} };

    const std::vector<CSVRow> treeData = { r1, r2, r3 };

    const CSVTree tree{ header, treeData };

    tree.Print();
}

TEST(Tree_Exp, CheckPush) {
    const std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    const CSVRow r1{ {1, { "LLV"s, "VEL"s, "LMA"s }} };
    const CSVRow r2{ {2, { "MLO"s, "VIR"s, "CHI"s }} };
    const CSVRow r3{{3, { "WLE"s, "TUA"s, "NE"s }} };
    const CSVRow r4{{4, { "GUN"s, "KEL"s, "LY"s }} };

    CSVTree tree{ header, std::vector<CSVRow>()};
    tree.PushRow(r1);
    tree.PushRow(r2);
    tree.PushRow(r3);
    tree.PushRow(r4);

    std::vector<CSVRow> vecRows{r1, r2, r3, r4};
    auto vecRowsIt = vecRows.begin();
    const auto vecRowsItEnd = vecRows.end();

    for (auto itTree = tree.begin(), itTreeEnd = tree.end();
        (itTree != itTreeEnd) && (vecRowsIt != vecRowsItEnd);
        ++itTree, ++vecRowsIt) {
        //std::equal(itTree)
        EXPECT_EQ(*itTree, *vecRowsIt);
    }
}

TEST(Tree_Exp, CheckPush2) {
    const std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    const CSVRow r1{ {1, { "LLV"s, "VEL"s, "LMA"s }} };
    const CSVRow r2{ {2, { "MLO"s, "VIR"s, "CHI"s }} };
    const CSVRow r3{ {3, { "WLE"s, "TUA"s, "NE"s }} };
    const CSVRow r4{ {4, { "GUN"s, "KEL"s, "LY"s }} };

    CSVTree tree{ header, std::vector<CSVRow>() };
    tree.PushRow(r1);
    tree.PushRow(r2);
    tree.PushRow(r3);
    tree.PushRow(r4);

    std::vector<CSVRow> vecRows{ r2, r3, r4 };
    auto vecRowsIt = vecRows.begin();
    const auto vecRowsItEnd = vecRows.end();

    for (auto itTree = tree.begin(), itTreeEnd = tree.end();
        (itTree != itTreeEnd) && (vecRowsIt != vecRowsItEnd);
        ++itTree, ++vecRowsIt) {
        EXPECT_NE(*itTree, *vecRowsIt);
    }
}

TEST(Tree_Exp, CheckRemove) {
    std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    const CSVRow r1{ {1, { "LLV"s, "VEL"s, "LMA"s }} };
    const CSVRow r2{ {2, { "MLO"s, "VIR"s, "CHI"s }} };
    const CSVRow r3{ {3, { "WLE"s, "TUA"s, "NE"s }} };
    const CSVRow r4{ {4, { "GUN"s, "KEL"s, "LY"s }} };

    std::unordered_map<size_t, std::vector<std::string>> treeData;

    CSVTree tree{ header, std::vector<CSVRow>() };
    tree.PushRow(r1);
    tree.PushRow(r2);
    tree.PushRow(r3);
    tree.PushRow(r4);

    tree.RemoveRow(r3.RowIndex());

    std::vector<CSVRow> vecRows{ r1, r2, r4 };
    auto vecRowsIt = vecRows.begin(), vecRowsItEnd = vecRows.end();

    for (auto itTree = tree.begin(), itTreeEnd = tree.end();
        (itTree != itTreeEnd) && (vecRowsIt != vecRowsItEnd);
        ++itTree, ++vecRowsIt) {
        EXPECT_EQ(*itTree, *vecRowsIt);
    }
}
