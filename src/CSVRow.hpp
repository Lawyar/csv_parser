#pragma once

#include <string>
#include <stdexcept>
#include <vector>

namespace csv {
    // CSVRow
    class CSVRow final {
    private:
        // index and row cells
        std::pair<size_t, std::vector<std::string>> row_;

    public:
        CSVRow(const std::pair<size_t, std::vector<std::string>>& record);
        CSVRow(std::pair<size_t, std::vector<std::string>>&& record);

        operator std::pair<size_t, std::vector<std::string>>() const;

        [[nodiscard]] std::string& operator[](size_t index);
        [[nodiscard]] std::string operator[](size_t index) const;

        [[nodiscard]] size_t RowIndex() const noexcept;
        [[nodiscard]] std::vector<std::string> RowCells() const;

        [[nodiscard]] std::pair<size_t, std::vector<std::string>> CloneRow() const;
        [[nodiscard]] std::pair<size_t, std::vector<std::string>>& Data()&;

        void SetRowIndex(size_t newIndex) noexcept;
        void SetRowCells(const std::vector<std::string>& newCells);
        void SetRowCells(std::vector<std::string>&& newCells) noexcept;

        [[nodiscard]] size_t Size() const noexcept;

        bool operator==(const CSVRow& rhs) const;
        bool operator!=(const CSVRow& rhs) const;
    };
}
