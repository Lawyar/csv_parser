#pragma once

#include <memory>

namespace csv {
    struct Cell {
        virtual ~Cell();

        // NVI
        bool operator==(const Cell& rhs) const;
        bool operator!=(const Cell& rhs) const;

        [[nodiscard]] virtual bool IsEqual(const Cell& rhs) const = 0;

        [[nodiscard]] virtual std::unique_ptr<Cell> Clone() const = 0;
    };

}  // namespace csv
