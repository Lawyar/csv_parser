#pragma once

#include <CSVTree.hpp>

#include <fstream>
#include <filesystem>
#include <string>

namespace csv {

    class CSVFile {
    private:
        CSVTree fileTree_;
        std::ifstream iFile_;

        // processHeader parses column names and counts them
        void processHeader(std::string&& headerStr);

        void parseRow(const std::string& rowStr);

        void processCell(CellAbstract& cell);

    public:

        CSVFile(const std::filesystem::path& inputFile,
                const std::filesystem::path& outFile);

        CSVFile(const std::filesystem::path& filePath);

        //std::vector<std::string> GetHeader();
    };
}
