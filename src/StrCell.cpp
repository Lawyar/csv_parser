#include <StrCell.hpp>

#include <typeinfo>

namespace csv {
    StrCell::StrCell(std::string&& cellVal) : cellVal_(std::move(cellVal)) { }

    StrCell::StrCell(const StrCell& rhs) : cellVal_(rhs.cellVal_) { }

    StrCell::StrCell(StrCell&& rhs) noexcept : cellVal_(std::move(rhs.cellVal_)) { }

    StrCell& StrCell::operator=(StrCell&& rhs) noexcept {
        cellVal_ = std::move(rhs.cellVal_);
        return *this;
    }

    StrCell& StrCell::operator=(const StrCell& rhs) {
        cellVal_ = rhs.cellVal_;
        return *this;
    }

    StrCell& StrCell::operator+=(const StrCell& rhs) {
        cellVal_.append(rhs.cellVal_);
        return *this;
    }

    std::string StrCell::GetVal() const { return cellVal_; }

    void StrCell::SetVal(std::string&& newVal) { cellVal_ = std::move(newVal); }

    bool StrCell::IsEqual(const Cell& rhs) const {
        return cellVal_ == static_cast<const StrCell&>(rhs).cellVal_;
    }

    StrCell operator+(const StrCell& lhs, const StrCell& rhs) {
        StrCell tmp = lhs;
        return tmp += rhs;
    }
}
