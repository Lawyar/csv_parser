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
        std::pair<size_t, std::vector<std::shared_ptr<Cell>>> row_;

    public:
        /*CSVRow(const std::vector<std::string>& rowWithIndex);
        CSVRow(std::vector<std::string>&& rowWithIndex);
        CSVRow(const std::pair<size_t, std::vector<std::string>>& record);
        CSVRow(std::pair<size_t, std::vector<std::string>>&& record);*/

        CSVRow(const std::pair<size_t, std::vector<std::shared_ptr<Cell>>>& rowData);

        operator std::pair<size_t, std::vector<std::shared_ptr<Cell>>>() const;

        [[nodiscard]] csv::Cell& operator[](size_t index);
        [[nodiscard]] std::string operator[](size_t index) const;

        [[nodiscard]] size_t RowIndex() const noexcept;
        [[nodiscard]] std::vector<std::shared_ptr<csv::Cell>> RowCells() const;

        [[nodiscard]] std::pair<size_t, std::vector<std::shared_ptr<Cell>>> CloneRow() const;
        [[nodiscard]] std::pair<size_t, std::vector<std::shared_ptr<Cell>>>& Data()&;

        void SetRowIndex(size_t newIndex) noexcept;
        void SetRowCells(const std::vector<std::shared_ptr<Cell>>& newCells);
        void SetRowCells(std::vector<std::shared_ptr<Cell>>&& newCells) noexcept;

        [[nodiscard]] size_t Size() const noexcept;

        bool operator==(const CSVRow& rhs) const;
        bool operator!=(const CSVRow& rhs) const;
    };
}
