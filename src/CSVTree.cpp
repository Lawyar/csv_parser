#include <CSVTree.hpp>

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std::string_literals;

namespace csv {
    bool CSVTree::isConsistent() const noexcept {
        assert(!header_.empty());
        const size_t consistentSize = header_.size() - 1;
        for (const auto& it : rows_) {
            if (it.second.size() != consistentSize) {
                return false;
            }
        }

        return true;
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
                     const std::unordered_map<size_t, std::vector<std::string>>& data)
        : header_(header), rows_(data) {
        if (!isConsistent()) {
            // @todo throw
        }
    }

    CSVTree::CSVTree(std::vector<std::string>&& header,
                     std::unordered_map<size_t, std::vector<std::string>>&& data)
        : header_(std::move(header)), rows_(std::move(data)) {
        if (!isConsistent()) {
            // @todo throw
        }
    }

    std::string& CSVTree::Get(size_t rowInd, const std::string& colName) {
        // empty Names doesn't exist because if empty column Name occurs in the file, it will be presented as single whitespace
        assert(!colName.empty());
        // find usage because operator[] inserts value into unordered_map if it doesn't exist, so it can't be const. 
        return rows_.find(rowInd)->second[getHeaderIndex(colName)];
    }

    std::string CSVTree::Get(size_t rowInd, const std::string& colName) const {
        assert(!colName.empty());
        return rows_.find(rowInd)->second[getHeaderIndex(colName)];
    }

    void CSVTree::Print() const {
        std::cout << '|';
        for (const auto& headerIt : header_) {
            std::cout << headerIt << '|';
        }
        std::cout << std::endl;

        for (const auto& rowIt : rows_) {
            std::cout << '|' << rowIt.first << '|';

            for (const auto& cellIt : rowIt.second) {
                std::cout << cellIt << '|';
            }
            std::cout << std::endl;
        }
    }
}

