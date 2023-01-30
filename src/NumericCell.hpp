#pragma once

#include <CellCRTP.hpp>

namespace csv {
    class NumericCell final : public CellCRTP<NumericCell> {
    private:
        double cellVal_;
    public:
        NumericCell(double CellVal) noexcept;

        [[nodiscard]] double GetVal() const noexcept;
        void SetVal(double NewVal) noexcept;

        NumericCell& operator+=(const NumericCell& rhs) noexcept;
        NumericCell& operator-=(const NumericCell& rhs) noexcept;
        NumericCell& operator*=(const NumericCell& rhs) noexcept;
        NumericCell& operator/=(const NumericCell& rhs) noexcept;

        auto operator<=>(const NumericCell& rhs) const;

        [[nodiscrad]] bool IsEqual(const Cell& rhs) const override;

        operator double() const noexcept;

        ~NumericCell() {}
    };

    NumericCell operator+(const NumericCell& rhs, const NumericCell& lhs) noexcept;
    NumericCell operator-(const NumericCell& rhs, const NumericCell& lhs) noexcept;
    NumericCell operator*(const NumericCell& rhs, const NumericCell& lhs) noexcept;
    NumericCell operator/(const NumericCell& rhs, const NumericCell& lhs) noexcept;

}  // namespace csv
