#pragma once

#include <CellCRTP.hpp>

namespace csv {
    class NumericCell final : public CellCRTP<NumericCell> {
    private:
        int cellVal_;
    public:
        NumericCell(int CellVal) noexcept;

        [[nodiscard]] int GetVal() const noexcept;
        void SetVal(int NewVal) noexcept;

        NumericCell& operator+=(const NumericCell& rhs) noexcept;
        NumericCell& operator-=(const NumericCell& rhs) noexcept;
        NumericCell& operator*=(const NumericCell& rhs) noexcept;
        NumericCell& operator/=(const NumericCell& rhs) noexcept;

        auto operator<=>(const NumericCell& rhs) const;

        [[nodiscrad]] bool IsEqual(const Cell& rhs) const override;

        operator double() const noexcept;

        ~NumericCell() {}
    };

    NumericCell operator+(const NumericCell& lhs, const NumericCell& rhs) noexcept;
    NumericCell operator-(const NumericCell& lhs, const NumericCell& rhs) noexcept;
    NumericCell operator*(const NumericCell& lhs, const NumericCell& rhs) noexcept;
    NumericCell operator/(const NumericCell& lhs, const NumericCell& rhs) noexcept;

}  // namespace csv
