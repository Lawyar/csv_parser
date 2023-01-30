#pragma once

#include <Cell.hpp>

#include <string>

namespace csv {
    class StrCell final : public Cell {
    private:
        std::string cellVal_;
    public:
        StrCell(std::string&& cellVal);

        [[nodiscard]] std::string GetVal() const;
        void SetVal(std::string&& newVal);

        StrCell& operator+=(const StrCell& rhs);

        auto operator<=>(const StrCell& rhs) const;

        [[nodiscrad]] bool IsEqual(const Cell& rhs) const override;

        [[nodiscard]] StrCell* Clone() const override;

    };

    StrCell operator+(const StrCell& lhs, const StrCell& rhs);
}  // namespace csv
