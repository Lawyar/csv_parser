#include <CSVFile.hpp>
#include <detail.hpp>

#include <fstream>
#include <set>

namespace {
    namespace fs = std::filesystem;
    using strsize_t = std::string::size_type;

    struct RowData {
        size_t index_;
        std::vector<std::string> data_;
    };

    // @todo put inside class because of rowLen invariant
    RowData parseRow(const std::string& row, strsize_t rowLen) {
        const strsize_t realLen = std::count(row.begin(), row.end(), ',');
        if (realLen != rowLen) {
            // @todo throw InconsistentFile(Identical row length)
        }

        size_t rowInd{};
        try {
            rowInd = std::stoll(row.substr(','));
        }
        catch (const std::invalid_argument& ex) {
            // @todo throw InconsistentFile(Row ind should be unsigned integer type)
        }
        catch (const std::out_of_range& ex) {
            // @todo throw InconsistentFile(Too big integer)
        }

        const std::vector<std::string> splittedRow =
            detail_::strSplit(row.substr(rowInd, row.length() - rowInd), ',', realLen);

        return RowData{ rowInd, splittedRow};
    }
}

namespace csv {

    CSVFile::CSVFile(const fs::path& inputFile, const fs::path& outFile) {
        // init file
        if (!(exists(inputFile) || is_regular_file(inputFile))) {
            throw std::runtime_error("invalid path");
        }
        std::ifstream file(inputFile);
        if (!file.good()) { // @todo overhead?
            throw std::runtime_error("invalid file");
        }

        std::ofstream ofile(outFile);

        // get header
        std::string header;
        file >> header;
        while (file.good()) {
            std::string val1, val2, val3;
            char delim;
            file >> val1;
            ofile << val1 << std::endl;
        }
    }

    CSVFile::CSVFile(const fs::path& filePath)
    : CSVFile(filePath, detail_::genDefaultOutName(filePath)) { }
}  // namespace csv
