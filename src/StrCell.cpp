#include <StrCell.hpp>

#include <typeinfo>

namespace csv {
    StrCell::StrCell(std::string&& cellVal) noexcept : cellVal_(std::move(cellVal)) { }

    StrCell::StrCell(const std::string& cellVal) : cellVal_(cellVal) { }

    StrCell::StrCell(const StrCell& rhs) : cellVal_(rhs.cellVal_) { }

    StrCell::StrCell(StrCell&& rhs) noexcept : cellVal_(std::move(rhs.cellVal_)) { }

    StrCell& StrCell::operator=(StrCell&& rhs) noexcept {
        cellVal_ = std::move(rhs.cellVal_);
        return *this;
    }

    StrCell& StrCell::operator=(const std::string& rhs) {
        cellVal_ = rhs;
        return *this;
    }

    StrCell& StrCell::operator=(const StrCell& rhs) {
        if (this->IsEqual(rhs)) {
            return *this;
        }
        cellVal_ = rhs.cellVal_;
        return *this;
    }

    bool StrCell::operator==(const std::string& str) const noexcept {
        return cellVal_ == str;
    }

    bool StrCell::operator==(const StrCell& rhs) const noexcept {
        return IsEqual(rhs);
    }

    std::string StrCell::GetVal() const { return cellVal_; }

    void StrCell::SetVal(std::string&& newVal) noexcept { cellVal_ = std::move(newVal); }

    bool StrCell::IsEqual(const CellAbstract& rhs) const {
        return cellVal_ == static_cast<const StrCell&>(rhs).cellVal_;
    }

}
