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
        std::pair<size_t, std::vector<std::unique_ptr<Cell>>> row_;

    public:
        CSVRow(const CSVRow& row);
        CSVRow(CSVRow&& row) noexcept;

        CSVRow(const std::vector<std::string>& rowStrWithIndex);
        CSVRow(std::vector<std::string>&& rowStrWithIndex);

        CSVRow(const std::pair < size_t, std::vector<std::unique_ptr<Cell>>>& indexedCells);
        CSVRow(std::pair < size_t, std::vector<std::unique_ptr<Cell>>>&& indexedCells);
        CSVRow(size_t rowIndex, std::vector<std::unique_ptr<Cell>>&& cells);
        CSVRow(size_t rowIndex, const std::vector<std::unique_ptr<Cell>>& cells);

        operator std::pair<size_t, std::vector<std::unique_ptr<Cell>>>() const;

        [[nodiscard]] csv::Cell& operator[](size_t index);
        [[nodiscard]] csv::Cell operator[](size_t index) const;

        [[nodiscard]] size_t RowIndex() const noexcept;
        [[nodiscard]] const std::vector<std::unique_ptr<csv::Cell>>& RowCells() const &;

        std::string ToString() const;

        void SetRowIndex(size_t newIndex) noexcept;

        [[nodiscard]] size_t Size() const noexcept;

        bool operator==(const CSVRow& rhs) const;
        bool operator!=(const CSVRow& rhs) const;
    };
}
