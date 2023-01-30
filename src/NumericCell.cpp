#include <NumericCell.hpp>

#include <limits>
#include <typeinfo>

namespace csv {
    NumericCell::NumericCell(double CellVal) : cellVal_(CellVal) { }

    double NumericCell::GetVal() const { return cellVal_; }
    void NumericCell::SetVal(double NewVal) { cellVal_ = NewVal; }

    NumericCell& NumericCell::operator+=(const NumericCell& rhs) {
        cellVal_ += rhs.cellVal_;
        return *this;
    }

    NumericCell& NumericCell::operator-=(const NumericCell& rhs) {
        cellVal_ -= rhs.cellVal_;
        return *this;
    }

    NumericCell& NumericCell::operator*=(const NumericCell& rhs) {
        cellVal_ *= rhs.cellVal_;
        return *this;
    }

    NumericCell& NumericCell::operator/=(const NumericCell& rhs) {
        cellVal_ /= rhs.cellVal_;
        return *this;
    }

    bool NumericCell::IsEqual(const Cell& rhs) const {
        try {
            const auto& rhsObj = dynamic_cast<const NumericCell&>(rhs);
            return fabs(cellVal_ - rhsObj.cellVal_) < std::numeric_limits<double>::epsilon();
        }
        catch (std::bad_cast&) {
            return false;
        }
    }

    NumericCell* NumericCell::Clone() const {
        return new NumericCell{ *this };
    }

    auto NumericCell::operator<=>(const NumericCell& rhs) const {
        return cellVal_ <=> rhs.cellVal_;
    }

    NumericCell operator+(const NumericCell& rhs, const NumericCell& lhs) {
        NumericCell tmp = lhs;
        return tmp += lhs;
    }

    NumericCell operator-(const NumericCell& rhs, const NumericCell& lhs) {
        NumericCell tmp = lhs;
        return tmp -= lhs;
    }

    NumericCell operator*(const NumericCell& rhs, const NumericCell& lhs) {
        NumericCell tmp = lhs;
        return tmp *= lhs;
    }

    NumericCell operator/(const NumericCell& rhs, const NumericCell& lhs) {
        NumericCell tmp = lhs;
        return tmp /= lhs;
    }

}
