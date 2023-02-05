#ifndef BINOP_HPP_
#define BINOP_HPP_

#include <Cell.hpp>

#include <limits>
#include <stdexcept>

namespace csv {
    class BinOpConstructionErr : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    enum class OpType {
        ADD,
        SUB,
        MUL,
        DIV
    };

    enum class ConstructionStatus : char {
        UNCONSTRUCTED,
        LHS_CONSTR,
        RHS_CONSTR,
        FULL_CONSTR
    };

    // BinOp represents Binary Operation between two integers
    // Available operations: +; -; *; /
    class BinOp final : public Cell {
    private:
        int lhs_ = 0;
        int rhs_ = 0;
        OpType op_ = OpType::ADD;
        ConstructionStatus constrStatus_ = ConstructionStatus::UNCONSTRUCTED;

        // signPosition_ is undefined on integer construction
        size_t signPosition_ = 0;

        [[nodiscard]] int doAdd() const noexcept;
        [[nodiscard]] int doSub() const noexcept;
        [[nodiscard]] int doMul() const noexcept;
        [[nodiscard]] int doDiv() const noexcept;

        void initSign();

    public:
        BinOp(int lhs, int rhs, OpType op) noexcept;

        // Expected string with format "={Operand1} {OpType} {Operand2}"
        // Where {Operand1} and {Operand2} are integers or cell Values
        // Ex1: =32+85 ; Ex2: =A3+ 4 ; Ex3: =32+C7
        BinOp(const std::string& binOpStr);

        // simple returns operation result
        [[nodiscard]] int GetExpressionResult() const;

        // returns operation result and substitutes it into CellAbstract::cellStr_
        int Evaluate();

        void SubstituteOpValues(int lhs, int rhs);

        [[nodiscard]]  bool IsConstructed() const;

        [[nodiscard]] ConstructionStatus ConstructionStatus() const;

        [[nodiscard]] int Lhs() const;
        [[nodiscard]] int Rhs() const;
        [[nodiscard]] OpType Op() const;

        void SetLhs(int lhs);
        void SetRhs(int rhs);
        void SetOp(OpType op);
    };
}  // namespace csv

#endif  // BINOP_HPP_

