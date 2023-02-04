#pragma once

#include <string>
#include <stdexcept>
#include <vector>

namespace csv {
    // RowException
    class RowException final : public std::runtime_error {
    private:
        size_t expectedWords_;
        size_t countedWords_;

    public:
        RowException(size_t expectedWords, size_t countedWords);
    };


    // CSVRow
    class CSVRow final {
    private:
        // index and row cells
        std::pair<size_t, std::vector<std::string>> record_;

        // throws RowException if record is unconsistent with expected wordsCount
        [[nodiscard]] bool isConsistency(size_t expectedWordsCount) const;

    public:
        CSVRow(const std::pair<size_t, std::vector<std::string>>& record, size_t expectedWordsCount);
        CSVRow(std::pair<size_t, std::vector<std::string>>&& record, size_t expectedWordsCount);

        operator std::pair<size_t, std::vector<std::string>>() const;

        [[nodiscard]] std::string& operator[](size_t index);
        [[nodiscard]] std::string operator[](size_t index) const;

        [[nodiscard]] size_t RecordIndex() const noexcept;
        [[nodiscard]] std::vector<std::string> RecordCells() const;

        void SetRecordIndex(size_t newIndex) noexcept;
        void SetRecordCells(const std::vector<std::string>& newCells, size_t expectedWordsCount);
        void SetRecordCells(std::vector<std::string>&& newCells, size_t expectedWordsCount) noexcept;
    };
}
