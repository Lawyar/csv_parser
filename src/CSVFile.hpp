#pragma once

#include <CSVTree.hpp>

#include <filesystem>
#include <set>
#include <string>

namespace csv {

    class CSVFile {
    private:
        //CSVTree fileTree_;
        std::string header_;
        
        std::set<std::string> colNames_;
        std::set<size_t> rowIndexes_;

        // processHeader parses column names and counts them
        void processHeader();

        struct RowData {
            size_t index_ = 0;
            std::vector<std::string> data_;

            RowData(const std::string& row, size_t wordsCount);
        };

        RowData parseRow(const std::string& row) const;

    public:

        CSVFile(const std::filesystem::path& inputFile,
                const std::filesystem::path& outFile);

        CSVFile(const std::filesystem::path& filePath);

        //std::vector<std::string> GetHeader();
    };
}
