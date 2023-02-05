#include <CellAbstract.hpp>

#include <typeinfo>

using namespace std::string_literals;

namespace csv {
    CellAbstract::CellAbstract()
        : CellAbstract(" "s) { }

    CellAbstract::CellAbstract(const std::string& str) : cellStr_(str) {
        cellStr_ = cellStr_.empty() ? " "s : cellStr_;
    }

    CellAbstract::CellAbstract(std::string&& str) noexcept : cellStr_(std::move(str)) {
        cellStr_ = cellStr_.empty() ? " "s : cellStr_;
    }

    CellAbstract::CellAbstract(const CellAbstract& rhs) : CellAbstract(rhs.cellStr_) { }

    CellAbstract::CellAbstract(CellAbstract&& rhs) noexcept : CellAbstract(std::move(rhs.cellStr_)) { }

    bool CellAbstract::IsEqual(const CellAbstract& rhs) const {
        return cellStr_ == rhs.cellStr_;
    }

    std::string CellAbstract::ToString() const {
        return cellStr_;
    }

    std::string& CellAbstract::StrData() & {
        return cellStr_;
    }

    CellAbstract::operator std::string() const {
        return cellStr_;
    }

    CellAbstract& CellAbstract::operator=(const CellAbstract& rhs) {
        cellStr_ = rhs.cellStr_;

        return *this;
    }

    CellAbstract& CellAbstract::operator=(CellAbstract&& rhs) noexcept {
        cellStr_ = std::move(rhs.cellStr_);

        return *this;
    }

    CellAbstract& CellAbstract::operator=(const std::string& str) {
        cellStr_ = str;

        return *this;
    }

    CellAbstract& CellAbstract::operator=(std::string&& str) noexcept {
        cellStr_ = std::move(str);

        return *this;
    }

    bool operator==(const CellAbstract& lhs, const CellAbstract& rhs) {
        return typeid(lhs) == typeid(rhs) && lhs.IsEqual(rhs);
    }

    bool operator!=(const CellAbstract& lhs, const CellAbstract& rhs) {
        return !(lhs == rhs);
    }

}
