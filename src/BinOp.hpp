#ifndef BINOP_HPP_
#define BINOP_HPP_

#include <Cell.hpp>

#include <stdexcept>

namespace csv {
    enum class OpType {
        ADD,
        SUB,
        MUL,
        DIV
    };

    class BinOpConstructionErr : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class BinOp final : public Cell {
    private:
        int lhs_;
        int rhs_;
        OpType op_;

        [[nodiscard]] int doAdd() const noexcept;
        [[nodiscard]] int doSub() const noexcept;
        [[nodiscard]] int doMul() const noexcept;
        [[nodiscard]] int doDiv() const noexcept;

    public:
        BinOp(int lhs, int rhs, OpType op) noexcept;
        BinOp(const std::string& binOpStr);

        [[nodiscard]] int Evaluate() const noexcept;
    };
}  // namespace csv

#endif  // BINOP_HPP_

