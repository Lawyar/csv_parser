#pragma once 

#include <CellAbstract.hpp>
#include <CSVRow.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace csv {
    class CSVTree {
    private:
        // using RowsType = std::unordered_map<size_t, std::vector<std::string>>;
        // размер заголовка должен быть на единицу больше размера каждой записи,
        // так как заголовок содержит название столбца индексов
        std::vector<std::string> header_;
        std::vector<CSVRow> rows_;

        // checks consistency of existing header and new row
        [[nodiscard]] bool isConsistent(const CSVRow& row) const noexcept;

        [[nodiscard]] size_t getHeaderIndex(const std::string& colName) const;

    public:
        CSVTree() = default;

        CSVTree(const std::vector<std::string>& header,
                const std::vector<CSVRow>& data);

        CSVTree(std::vector<std::string>&& header,
                std::vector<CSVRow>&& data);

        void SetHeader(const std::vector<std::string>& header);
        void SetHeader(std::vector<std::string>&& header);

        // header_.size() - 1
        size_t ConsistentSize() const;

        csv::Cell GetCell(size_t rowInd, const std::string& colName) const&;

        void PushRow(const CSVRow& row);
        void PushRow(CSVRow&& row);

        void RemoveRow(size_t rowInd);

        void Print() const;

        std::vector<CSVRow>::iterator begin();
        std::vector<CSVRow>::iterator end();

        std::vector<CSVRow>::const_iterator cbegin() const;
        std::vector<CSVRow>::const_iterator cend() const;
    };

}  // namespace csv
