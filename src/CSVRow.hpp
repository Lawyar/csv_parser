#pragma once

#include <Cell.hpp>

#include <string>
#include <stdexcept>
#include <vector>

namespace csv {
    // CSVRow
    class CSVRow final {
    private:
        // index and row cells
        std::pair<size_t, std::vector<std::reference_wrapper<Cell>>> row_;

    public:
        /*CSVRow(const std::vector<std::string>& rowWithIndex);
        CSVRow(std::vector<std::string>&& rowWithIndex);
        CSVRow(const std::pair<size_t, std::vector<std::string>>& record);
        CSVRow(std::pair<size_t, std::vector<std::string>>&& record);*/

        CSVRow(const std::pair<size_t, std::vector<std::reference_wrapper<Cell>>>& rowData);

        operator std::pair<size_t, std::vector<std::reference_wrapper<Cell>>>() const;

        [[nodiscard]] csv::Cell& operator[](size_t index);
        [[nodiscard]] std::string operator[](size_t index) const;

        [[nodiscard]] size_t RowIndex() const noexcept;
        [[nodiscard]] std::vector<std::reference_wrapper<csv::Cell>> RowCells() const;

        [[nodiscard]] std::pair<size_t, std::vector<std::reference_wrapper<Cell>>> CloneRow() const;
        [[nodiscard]] std::pair<size_t, std::vector<std::reference_wrapper<Cell>>>& Data()&;

        void SetRowIndex(size_t newIndex) noexcept;
        void SetRowCells(const std::vector<std::reference_wrapper<Cell>>& newCells);
        void SetRowCells(std::vector<std::reference_wrapper<Cell>>&& newCells) noexcept;

        [[nodiscard]] size_t Size() const noexcept;

        bool operator==(const CSVRow& rhs) const;
        bool operator!=(const CSVRow& rhs) const;
    };
}
