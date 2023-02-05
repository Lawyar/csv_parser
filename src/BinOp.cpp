#include <BinOp.hpp>

#include <cassert>

using namespace std::string_literals;

namespace {
    // convert op into char
    char opTypeToChar(csv::OpType op) {
        switch (op) {
        case csv::OpType::ADD: {
            return '+';
        }
        case csv::OpType::SUB: {
            return '-';
        }
        case csv::OpType::MUL: {
            return '*';
        }
        case csv::OpType::DIV: {
            return '/';
        }
        }
    }

    // converts ch into OpType
    // throws exception if not possible
    csv::OpType charToOpType(char ch) {
        switch (ch) {
        case '+': {
            return csv::OpType::ADD;
        }
        case '-': {
            return csv::OpType::SUB;
        }
        case '*': {
            return csv::OpType::MUL;
        }
        case '/': {
            return csv::OpType::DIV;
        }
        default: {
            throw std::invalid_argument("Given char is not a BinOp");
        }
        }
    }

    // generates string "={lhs}{op}{rhs}"
    std::string genStringFromBinOp(int lhs, int rhs, csv::OpType op) {
        std::string res = '=' + std::to_string(lhs) + opTypeToChar(op) + std::to_string(rhs);
        return res;
    }

    // exception safe std::string to int conversion
    bool strToInt(const std::string& str, int& res) noexcept {
        try {
            res = std::stoi(str);
        }
        catch (std::invalid_argument&) {
            return false;
        }
        catch (std::out_of_range&) {
            return false;
        }

        return true;
    }

    // formats str for parcing simplification
    std::string formatString(const std::string& str) {
        
    }
    
}

namespace {
    constexpr char POSSIBLE_SIGNS[] = "+-*/";
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


    void BinOp::initSign() {
        signPosition_ = cellStr_.find_first_of(POSSIBLE_SIGNS, 1);
        if (signPosition_ == std::string::npos) {
            throw BinOpConstructionErr("Input string doesn't contain possible operation");
        }

        op_ = charToOpType(cellStr_[signPosition_]);
    }

    BinOp::BinOp(int lhs, int rhs, OpType op) noexcept
        : Cell(genStringFromBinOp(lhs, rhs, op)),
          lhs_(lhs), rhs_(rhs), op_(op),
          constrStatus_(ConstructionStatus::FULL_CONSTR) {
        // @todo overhead
        initSign();
    }

    BinOp::BinOp(const std::string& binOpStr)
        : Cell(binOpStr) {
        std::string strForm = cellStr_;
        strForm.erase(0, 1);  // removing '='
        std::erase_if(strForm, isspace);  // removing spaces 
        //assert(strForm.length() >= 3);

        initSign();

        bool lConstr = strToInt(cellStr_.substr(0, signPosition_), lhs_);
        bool rConstr = strToInt(cellStr_.substr(signPosition_ + 1), rhs_);

        if (lConstr && rConstr) {
            constrStatus_ = ConstructionStatus::FULL_CONSTR;
        }
        else if (lConstr) {
            constrStatus_ = ConstructionStatus::LHS_CONSTR;
        }
        else if (rConstr) {
            constrStatus_ = ConstructionStatus::RHS_CONSTR;
        }
        else {
            constrStatus_ = ConstructionStatus::UNCONSTRUCTED;
        }
    }

    int BinOp::GetExpressionResult() const {
        if (constrStatus_ != ConstructionStatus::FULL_CONSTR) {
            throw BinOpConstructionErr("BinOp should be constructed before evaluation.");
        }

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

    int BinOp::Evaluate() {
        const int res = GetExpressionResult();
        cellStr_ = std::to_string(res);

        return res;
    }

    void BinOp::SubstituteOpValues(int lhs, int rhs) {
        lhs_ = lhs;
        rhs_ = rhs;
        genStringFromBinOp(lhs_, rhs_, op_);

        constrStatus_ = ConstructionStatus::FULL_CONSTR;
    }

    bool BinOp::IsConstructed() const {
        return constrStatus_ == ConstructionStatus::FULL_CONSTR;
    }

    ConstructionStatus BinOp::Status() const {
        return constrStatus_;
    }

    int BinOp::Lhs() const {
        return lhs_;
    }

    int BinOp::Rhs() const {
        return rhs_;
    }

    OpType BinOp::Op() const {
        return op_;
    }

    void BinOp::SetLhs(int lhs) {
        lhs_ = lhs;
        if (constrStatus_ == ConstructionStatus::RHS_CONSTR) {
            constrStatus_ = ConstructionStatus::FULL_CONSTR;
        }
        else if (constrStatus_ == ConstructionStatus::UNCONSTRUCTED) {
            constrStatus_ = ConstructionStatus::LHS_CONSTR;
        }

        cellStr_.replace(cellStr_.begin(), cellStr_.begin() + signPosition_, std::to_string(lhs_));
    }

    void BinOp::SetRhs(int rhs) {
        rhs_ = rhs;
        if (constrStatus_ == ConstructionStatus::LHS_CONSTR) {
            constrStatus_ = ConstructionStatus::FULL_CONSTR;
        }
        else if (constrStatus_ == ConstructionStatus::UNCONSTRUCTED) {
            constrStatus_ = ConstructionStatus::RHS_CONSTR;
        }

        cellStr_.replace(cellStr_.begin() + signPosition_ + 1, cellStr_.end(), std::to_string(rhs_));
    }

    void BinOp::SetOp(OpType op) {
        op_ = op;
        cellStr_[signPosition_] = opTypeToChar(op_);
    }

}
