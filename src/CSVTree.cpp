#include <CSVTree.hpp>

#include <InconsistentRowErr.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std::string_literals;

namespace csv {
    bool CSVTree::isConsistent(const CSVRow& row) const noexcept {
        return header_.size() - 1 == row.Size();
    }

    size_t CSVTree::getHeaderIndex(const std::string& colName) const {
        const auto& indIter = std::find(header_.begin(), header_.end(), colName);

        if (indIter == header_.end()) {
            const std::string&& exMess = "No such colName = "s + colName;
            throw std::out_of_range(exMess);
        }
        return indIter - header_.begin();
    }

    CSVTree::CSVTree(const std::vector<std::string>& header,
                     const std::vector<CSVRow>& data)
        : header_(header), rows_(data) {
        for (const auto& row : rows_) {
            if (!isConsistent(row)) {
                throw InconsistentRowErr(header_.size() - 1, row.Size());
            }
        }
    }

    CSVTree::CSVTree(std::vector<std::string>&& header,
                     std::vector<CSVRow>&& data)
        : header_(std::move(header)), rows_(std::move(data)) {
        for (const auto& row : rows_) {
            if (!isConsistent(row)) {
                throw InconsistentRowErr(header_.size() - 1, row.Size());
            }
        }
    }

    std::string& CSVTree::GetCell(size_t rowInd, const std::string& colName) {
        // empty Names doesn't exist because if empty column Name occurs in the file, it will be presented as single whitespace
        assert(!colName.empty());
        // find usage because operator[] inserts value into unordered_map if it doesn't exist, so it can't be const. 
        for (auto& it : rows_) {
            const size_t recordInd = it.RowIndex();
            if (recordInd == rowInd) {
                return it.Data().second.at(getHeaderIndex(colName));
            }
        }
        
        throw;
    }

    std::string CSVTree::GetCell(size_t rowInd, const std::string& colName) const {
        // empty Names doesn't exist because if empty column Name occurs in the file, it will be presented as single whitespace
        assert(!colName.empty());
        // find usage because operator[] inserts value into unordered_map if it doesn't exist, so it can't be const. 
        for (const auto& it : rows_) {
            const size_t recordInd = it.RowIndex();
            if (recordInd == rowInd) {
                return it.RowCells().at(getHeaderIndex(colName));
            }
        }

        // @todo throw something
        throw; 
    }

    void CSVTree::PushRow(const CSVRow& row) {
        rows_.push_back(row);
    }

    void CSVTree::PushRow(CSVRow&& row) {
        rows_.push_back(std::move(row));
    }

    void CSVTree::RemoveRow(size_t rowInd) {
        auto findRecordCellsOnRowInd = [rowInd](const CSVRow& row) {
            return rowInd == row.RowIndex();
        };
        const auto elToErase = std::find_if(rows_.cbegin(), rows_.cend(), findRecordCellsOnRowInd);
        rows_.erase(elToErase);
    }

    void CSVTree::Print() const {
        std::cout << '|';
        for (const auto& headerIt : header_) {
            std::cout << headerIt << '|';
        }
        std::cout << std::endl;

        for (const auto& rowIt : rows_) {
            std::cout << '|' << rowIt.RowIndex() << '|';

            for (const auto& cellIt : rowIt.RowCells()) {
                std::cout << cellIt << '|';
            }
            std::cout << std::endl;
        }
    }

    std::vector<CSVRow>::iterator CSVTree::begin() {
        return rows_.begin();
    }

    std::vector<CSVRow>::iterator CSVTree::end() {
        return rows_.end();
    }

    std::vector<CSVRow>::const_iterator CSVTree::cbegin() const {
        return rows_.cbegin();
    }

    std::vector<CSVRow>::const_iterator CSVTree::cend() const {
        return rows_.cend();
    }
}

