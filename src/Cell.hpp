#pragma once

#include <memory>

namespace csv {
    struct Cell {
        virtual ~Cell();

        [[nodiscard]] virtual bool IsEqual(const Cell& rhs) const = 0;

        [[nodiscard]] virtual std::unique_ptr<Cell> Clone() const = 0;
    };

    bool operator==(const Cell& lhs, const Cell& rhs);
    bool operator!=(const Cell& lhs, const Cell& rhs);

}  // namespace csv
