#pragma once

#include <Cell.hpp>

#include <compare>

namespace csv {
    class NumericCell final : public Cell {
    private:
        double cellVal_;
    public:
        NumericCell(double CellVal);

        [[nodiscard]] double GetVal() const;
        void SetVal(double NewVal);

        NumericCell& operator+=(const NumericCell& rhs);
        NumericCell& operator-=(const NumericCell& rhs);
        NumericCell& operator*=(const NumericCell& rhs);
        NumericCell& operator/=(const NumericCell& rhs);

        auto operator<=>(const NumericCell& rhs) const;

        [[nodiscrad]] bool IsEqual(const Cell& rhs) const override;

        [[nodiscard]] NumericCell* Clone() const override;
    };

    NumericCell operator+(const NumericCell& rhs, const NumericCell& lhs);
    NumericCell operator-(const NumericCell& rhs, const NumericCell& lhs);
    NumericCell operator*(const NumericCell& rhs, const NumericCell& lhs);
    NumericCell operator/(const NumericCell& rhs, const NumericCell& lhs);

    bool operator==(const NumericCell& lhs, const NumericCell& rhs);
    bool operator!=(const NumericCell& lhs, const NumericCell& rhs);

}  // namespace csv
