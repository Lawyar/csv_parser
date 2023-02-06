#pragma once

#include <stdexcept>

namespace csv {
    struct InconsistentRowErr final : public std::runtime_error {
        InconsistentRowErr(size_t expectedWords, size_t countedWords);

        using std::runtime_error::runtime_error;
    };
}
