#include <CSVFile.hpp>
#include <detail.hpp>

#include <fstream>
#include <set>

namespace fs = std::filesystem;
using strsize_t = std::string::size_type;

namespace csv {
    CSVFile::RowData::RowData(const std::string& row, size_t wordsCount) {
        const strsize_t realLen = std::count(row.begin(), row.end(), ',');
        if (realLen != wordsCount) {
            // @todo throw InconsistentFile(Identical row length)
        }
        
        try {
            index_ = std::stoll(row.substr(','));
        }
        catch (const std::invalid_argument& ex) {
            // @todo throw InconsistentFile(Row ind should be unsigned integer type)
        }
        catch (const std::out_of_range& ex) {
            // @todo throw InconsistentFile(Too big integer)
        }

        data_ = detail_::strSplit(row.substr(index_, row.length() - index_), ',', realLen);
    }

    CSVFile::CSVFile(const fs::path& inputFile, const fs::path& outFile) {
        // init file
        if (!(exists(inputFile) || is_regular_file(inputFile))) {
            throw std::runtime_error("invalid path");
        }

        std::ifstream file(inputFile);
        // we need to check this because of the possible race condition or file inaccessibility
        // https://stackoverflow.com/questions/36022189/what-guarantee-do-i-have-after-is-regular-file
        if (!file.good()) {
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

    CSVFile::RowData CSVFile::parseRow(const std::string& row) const {
        return RowData(row, colNames_.size());
    }
    
}  // namespace csv
