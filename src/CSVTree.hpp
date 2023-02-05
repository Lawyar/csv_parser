#pragma once 

#include <Cell.hpp>
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

        [[nodiscard]] size_t getHeaderIndex(const std::string& colName) const;

    public:

        CSVTree(const std::vector<std::string>& header,
                const std::vector<CSVRow>& data);

        CSVTree(std::vector<std::string>&& header,
                std::vector<CSVRow>&& data);

        std::string& GetCell(size_t rowInd, const std::string& colName);
        std::string GetCell(size_t rowInd, const std::string& colName) const;

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
