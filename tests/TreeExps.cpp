#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using Row = std::unordered_multimap<std::string, std::string>;
using Tree = std::map<size_t, Row>;

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
