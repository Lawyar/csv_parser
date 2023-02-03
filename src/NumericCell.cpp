#include <NumericCell.hpp>

#include <compare>
#include <cmath>
#include <limits>

namespace csv {
    NumericCell::NumericCell(int CellVal) noexcept : cellVal_(CellVal) { }

    int NumericCell::GetVal() const noexcept { return cellVal_; }
    void NumericCell::SetVal(int NewVal) noexcept { cellVal_ = NewVal; }

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
        return cellVal_ == static_cast<const NumericCell&>(rhs).cellVal_;
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
