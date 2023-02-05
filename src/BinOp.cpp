#include <BinOp.hpp>

#include <array>

using namespace std::string_literals;

namespace {
    std::string genStringFromBinOp(int lhs, int rhs, csv::OpType op) {
        std::string res = std::to_string(lhs);
        switch (op) {
        case csv::OpType::ADD : {
            res += '+';
            break;
        }
        case csv::OpType::SUB: {
            res += '-';
            break;
        }
        case csv::OpType::MUL: {
            res += '*';
            break;
        }
        case csv::OpType::DIV: {
            res += '/';
            break;
        }
        }
        res += std::to_string(rhs);

        return res;
    }
    
}

namespace csv {
    int BinOp::doAdd() const noexcept {
        return lhs_ + rhs_;
    }
    
    int BinOp::doSub() const noexcept {
        return lhs_ - rhs_;
    }

    int BinOp::doMul() const noexcept {
        return lhs_ * rhs_;
    }

    int BinOp::doDiv() const noexcept {
        return lhs_ / rhs_;
    }

    BinOp::BinOp(int lhs, int rhs, OpType op) noexcept
        : Cell(genStringFromBinOp(lhs, rhs, op)), lhs_(lhs), rhs_(rhs), op_(op) { }

    BinOp::BinOp(const std::string& binOpStr)
        : Cell(binOpStr) {
        const std::string possibleSign = "+-*/"s;
        const size_t signPos = cellStr_.find_first_of(possibleSign);
        if (signPos == std::string::npos) {
            throw BinOpConstructionErr("Input string doesn't contain possible operation");
        }

        lhs_ = std::stoi(cellStr_.substr(signPos));
        rhs_ = std::stoi(cellStr_.substr(signPos, cellStr_.length() - signPos));

        switch (cellStr_[signPos]) {
        case '+': {
            op_ = OpType::ADD;
            break;
        }
        case '-': {
            op_ = OpType::SUB;
            break;
        }
        case '*': {
            op_ = OpType::MUL;
            break;
        }
        default: {
            op_ = OpType::DIV;
            break;
        }
            
        }
    }

    int BinOp::Evaluate() const noexcept {
        switch (op_) {
        case OpType::ADD: {
            return doAdd();
        }
        case OpType::SUB: {
            return doSub();
        }
        case OpType::MUL: {
            return doMul();
        }
        default: {
            return doDiv();
        }
        }
    }
}
