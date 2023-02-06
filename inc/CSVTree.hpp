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
        // ������ ��������� ������ ���� �� ������� ������ ������� ������ ������,
        // ��� ��� ��������� �������� �������� ������� ��������
        std::vector<std::string> header_;
        std::vector<CSVRow> rows_;

        // checks consistency of existing header and new row
        [[nodiscard]] bool isConsistent(const CSVRow& row) const noexcept;

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

        std::unique_ptr<csv::CellAbstract> GetCell(size_t rowInd, const std::string& colName) const&;

        void PushRow(const CSVRow& row);
        void PushRow(CSVRow&& row);

        void RemoveRow(size_t rowInd);

        const CSVRow& GetRow(size_t rowInd) const&;

        const CSVRow& operator[](size_t rowInd) const&;

        void Print() const;

        [[nodiscard]] size_t GetHeaderIndex(const std::string& colName) const;

        std::vector<CSVRow>::iterator begin(); // rows_.begin()
        std::vector<CSVRow>::iterator end(); // rows_.end()

        std::vector<CSVRow>::const_iterator cbegin() const; // rows_.cbegin()
        std::vector<CSVRow>::const_iterator cend() const; // rows.cend()
    };

}  // namespace csv
