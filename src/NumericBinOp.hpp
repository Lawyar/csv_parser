#pragma once

#include <BinOpCRTP.hpp>
#include <NumericCell.hpp>

#include <memory>

namespace csv {
    enum class NumericOp_T {
        ADD = 1,
        SUB,
        MUL,
        DIV
    };

    class NumericBinOp final : public BinOpCRTP<NumericBinOp> {
    private:
        std::unique_ptr<NumericCell> lhs_, rhs_;
        NumericOp_T opType_;

    public:
        NumericBinOp(const NumericCell& lhs, const NumericCell& rhs, NumericOp_T opType);
        NumericBinOp(const NumericBinOp& rhs);

        [[nodiscard]] NumericCell GetLhs() const noexcept;
        void SetLhs(const NumericCell& newLhs);

        [[nodiscard]] NumericCell GetRhs() const noexcept;
        void SetRhs(const NumericCell& newRhs);

        [[nodiscard]] NumericOp_T GetOpType() const noexcept;
        void SetOpType(NumericOp_T opType) noexcept;

        [[nodiscard]] std::unique_ptr<Cell> Evaluate() const override;

        [[nodiscard]] bool IsEqual(const Cell& rhs) const override;
    };
}

