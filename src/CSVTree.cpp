#include <CSVTree.hpp>

#include <InconsistentRowErr.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "BinOp.hpp"

using namespace std::string_literals;

namespace {
    bool isConsistentRow(const csv::CSVRow& row, size_t consistentSize) {
        return consistentSize == row.Size();
    }
}

namespace csv {
    bool CSVTree::isConsistent(const CSVRow& row) const noexcept {
        return isConsistentRow(row, header_.size() - 1);
    }

    size_t CSVTree::GetHeaderIndex(const std::string& colName) const {
        const auto& indIter = std::find(header_.begin(), header_.end(), colName);

        if (indIter == header_.end()) {
            const std::string&& exMess = "No such colName = "s + colName;
            throw std::out_of_range(exMess);
        }
        return indIter - header_.begin() - 1;
    }

    CSVTree::CSVTree(const std::vector<std::string>& header,
                     const std::vector<CSVRow>& data)
        : header_(header) {
        for (const auto& row : data) {
            rows_.push_back(row);
        }

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

    void CSVTree::SetHeader(const std::vector<std::string>& header) {
        size_t consistentSize = header.size() - 1;
        for (const auto& row : rows_) {
            if (!isConsistentRow(row, consistentSize)) {
                throw InconsistentRowErr(header_.size() - 1, row.Size());
            }
        }

        header_ = header;
    }

    void CSVTree::SetHeader(std::vector<std::string>&& header) {
        header_ = std::move(header);
    }

    size_t CSVTree::ConsistentSize() const {
        return header_.size() - 1;
    }

    std::unique_ptr<csv::CellAbstract> CSVTree::GetCell(size_t rowInd,
                                                        const std::string& colName) const & {
        const CSVRow& row = GetRow(rowInd);
        const Cell& cell = row[GetHeaderIndex(colName)];
        try {
            auto binOpCell = static_cast<BinOp>(cell);
            return cell.Clone();
        }
        catch (BinOpConstructionErr&) {
            return cell.Clone();
        }
    }

    void CSVTree::PushRow(const CSVRow& row) {
        if (!isConsistent(row)) {
            throw InconsistentRowErr(header_.size() - 1, row.Size());
        }
        rows_.push_back(row);
    }

    void CSVTree::PushRow(CSVRow&& row) {
        if (!isConsistent(row)) {
            throw InconsistentRowErr(header_.size() - 1, row.Size());
        }
        rows_.push_back(std::move(row));
    }

    const CSVRow& CSVTree::GetRow(size_t rowInd) const& {
        for (const auto& it : rows_) {
            if (it.RowIndex() == rowInd) {
                return it;
            }
        }

        throw std::out_of_range("Element with given rowInd"s + std::to_string(rowInd) + "doesn't exist"s);
    }

    const CSVRow& CSVTree::operator[](size_t rowInd) const & {
        return rows_[rowInd];
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

