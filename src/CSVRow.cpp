#include <CSVRow.hpp>

#include <charconv>

using namespace std::string_literals;

namespace csv {
    CSVRow::CSVRow(const CSVRow& row) : CSVRow(row.row_) { }

    CSVRow::CSVRow(CSVRow&& row) noexcept : CSVRow(std::move(row.row_)) { }

    CSVRow::CSVRow(const std::vector<std::string>& rowStrWithIndex) {
        row_.first = std::stoi(rowStrWithIndex[0]);
        row_.second.reserve(rowStrWithIndex.size() - 1);

        for (auto strIt = rowStrWithIndex.begin() + 1; strIt != rowStrWithIndex.end(); ++strIt) {
            row_.second.push_back(std::make_unique<Cell>(*strIt));
        }
    }

    CSVRow::CSVRow(std::vector<std::string>&& rowStrWithIndex) {
        row_.first = std::stoi(rowStrWithIndex[0]);
        row_.second.reserve(rowStrWithIndex.size() - 1);

        for (auto strIt = rowStrWithIndex.begin() + 1; strIt != rowStrWithIndex.end(); ++strIt) {
            row_.second.push_back(std::make_unique<Cell>(std::move(*strIt)));
        }
    }

    CSVRow::CSVRow(const std::pair<size_t, std::vector<std::unique_ptr<Cell>>>& indexedCells)
        : CSVRow(indexedCells.first, indexedCells.second){ }

    CSVRow::CSVRow(std::pair<size_t, std::vector<std::unique_ptr<Cell>>>&& indexedCells)
        : CSVRow(indexedCells.first, std::move(indexedCells.second)) { }

    CSVRow::CSVRow(size_t rowIndex, std::vector<std::unique_ptr<Cell>>&& cells)
        : row_({ rowIndex, std::move(cells) }) {}

    CSVRow::CSVRow(size_t rowIndex, const std::vector<std::unique_ptr<Cell>>& cells) {
        row_.first = rowIndex;
        row_.second.reserve(cells.size());
        for (const auto& cell : cells) {
            row_.second.push_back(std::make_unique<Cell>(*cell));
        }
    }

    CSVRow::operator std::pair<size_t, std::vector<std::unique_ptr<Cell>>>() const {
        CSVRow copy(row_.first, row_.second);
        return std::make_pair(copy.row_.first, std::move(copy.row_.second));
    }

    csv::Cell& CSVRow::operator[](size_t index) {
        return *row_.second.at(index);
    }

    csv::Cell CSVRow::operator[](size_t index) const {
        return *row_.second.at(index);
    }

    size_t CSVRow::RowIndex() const noexcept {
        return row_.first;
    }

    const std::vector<std::unique_ptr<csv::Cell>>& CSVRow::RowCells() const & {
        return row_.second;
    }

    std::string CSVRow::ToString() const {
        std::string res = std::to_string(row_.first);
        for (const auto& it : row_.second) {
            res += ',' + it->ToString();
        }

        return res;
    }

    void CSVRow::SetRowIndex(size_t newIndex) noexcept {
        row_.first = newIndex;
    }

    size_t CSVRow::Size() const noexcept {
        return row_.second.size();
    }

    bool CSVRow::operator==(const CSVRow& rhs) const {
        return (row_.first == rhs.RowIndex()) && 
            std::equal(row_.second.cbegin(), row_.second.cend(), rhs.row_.second.cbegin());
    }

    bool CSVRow::operator!=(const CSVRow& rhs) const {
        return !(*this == rhs);
    }
}
