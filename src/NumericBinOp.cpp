#include <NumericBinOp.hpp>
#include <NumericCell.hpp>

#include <memory>

namespace csv {
    NumericBinOp::NumericBinOp(const NumericCell& lhs,
                               const NumericCell& rhs,
                               NumericOp_T opType)
        : lhs_(std::make_unique<NumericCell>(lhs)),
          rhs_(std::make_unique<NumericCell>(rhs)),
          opType_(opType)
    { }

    NumericBinOp::NumericBinOp(const NumericBinOp & rhs)
        : lhs_(std::make_unique<NumericCell>(*rhs.lhs_)),
          rhs_(std::make_unique<NumericCell>(*rhs.rhs_)),
          opType_(rhs.opType_)
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

    NumericOp_T NumericBinOp::GetOpType() const noexcept {
        return opType_;
    }

    void NumericBinOp::SetOpType(NumericOp_T opType) noexcept {
        opType_ = opType;
    }

    std::unique_ptr<CellAbstract> NumericBinOp::Evaluate() const {
        switch (opType_) {
        case NumericOp_T::ADD: {
            return std::make_unique<NumericCell>(*lhs_ + *rhs_);
        }
        case NumericOp_T::SUB: {
            return std::make_unique<NumericCell>(*lhs_ - *rhs_);
        }
        case NumericOp_T::MUL: {
            return std::make_unique<NumericCell>(*lhs_ * *rhs_);
        }
        case NumericOp_T::DIV: {
            return std::make_unique<NumericCell>(*lhs_ / *rhs_);
        }
        }
        return nullptr;
    }

    bool NumericBinOp::IsEqual(const CellAbstract& rhs) const {
        const NumericBinOp& rhsVal = static_cast<const NumericBinOp&>(rhs);
        return *lhs_ == *rhsVal.lhs_ && *rhs_ == *rhsVal.rhs_ && opType_ == rhsVal.opType_;
    }

}  // namespace csv
