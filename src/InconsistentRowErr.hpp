#pragma once

#include <stdexcept>

namespace csv {
    class InconsistentRowErr final : public std::runtime_error {
    private:
        size_t expectedWords_;
        size_t countedWords_;

    public:
        InconsistentRowErr(size_t expectedWords, size_t countedWords);
    };
}
