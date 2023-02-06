#include <CSVFile.hpp>

#include <BinOp.hpp>
#include <InconsistentRowErr.hpp>
#include <detail.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

// WIN32 std::execution::par implementation doesn't require tbb
// @todo add tbb dependency in the cmake
#ifdef _WIN32
#include <execution>
#endif

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
}

namespace {
    constexpr char POSSIBLE_SIGNS[] = "+-*/";
}

namespace csv {
    void CSVFile::processHeader(const std::string& headerStr) {
        const size_t headerSize = std::count(headerStr.begin(), headerStr.end(), ',');
        std::vector<std::string> header = detail_::strSplit(headerStr, headerSize, ',');
        fileTree_.SetHeader(std::move(header));
    }

    void CSVFile::parseRow(const std::string& rowStr) {
        std::vector<std::string> rowData = detail_::strSplit(rowStr, fileTree_.ConsistentSize(), ',');

        // get row index
        size_t rowIndex;
        try {
            rowIndex = std::stoull(rowData[0]);
        }
        catch (std::invalid_argument&) {
            return;
        }
        catch (std::out_of_range&) {
            return;
        }
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

    void CSVFile::processLhs(CellAbstract& cell) {
        const std::string& strData = cell.StrData();
        const size_t signPos = strData.find_first_of(POSSIBLE_SIGNS, 2);
        std::string lhsStr = strData.substr(1, signPos - 1);

        // extract cellName and indexVal from lhsStr
        const std::string::iterator indexIt = std::find_if(lhsStr.begin(), lhsStr.end(), isdigit);
        if (indexIt != lhsStr.end()) {
            const std::string cellName = lhsStr.substr(0, indexIt - lhsStr.begin());

            size_t indexVal;
            try {
                indexVal = std::stoull(lhsStr.substr(indexIt - lhsStr.begin()));
            }
            catch (std::invalid_argument&) {
                return;
            }
            catch (std::out_of_range&) {
                return;
            }

            // get correspong fileTree_ element
            std::string cellStr;
            try {
                BinOp lhsCell = static_cast<BinOp>(*fileTree_.GetCell(indexVal, cellName));
                processCell(lhsCell);
                cellStr = lhsCell.ToString();
            }
            catch (BinOpConstructionErr&) {
                const auto lhsCell = fileTree_.GetCell(indexVal, cellName);
                cellStr = lhsCell->ToString();
            }

            // get lhs value from cellStr
            int cellVal;
            try {
                cellVal = std::stoi(cellStr);
            }
            catch (std::invalid_argument&) {
                return;
            }
            catch (std::out_of_range&) {
                return;
            }

            // set lhs value into BinOp
            BinOp& cellOp = static_cast<BinOp&>(cell);
            cellOp.SetLhs(cellVal);
        }
    }

    void CSVFile::processRhs(CellAbstract& cell) {
        const std::string& strData = cell.StrData();
        const size_t signPos = strData.find_first_of(POSSIBLE_SIGNS, 1);
        std::string rhsStr = strData.substr(signPos + 1);

        // extract cellName and indexVal from lhsStr
        const std::string::iterator indexIt = std::find_if(rhsStr.begin(), rhsStr.end(), isdigit);
        if (indexIt != rhsStr.end()) {
            const std::string cellName = rhsStr.substr(0, indexIt - rhsStr.begin());
            size_t indexVal;
            try {
                indexVal = std::stoull(rhsStr.substr(indexIt - rhsStr.begin()));
            }
            catch (std::invalid_argument&) {
                return;
            }
            catch (std::out_of_range&) {
                return;
            }

            // get fileTree_[] 
            std::string cellStr;
            try {
                BinOp rhsCell = static_cast<BinOp>(*fileTree_.GetCell(indexVal, cellName));
                processCell(rhsCell);
                cellStr = rhsCell.ToString();
            }
            catch (...) {
                const auto rhsCell = fileTree_.GetCell(indexVal, cellName);
                cellStr = rhsCell->ToString();
            }
            int cellVal;
            try {
                cellVal = std::stoi(cellStr);
            }
            catch (std::invalid_argument&) {
                return;
            }
            catch (std::out_of_range&) {
                return;
            }
            BinOp& cellOp = static_cast<BinOp&>(cell);
            cellOp.SetRhs(cellVal);
        }
    }

    void CSVFile::processCell(CellAbstract& cell) {
        try {
            cell.Evaluate();
        }
        catch (BinOpLhsErr&) {
            processLhs(cell);
            cell.Evaluate();
        }
        catch (BinOpRhsErr&) {
            processRhs(cell);
            cell.Evaluate();
        }
        catch (BinOpSubstitutionErr&) {
            processLhs(cell);
            processRhs(cell);
            cell.Evaluate();
        }
    }

    CSVFile::CSVFile(const fs::path& inputFile, std::ostream& stream) {
        // prepare Input file
        iFile_ = validateAndCreateIFile(inputFile);

        // get header
        std::string headerStr;
        std::getline(iFile_, headerStr);
        processHeader(headerStr);

        // file iteration
        while (iFile_.good()) {
            // parsing row
            std::string rowStr;
            std::getline(iFile_, rowStr);
            std::erase_if(rowStr, isspace);
            if (rowStr.empty()) {
                continue;
            }
            parseRow(rowStr);
        }

        // BinOp evaluation
        stream << headerStr << std::endl;
        for (auto& it : fileTree_) {
            // WIN32 std::execution::par implementation doesn't require tbb
            // @todo add dependency to tbb in the cmake
#ifdef _WIN32
            std::for_each(std::execution::par, it.begin(), it.end(), [this](std::unique_ptr<Cell>& c) {
                processCell(*c);
            });
#else
            std::for_each(it.begin(), it.end(), [this](std::unique_ptr<Cell>& c) {
                processCell(*c);
        });
#endif
            stream << it.ToString() << std::endl;
        }
    }
    
}  // namespace csv
