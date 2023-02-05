#pragma once

#include <BinOp.hpp>

namespace csv {
    template <typename Derived>
    struct BinOpCRTP : public BinOp {
        [[nodiscard]] std::unique_ptr<CellAbstract> Clone() const override {
            return std::make_unique<Derived>(static_cast<const Derived&>(*this));
        }
    };
}
