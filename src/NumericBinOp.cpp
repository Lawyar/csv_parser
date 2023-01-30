#include <NumericBinOp.hpp>
#include <NumericCell.hpp>

namespace csv {
    NumericBinOp::NumericBinOp(const NumericCell& lhs, const NumericCell& rhs, BinOp_T opType)
        : BinOp(opType),
          lhs_(std::make_unique<NumericCell>(lhs)),
          rhs_(std::make_unique<NumericCell>(rhs))
    { }

    NumericBinOp::NumericBinOp(const NumericBinOp & rhs)
        : BinOp(rhs.opType_),
          lhs_(std::make_unique<NumericCell>(*rhs.lhs_)),
          rhs_(std::make_unique<NumericCell>(*rhs.rhs_))
    { }

    NumericCell NumericBinOp::GetLhs() const noexcept {
        return *lhs_;
    }

    void NumericBinOp::SetLhs(const NumericCell& newLhs) {
        lhs_ = std::make_unique<NumericCell>(newLhs);
    }

    NumericCell NumericBinOp::GetRhs() const noexcept {
        return *rhs_;
    }

    void NumericBinOp::SetRhs(const NumericCell& newRhs) {
        rhs_ = std::make_unique<NumericCell>(newRhs);
    }

    std::unique_ptr<Cell> NumericBinOp::Evaluate() const {
        switch (opType_) {
        case BinOp_T::ADD: {
            return std::make_unique<NumericCell>(*lhs_ + *rhs_);
        }
        case BinOp_T::SUB: {
            return std::make_unique<NumericCell>(*lhs_ - *rhs_);
        }
        case BinOp_T::MUL: {
            return std::make_unique<NumericCell>(*lhs_ * *rhs_);
        }
        case BinOp_T::DIV: {
            return std::make_unique<NumericCell>(*lhs_ / *rhs_);
        }
        }
        return nullptr;
    }

    bool NumericBinOp::IsEqual(const Cell& rhs) const {
        const NumericBinOp& rhsVal = static_cast<const NumericBinOp&>(rhs);
        return *lhs_ == *rhsVal.lhs_ && *rhs_ == *rhsVal.rhs_ && opType_ == rhsVal.opType_;
    }

    std::unique_ptr<Cell> NumericBinOp::Clone() const {
        return std::make_unique<NumericBinOp>(*this);
    }

}  // namespace csv
