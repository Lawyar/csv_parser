#ifndef BINOP_HPP_
#define BINOP_HPP_

#include <CellAbstract.hpp>

#include <memory>

namespace csv {
    struct BinOp : public CellAbstract {
        [[nodiscard]] virtual std::unique_ptr<CellAbstract> Evaluate() const = 0;

        virtual ~BinOp() { }
    };
}  // namespace csv

#endif  // BINOP_HPP_

