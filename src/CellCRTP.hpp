#pragma once

#include <Cell.hpp>

namespace csv {
    template <typename Derived>
    struct CellCRTP : public Cell {
        [[nodiscard]] std::unique_ptr<Cell> Clone() const override {
            return std::make_unique<Derived>(static_cast<const Derived&>(*this));
        }
    };
}
