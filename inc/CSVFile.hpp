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
        void processHeader(const std::string& headerStr);

        void parseRow(const std::string& rowStr);

        void processCell(CellAbstract& cell);

        void processRhs(CellAbstract& cell);
        void processLhs(CellAbstract& cell);

    public:

        CSVFile(const std::filesystem::path& inputFile,
                const std::filesystem::path& outFile);

        CSVFile(const std::filesystem::path& filePath);

        //std::vector<std::string> GetHeader();
    };
}
