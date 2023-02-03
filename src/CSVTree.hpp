#pragma once 

#include <Cell.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace csv {
    class CSVTree {
        using TreeType = std::unordered_map<std::string, std::unordered_map<int, Cell>>;
    private:
        TreeType tree_;
        bool toLazyEval_;

    public:
        CSVTree(const std::vector<std::string>& colNames);

        void PushCell(const std::string& colName, const Cell& cell);

        void InsertCol(const std::string& colName, const std::vector<Cell>& colCells);

        void RemoveCell(const std::string& colName, const Cell& cell);

        void RemoveCol(const std::string& colName);

        void EvaluateAll();

        void Evaluate(const std::string& colName, const Cell& cell);
    };

}  // namespace csv
