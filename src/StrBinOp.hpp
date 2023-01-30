#pragma once

#include <BinOp.hpp>
#include <StrCell.hpp>

#include <memory>

namespace csv {
    enum class StrOp_T {
        ADD = 1
    };

    class StrBinOp final : public BinOp {
    private:
        std::unique_ptr<StrCell> lhs_, rhs_;
        StrOp_T opType_;

    public:
        StrBinOp(const StrCell& lhs, const StrCell& rhs, StrOp_T opType);
        StrBinOp(const StrBinOp& rhs);

        [[nodiscard]] StrCell GetLhs() const noexcept;
        void SetLhs(const StrCell& newLhs);

        [[nodiscard]] StrCell GetRhs() const noexcept;
        void SetRhs(const StrCell& newRhs);

        [[nodiscard]] StrOp_T GetOpType() const noexcept;
        void SetOpType(StrOp_T opType) noexcept;

        [[nodiscard]] std::unique_ptr<Cell> Evaluate() const override;

        [[nodiscard]] bool IsEqual(const Cell& rhs) const override;

        [[nodiscard]] std::unique_ptr<Cell> Clone() const override;
    };
}

