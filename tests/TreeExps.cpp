#include <gtest/gtest.h>

#include <CSVTree.hpp>

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

TEST(Tree_Exp, CSVTree_EX) {
    std::vector<std::string> header{ " "s, "A"s, "B"s, "C"s };
    std::vector<std::string> r1{ "LL"s, "LEV"s, "TU"s };
    std::vector<std::string> r2{ "VM"s, "EL"s, "AL"s };
    std::vector<std::string> r3{ "LOW"s, "VIR"s, "MAC"s };

    std::unordered_map<size_t, std::vector<std::string>> treeData = { {1, r1}, {2, r2}, {3, r3} };

    CSVTree tree{ header, treeData };

    tree.Print();

}
