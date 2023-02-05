#pragma once

#include <Cell.hpp>

#include <string>

namespace csv {
    class StrCell final : public Cell<StrCell> {
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

        [[nodiscard]] bool IsEqual(const CellAbstract& rhs) const override;
    };
}  // namespace csv
