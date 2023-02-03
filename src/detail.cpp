#include <detail.hpp>

namespace detail_ {
    namespace fs = std::filesystem;
    using namespace std::string_literals;

    fs::path genDefaultOutName(const fs::path& fName,
                               const std::string& postfix,
                               const std::string& ext) {
        fs::path oPath = fName.parent_path();
        std::string oFilename = fName.filename().replace_extension().string();
        oFilename += postfix + '.' + ext;
        oPath /= oFilename;

        return oPath;
    }

    std::vector<std::string> strSplit(const std::string& str,
                                      size_t wordsCount,
                                      char delim) {
        std::vector<std::string> res;
        res.reserve(wordsCount);
        size_t last = 0; size_t next = 0;
        size_t it = 0;
        while ((next = str.find(delim, last)) != std::string::npos) {
            res.push_back(str.substr(last, next - last));
            last = next + 1;
            ++it;
        }
        res.push_back(str.substr(last));

        return res;
    }
}
