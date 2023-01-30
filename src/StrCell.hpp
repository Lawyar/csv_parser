#pragma once

#include <CellCRTP.hpp>

#include <string>

namespace csv {
    class StrCell final : public CellCRTP<StrCell> {
    private:
        std::string cellVal_;
    public:
        StrCell(std::string&& cellVal) noexcept;
        StrCell(const std::string& cellVal);
        StrCell(const StrCell& rhs);
        StrCell(StrCell&& rhs) noexcept;

        StrCell& operator=(StrCell&& rhs) noexcept;
        StrCell& operator=(const std::string& rhs);
        StrCell& operator=(const StrCell& rhs);

        bool operator==(const std::string& str) const noexcept;
        bool operator==(const StrCell& rhs) const noexcept;

        [[nodiscard]] std::string GetVal() const;
        void SetVal(std::string&& newVal) noexcept;

        StrCell& operator+=(const StrCell& rhs);

        [[nodiscard]] bool IsEqual(const Cell& rhs) const override;
    };

    StrCell operator+(const StrCell& lhs, const StrCell& rhs);
}  // namespace csv
