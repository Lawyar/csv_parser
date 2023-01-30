#include <StrBinOp.hpp>
#include <StrCell.hpp>

namespace csv {
    StrBinOp::StrBinOp(const StrCell& lhs, const StrCell& rhs, StrOp_T opType)
        : lhs_(std::make_unique<StrCell>(lhs)),
        rhs_(std::make_unique<StrCell>(rhs)),
        opType_(opType)
    { }

    StrBinOp::StrBinOp(const StrBinOp& rhs)
        : lhs_(std::make_unique<StrCell>(*rhs.lhs_)),
        rhs_(std::make_unique<StrCell>(*rhs.rhs_)),
        opType_(rhs.opType_)
    { }

    StrCell StrBinOp::GetLhs() const noexcept {
        return *lhs_;
    }

    void StrBinOp::SetLhs(const StrCell& newLhs) {
        lhs_ = std::make_unique<StrCell>(newLhs);
    }

    StrCell StrBinOp::GetRhs() const noexcept {
        return *rhs_;
    }

    void StrBinOp::SetRhs(const StrCell& newRhs) {
        rhs_ = std::make_unique<StrCell>(newRhs);
    }

    StrOp_T StrBinOp::GetOpType() const noexcept {
        return opType_;
    }

    void StrBinOp::SetOpType(StrOp_T opType) noexcept {
        opType_ = opType;
    }

    std::unique_ptr<Cell> StrBinOp::Evaluate() const {
        switch (opType_) {
        case StrOp_T::ADD: {
            return std::make_unique<StrCell>(*lhs_ + *rhs_);
        }
        }
        return nullptr;
    }

    bool StrBinOp::IsEqual(const Cell& rhs) const {
        const StrBinOp& rhsVal = static_cast<const StrBinOp&>(rhs);
        return *lhs_ == *rhsVal.lhs_ && *rhs_ == *rhsVal.rhs_ && opType_ == rhsVal.opType_;
    }

    std::unique_ptr<Cell> StrBinOp::Clone() const {
        return std::make_unique<StrBinOp>(*this);
    }

}  // namespace csv
