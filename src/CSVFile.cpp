#include <CSVFile.hpp>

#include <BinOp.hpp>
#include <InconsistentRowErr.hpp>
#include <detail.hpp>

#include <iostream>
#include <fstream>

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
        size_t rowIndex = std::stoull(rowData[0]);
        rowData.erase(rowData.begin());

        // generate std::vector<csv::Cell>
        std::vector<std::unique_ptr<csv::Cell>> rowCells;
        rowCells.reserve(rowData.size());
        for (const auto& cellStr : rowData) {
            if (cellStr[0] == '=') {
                try {
                    BinOp bOp(cellStr);
                    std::unique_ptr<Cell> currCell = std::make_unique<BinOp>(bOp);
                    rowCells.push_back(std::move(currCell));
                    continue;
                }
                catch (BinOpConstructionErr& ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
            std::unique_ptr<Cell> currCell = std::make_unique<Cell>(cellStr);
            rowCells.push_back(std::move(currCell));
        }

        // pushing row into the tree
        CSVRow row{ rowIndex, std::move(rowCells)};
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
        // std::ofstream oFile = validateAndCreateOFile(outFile);
        std::ofstream oFile(outFile);
        if (!oFile.good()) {
            throw std::runtime_error("invalid file");
        }

        // get header
        std::string headerStr;
        iFile_ >> headerStr;
        processHeader(std::move(headerStr));

        // file iteration
        size_t curRow = 0;
        while (iFile_.good()) {
            // parsing row
            std::string rowStr;
            iFile_ >> rowStr;
            parseRow(rowStr);

            // writing to oFile
            oFile << fileTree_[curRow].ToString() << std::endl;
            curRow++;
        }
    }

    CSVFile::CSVFile(const fs::path& filePath)
    : CSVFile(filePath, detail_::genDefaultOutName(filePath)) { }
    
}  // namespace csv
