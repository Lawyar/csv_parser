#include <NumericCell.hpp>

#include <compare>
#include <cmath>
#include <limits>

namespace csv {
    NumericCell::NumericCell(double CellVal) noexcept : cellVal_(CellVal) { }

    double NumericCell::GetVal() const noexcept { return cellVal_; }
    void NumericCell::SetVal(double NewVal) noexcept { cellVal_ = NewVal; }

    NumericCell& NumericCell::operator+=(const NumericCell& rhs) noexcept {
        cellVal_ += rhs.cellVal_;
        return *this;
    }

    NumericCell& NumericCell::operator-=(const NumericCell& rhs) noexcept {
        cellVal_ -= rhs.cellVal_;
        return *this;
    }

    NumericCell& NumericCell::operator*=(const NumericCell& rhs) noexcept {
        cellVal_ *= rhs.cellVal_;
        return *this;
    }

    NumericCell& NumericCell::operator/=(const NumericCell& rhs) noexcept {
        cellVal_ /= rhs.cellVal_;
        return *this;
    }

    bool NumericCell::IsEqual(const Cell& rhs) const {
        return fabs(cellVal_ - static_cast<const NumericCell&>(rhs).cellVal_)
               < std::numeric_limits<double>::epsilon();
    }

    NumericCell::operator double() const noexcept {
        return cellVal_;
    }

    auto NumericCell::operator<=>(const NumericCell& rhs) const {
        return cellVal_ <=> rhs.cellVal_;
    }

    NumericCell operator+(const NumericCell& lhs, const NumericCell& rhs) noexcept {
        NumericCell tmp = lhs;
        return tmp += rhs;
    }

    NumericCell operator-(const NumericCell& lhs, const NumericCell& rhs) noexcept {
        NumericCell tmp = lhs;
        return tmp -= rhs;
    }

    NumericCell operator*(const NumericCell& lhs, const NumericCell& rhs) noexcept {
        NumericCell tmp = lhs;
        return tmp *= rhs;
    }

    NumericCell operator/(const NumericCell& lhs, const NumericCell& rhs) noexcept {
        NumericCell tmp = lhs;
        return tmp /= rhs;
    }
}
