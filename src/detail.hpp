#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace detail_ {
    using namespace std::string_literals;

    std::filesystem::path genDefaultOutName(const std::filesystem::path& fName,
                                            const std::string& postfix = "_out"s,
                                            const std::string& ext = "txt"s);

    std::vector<std::string> strSplit(const std::string& str,
                                      size_t wordsCount,
                                      char delim);
}
