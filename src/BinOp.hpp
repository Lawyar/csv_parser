#ifndef BINOP_HPP_
#define BINOP_HPP_

#include <Cell.hpp>

namespace csv {
    struct BinOp : public Cell {
        virtual Cell* Evaluate() = 0;
        virtual ~BinOp() { }
    };
}  // namespace csv

#endif  // BINOP_HPP_

