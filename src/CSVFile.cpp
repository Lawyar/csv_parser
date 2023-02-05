#include <CSVFile.hpp>

#include <InconsistentRowErr.hpp>
#include <detail.hpp>

#include <iostream>
#include <fstream>
#include <set>

namespace fs = std::filesystem;
using strsize_t = std::string::size_type;

namespace {
    std::ifstream validateAndCreateIFile(const fs::path& inputFile) {
        if (!(fs::exists(inputFile) || fs::is_regular_file(inputFile))) {
            throw std::runtime_error("invalid path");
        }

        std::ifstream iFile(inputFile);
        // we need to check this because of the possible race condition or file inaccessibility
        // https://stackoverflow.com/questions/36022189/what-guarantee-do-i-have-after-is-regular-file
        if (!iFile.good()) {
            throw std::runtime_error("invalid file");
        }

        return iFile;
    }

    std::ofstream validateAndCreateOFile(const fs::path& outputFile) {
        std::ofstream oFile(outputFile);
        if (!oFile.good()) {
            throw std::runtime_error("invalid file");
        }

        return oFile;
    }
}

namespace csv {
    void CSVFile::processHeader(std::string&& headerStr) {
        size_t headerSize = std::count(headerStr.begin(), headerStr.end(), ',');
        std::vector<std::string> header = detail_::strSplit(headerStr, headerSize, ',');
        fileTree_.SetHeader(header);
    }

    void CSVFile::parseRow(const std::string& rowStr) {
        std::vector<std::string> rowData = detail_::strSplit(rowStr, fileTree_.ConsistentSize(), ',');

        // get row index
        int rowIndex = std::stoi(rowData[0]);
        rowData.erase(rowData.begin());

        // generate std::vector<csv::Cell>
        std::vector<std::shared_ptr<csv::Cell>> rowCells;
        rowCells.reserve(rowData.size());
        for (const auto& cellStr : rowData) {
            if (cellStr[0] == '=') {
                // validate cellStr for BinOp. Validate faulty leads to csv::Cell pushing
                // process BinOp
            }
            else {
                std::shared_ptr<Cell> currCell = std::make_shared<Cell>(cellStr);
                rowCells.push_back(currCell);
            }
        }

        // pushing row into the tree
        CSVRow row{ {rowIndex, rowCells} };
        try {
            fileTree_.PushRow(std::move(row));
        }
        catch (csv::InconsistentRowErr& ex) {
            std::cout << "Warning: row with index " << rowIndex
                      << "wasn\'t pushed. Reason: " << ex.what() << std::endl;
        }
    }

    CSVFile::CSVFile(const fs::path& inputFile, const fs::path& outFile) {
        // prepare IO files
        iFile_ = validateAndCreateIFile(inputFile);
        std::ofstream oFile = validateAndCreateOFile(outFile);

        // get header
        std::string headerStr;
        iFile_ >> headerStr;
        processHeader(std::move(headerStr));

        // file iteration
        while (iFile_.good()) {
            // parsing row
            std::string rowStr;
            iFile_ >> rowStr;
            parseRow(rowStr);

            // writing to oFile
            oFile << rowStr << std::endl;
        }
    }

    CSVFile::CSVFile(const fs::path& filePath)
    : CSVFile(filePath, detail_::genDefaultOutName(filePath)) { }
    
}  // namespace csv
