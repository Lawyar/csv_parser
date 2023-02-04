#include <CSVRow.hpp>

#include <charconv>

using namespace std::string_literals;

namespace {
    // @todo it is unsafe to use std::string with exceptions because std::string ctor can throw on allocation
    std::string generateMessage(size_t expectedWords, size_t countedWords) {
        std::string message = "RowException: expected = "s + 
            std::to_string(expectedWords) + " , counted = "s + std::to_string(countedWords);

        return message; 
    }
}

namespace csv {
    // RowException
    RowException::RowException(size_t expectedWords, size_t countedWords)
    : runtime_error(generateMessage(expectedWords, countedWords)), 
      expectedWords_(expectedWords), countedWords_(countedWords) { }


    // CSVRow
    bool CSVRow::isConsistency(size_t expectedWordsCount) const {
        return record_.second.size() == expectedWordsCount;
    }

    CSVRow::CSVRow(const std::pair<size_t, std::vector<std::string>>& record, size_t expectedWordsCount)
        : record_(record) {
        !isConsistency(expectedWordsCount) ? throw RowException(expectedWordsCount, record_.second.size()) : nullptr;
    }

    CSVRow::CSVRow(std::pair<size_t, std::vector<std::string>>&& record, size_t expectedWordsCount)
        : record_(std::move(record)) {
        !isConsistency(expectedWordsCount) ? throw RowException(expectedWordsCount, record_.second.size()) : nullptr;
    }

    CSVRow::operator std::pair<size_t, std::vector<std::string>>() const {
        return record_;
    }

    std::string& CSVRow::operator[](size_t index) {
        return record_.second.at(index);
    }

    std::string CSVRow::operator[](size_t index) const {
        return record_.second.at(index);
    }

    size_t CSVRow::RecordIndex() const noexcept {
        return record_.first;
    }

    std::vector<std::string> CSVRow::RecordCells() const {
        return record_.second;
    }

    void CSVRow::SetRecordIndex(size_t newIndex) noexcept {
        record_.first = newIndex;
    }

    void CSVRow::SetRecordCells(const std::vector<std::string>& newCells, size_t expectedWordsCount) {
        CSVRow tmp({ record_.first, newCells }, expectedWordsCount);
        *this = std::move(tmp);
    }

    void CSVRow::SetRecordCells(std::vector<std::string>&& newCells, size_t expectedWordsCount) noexcept {
        CSVRow tmp({ record_.first, std::move(newCells) }, expectedWordsCount);
        *this = std::move(tmp);
    }
}
