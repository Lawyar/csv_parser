#pragma once

#include <BinOp.hpp>

namespace csv {
    template <typename Derived>
    struct BinOpCRTP : public BinOp {
        [[nodiscard]] std::unique_ptr<Cell> Clone() const override {
            return std::make_unique<Derived>(static_cast<const Derived&>(*this));
        }
    };
}
