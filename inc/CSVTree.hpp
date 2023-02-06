#pragma once 

#include <CellAbstract.hpp>
#include <CSVRow.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace csv {
    class CSVTree {
    private:
        std::vector<std::string> header_;

        // expected that CSVRow::Size() == header.size() - 1
        std::vector<CSVRow> rows_;

        // checks consistency of existing header and new row
        [[nodiscard]] bool isConsistent(const CSVRow& row) const noexcept;

    public:
        CSVTree() = default;

        CSVTree(const std::vector<std::string>& header,
                const std::vector<CSVRow>& data);

        CSVTree(std::vector<std::string>&& header,
                std::vector<CSVRow>&& data);

        // changing the header_ field. throws exception if new header isn't consistent with existing rows
        void SetHeader(const std::vector<std::string>& header);
        void SetHeader(std::vector<std::string>&& header);

        // header_.size() - 1
        [[nodiscard]] size_t ConsistentSize() const;

        // casts to std::unique_ptr<csv::BinOp> if possible
        [[nodiscard]] std::unique_ptr<CellAbstract> GetCell(size_t rowInd, const std::string& colName) const&;

        // push_back into rows_
        void PushRow(const CSVRow& row);
        void PushRow(CSVRow&& row);
        
        [[nodiscard]] const CSVRow& GetRow(size_t rowInd) const&;

        [[nodiscard]] const CSVRow& operator[](size_t rowInd) const&;

        // returns position of colName from the header
        [[nodiscard]] size_t GetHeaderIndex(const std::string& colName) const;

        [[nodiscard]] std::vector<CSVRow>::iterator begin(); // rows_.begin()
        [[nodiscard]] std::vector<CSVRow>::iterator end(); // rows_.end()

        [[nodiscard]] std::vector<CSVRow>::const_iterator cbegin() const; // rows_.cbegin()
        [[nodiscard]] std::vector<CSVRow>::const_iterator cend() const; // rows.cend()
    };

}  // namespace csv
