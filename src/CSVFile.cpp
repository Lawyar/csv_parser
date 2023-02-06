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

namespace {
    constexpr char POSSIBLE_SIGNS[] = "+-*/";
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

    void CSVFile::processCell(CellAbstract& cell) {
        auto processLhs = [this, &cell]() {
            const std::string& strData = cell.StrData();
            size_t signPos = strData.find_first_of(POSSIBLE_SIGNS, 2);
            std::string lhsStr = strData.substr(1, signPos - 1);

            // extract cellName and indexVal from lhsStr
            std::string::iterator indexIt = std::find_if(lhsStr.begin(), lhsStr.end(), isdigit);
            if (indexIt != lhsStr.end()) {
                std::string cellName = lhsStr.substr(0, indexIt - lhsStr.begin());
                size_t endd = indexIt - lhsStr.begin();
                size_t indexVal = std::stoull(lhsStr.substr(indexIt - lhsStr.begin()));

                // get fileTree_[] 
                std::unique_ptr<CellAbstract> lhsCell = fileTree_.GetCell(indexVal, cellName);
                processCell(*lhsCell);
                const std::string& cellStr = lhsCell->ToString();
                int cellVal = std::stoi(cellStr);
                BinOp& cellOp = static_cast<BinOp&>(cell);
                cellOp.SetLhs(cellVal);
            }
        };

        auto processRhs = [this, &cell]() {
            const std::string& strData = cell.StrData();
            size_t signPos = strData.find_first_of(POSSIBLE_SIGNS, 2);
            std::string rhsStr = strData.substr(signPos + 1);

            // extract cellName and indexVal from lhsStr
            std::string::iterator indexIt = std::find_if(rhsStr.begin(), rhsStr.end(), isdigit);
            if (indexIt != rhsStr.end()) {
                std::string cellName = rhsStr.substr(0, indexIt - rhsStr.begin());
                size_t indexVal = std::stoull(rhsStr.substr(indexIt - rhsStr.begin()));

                // get fileTree_[] 
                std::unique_ptr<CellAbstract> rhsCell = fileTree_.GetCell(indexVal, cellName);
                processCell(*rhsCell);
                const std::string& cellStr = rhsCell->ToString();
                int cellVal = std::stoi(cellStr);
                BinOp& cellOp = static_cast<BinOp&>(cell);
                cellOp.SetRhs(cellVal);
            }
        };

        try {
            cell.Evaluate();
        }
        catch (BinOpLhsErr&) {
            processLhs();
            cell.Evaluate();
        }
        catch (BinOpRhsErr&) {
            processRhs();
            cell.Evaluate();
        }
        catch (BinOpSubstitutionErr&) {
            processLhs();
            processRhs();
            cell.Evaluate();
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
            //oFile << fileTree_[curRow].ToString() << std::endl;
            curRow++;
        }

        // BinOp evaluation
        for (auto& it : fileTree_) {
            for (auto& it2 : it) {
                processCell(*it2);
            }
            oFile << it.ToString() << std::endl;
        }
    }

    CSVFile::CSVFile(const fs::path& filePath)
    : CSVFile(filePath, detail_::genDefaultOutName(filePath)) { }
    
}  // namespace csv
