#include <StrCell.hpp>

#include <typeinfo>

namespace csv {
    StrCell::StrCell(std::string&& cellVal) : cellVal_(std::move(cellVal)) { }

    StrCell& StrCell::operator+=(const StrCell& rhs) {
        cellVal_.append(rhs.cellVal_);
        return *this;
    }

    auto StrCell::operator<=>(const StrCell& rhs) const {
        return cellVal_ <=> rhs.cellVal_;
    }

    std::string StrCell::GetVal() const { return cellVal_; }

    void StrCell::SetVal(std::string&& newVal) { cellVal_ = std::move(newVal); }

    bool StrCell::IsEqual(const Cell& rhs) const {
        try {
            const auto& rhsObj = dynamic_cast<const StrCell&>(rhs);
            return cellVal_ == rhsObj.cellVal_;
        }
        catch (std::bad_cast&) {
            return false;
        }
    }

    StrCell operator+(const StrCell& lhs, const StrCell& rhs) {
        StrCell tmp = lhs;
        return tmp += rhs;
    }
}
