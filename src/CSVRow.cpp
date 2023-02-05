#include <CSVRow.hpp>

#include <charconv>

using namespace std::string_literals;

namespace csv {
    //CSVRow::CSVRow(const std::vector<std::string>& rowWithIndex) {
    //    // @todo exception safety
    //    row_.first = std::stoi(rowWithIndex[0]);
    //    std::copy(rowWithIndex.begin() + 1, rowWithIndex.end(), row_.second.begin());
    //}

    //CSVRow::CSVRow(std::vector<std::string>&& rowWithIndex) {
    //    row_.first = std::stoi(rowWithIndex[0]);
    //    rowWithIndex.erase(rowWithIndex.begin());
    //    row_.second = std::move(rowWithIndex);
    //}

    //CSVRow::CSVRow(const std::pair<size_t, std::vector<std::string>>& record)
    //    : row_(record) { }

    //CSVRow::CSVRow(std::pair<size_t, std::vector<std::string>>&& record)
    //    : row_(std::move(record)) { }

    CSVRow::CSVRow(const std::pair<size_t, std::vector<std::shared_ptr<Cell>>>& rowData)
        : row_(rowData){ }

    CSVRow::operator std::pair<size_t, std::vector<std::shared_ptr<Cell>>>() const {
        return row_;
    }

    /*csv::Cell& CSVRow::operator[](size_t index) {
        return row_.second.at(index);
    }

    csv::Cell CSVRow::operator[](size_t index) const {
        return row_.second.at(index).get();
    }*/

    size_t CSVRow::RowIndex() const noexcept {
        return row_.first;
    }

    std::vector<std::shared_ptr<csv::Cell>> CSVRow::RowCells() const {
        return row_.second;
    }

    std::pair<size_t, std::vector<std::shared_ptr<Cell>>> CSVRow::CloneRow() const {
        return row_;
    }

    std::pair<size_t, std::vector<std::shared_ptr<Cell>>>& CSVRow::Data() & {
        return row_;
    }

    void CSVRow::SetRowIndex(size_t newIndex) noexcept {
        row_.first = newIndex;
    }

    void CSVRow::SetRowCells(const std::vector<std::shared_ptr<Cell>>& newCells) {
        CSVRow tmp({ row_.first, newCells });
        *this = std::move(tmp);
    }

    void CSVRow::SetRowCells(std::vector<std::shared_ptr<Cell>>&& newCells) noexcept {
        CSVRow tmp({ row_.first, std::move(newCells) });
        *this = std::move(tmp);
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
