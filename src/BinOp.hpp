#ifndef BINOP_HPP_
#define BINOP_HPP_

#include <CellCRTP.hpp>

#include <memory>

namespace csv {
    enum class BinOp_T {
        ADD = 1,
        SUB,
        MUL,
        DIV
    };

    class BinOp : public Cell {
    protected:
        BinOp_T opType_;
    public:
        BinOp(BinOp_T opType) noexcept;

        void SetOpType(BinOp_T opType) noexcept;
        [[nodiscard]] BinOp_T GetOpType() const noexcept;

        [[nodiscard]] virtual std::unique_ptr<Cell> Evaluate() const = 0;

        virtual ~BinOp() { }
    };
}  // namespace csv

#endif  // BINOP_HPP_

