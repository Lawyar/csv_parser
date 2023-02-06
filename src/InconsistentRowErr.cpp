#include <InconsistentRowErr.hpp>

#include <string>

using namespace std::string_literals;

namespace {
    // @todo it is unsafe to use std::string with exceptions because std::string ctor can throw on allocation
    std::string generateMessage(size_t expectedWords, size_t countedWords) {
        std::string message = "InconsistentRowErr: expected rowLength = "s +
            std::to_string(expectedWords) + " , but counted = "s + std::to_string(countedWords);

        return message;
    }
}

namespace csv {
    // RowException
    InconsistentRowErr::InconsistentRowErr(size_t expectedWords, size_t countedWords)
        : runtime_error(generateMessage(expectedWords, countedWords)) { }
}
