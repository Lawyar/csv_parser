#pragma once

namespace csv {
    struct Cell {
        virtual ~Cell() { }

        virtual bool IsEqual(const Cell& rhs) const = 0;

        virtual Cell* Clone() const = 0;
    };

}  // namespace csv
