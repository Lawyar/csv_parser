#ifndef BINOP_HPP_
#define BINOP_HPP_

#include <Cell.hpp>

#include <memory>

namespace csv {
    struct BinOp : public Cell {
        [[nodiscard]] virtual std::unique_ptr<Cell> Evaluate() const = 0;

        virtual ~BinOp() { }
    };
}  // namespace csv

#endif  // BINOP_HPP_

