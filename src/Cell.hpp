#pragma once

#include <CellAbstract.hpp>

namespace csv {
    template <typename Derived>
    class Cell : public CellAbstract {
        [[nodiscard]] std::unique_ptr<CellAbstract> Clone() const override {
            return std::make_unique<Derived>(static_cast<const Derived&>(*this));
        }
    };
}
