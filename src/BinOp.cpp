#include <BinOp.hpp> 

namespace csv {
    BinOp::BinOp(BinOp_T opType) noexcept : opType_(opType) { }

    void BinOp::SetOpType(BinOp_T opType) noexcept {
        opType_ = opType;
    }

    BinOp_T BinOp::GetOpType() const noexcept {
        return opType_;
    }
}  // namespace csv

