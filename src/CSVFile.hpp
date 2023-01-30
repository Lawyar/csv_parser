#pragma once

#include <CSVTree.hpp>

#include <filesystem>

namespace csv {
    class CSVFile {
    private:
        //CSVTree fileTree_;

    public:
        CSVFile(const std::filesystem::path& filePath);

        //std::vector<std::string> GetHeader();
    };
}
