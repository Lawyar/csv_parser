#pragma once 

#include <Cell.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace csv {
    class CSVTree {
    private:
        // размер заголовка должен быть на единицу больше размера каждой записи,
        // так как заголовок содержит название столбца индексов
        std::vector<std::string> header_;
        std::unordered_map<size_t, std::vector<std::string>> data_;

        [[nodiscard]] bool isConsistent() const noexcept;

        [[nodiscard]] size_t getHeaderIndex(const std::string& colName) const;

    public:

        CSVTree(const std::vector<std::string>& header,
                const std::unordered_map<size_t, std::vector<std::string>>& data);

        CSVTree(std::vector<std::string>&& header,
                std::unordered_map<size_t, std::vector<std::string>>&& data);

        std::string& Get(size_t rowInd, const std::string& colName);

        std::string Get(size_t rowInd, const std::string& colName) const;

        void Print() const;
    };

}  // namespace csv
