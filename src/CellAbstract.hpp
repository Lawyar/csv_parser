#pragma once

#include <string>
#include <memory>

namespace csv {
    class CellAbstract {
    private:
        std::string cellStr_;

    public:
        CellAbstract() = default;
        CellAbstract(const std::string& str);
        CellAbstract(std::string&& str) noexcept;
        CellAbstract(const CellAbstract& rhs);
        CellAbstract(CellAbstract&& rhs) noexcept;

        virtual ~CellAbstract() = default;

        [[nodiscard]] virtual bool IsEqual(const CellAbstract& rhs) const;

        [[nodiscard]] std::string ToString() const;

        [[nodiscard]] std::string& StrData() &;

        operator std::string() const;

        CellAbstract& operator=(const CellAbstract& rhs);
        CellAbstract& operator=(CellAbstract&& rhs) noexcept;

        CellAbstract& operator=(const std::string& str);
        CellAbstract& operator=(std::string&& str) noexcept;

        virtual std::unique_ptr<CellAbstract> Clone() const = 0;
    };

    bool operator==(const CellAbstract& lhs, const CellAbstract& rhs);
    bool operator!=(const CellAbstract& lhs, const CellAbstract& rhs);
}
