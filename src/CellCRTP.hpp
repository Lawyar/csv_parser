#pragma once

#include <CellAbstract.hpp>

namespace csv {
    template <typename Derived>
    struct CellCRTP : public CellAbstract {
        CellCRTP() : CellAbstract() {}
        CellCRTP(const std::string& str) : CellAbstract(str) { }
        CellCRTP(std::string&& str) : CellAbstract(std::move(str)) { }

        [[nodiscard]] std::unique_ptr<CellAbstract> Clone() const override {
            return std::make_unique<Derived>(static_cast<const Derived&>(*this));
        }
    };
}
