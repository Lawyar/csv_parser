#pragma once

#include <BinOp.hpp>
#include <NumericCell.hpp>

#include <memory>

namespace csv {
    class NumericBinOp final : public BinOp {
    private:
        std::unique_ptr<NumericCell> lhs_, rhs_;

    public:
        NumericBinOp(const NumericCell& lhs, const NumericCell& rhs, BinOp_T opType);
        NumericBinOp(const NumericBinOp& rhs);

        [[nodiscard]] NumericCell GetLhs() const noexcept;
        void SetLhs(const NumericCell& newLhs);

        [[nodiscard]] NumericCell GetRhs() const noexcept;
        void SetRhs(const NumericCell& newRhs);

        [[nodiscard]] std::unique_ptr<Cell> Evaluate() const override;

        [[nodiscard]] bool IsEqual(const Cell& rhs) const override;

        [[nodiscard]] std::unique_ptr<Cell> Clone() const override;

    };
}

