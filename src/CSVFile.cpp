#include "CSVFile.hpp"

#include <exception>
#include <fstream>

namespace csv {
    CSVFile::CSVFile(const std::filesystem::path& filePath) {
        // init file
        if (!(exists(filePath) || is_regular_file(filePath))) {
            throw std::runtime_error("invalid path");
        }
        std::ifstream file(filePath);
        if (!file.good()) { // @todo overhead?
            throw std::runtime_error("invalid file");
        }

        // get header
        std::string header;
        std::getline()
        while (file.good()) {
            std::string val1, val2, val3;
            char delim;
            file >> val1;
            str.push_back(val1);
        }
    }
}  // namespace csv
