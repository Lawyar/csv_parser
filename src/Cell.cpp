#include <Cell.hpp>

#include <typeinfo>

namespace csv {
    Cell::~Cell() { }

    bool Cell::operator==(const Cell& rhs) const {
        return typeid(*this) == typeid(rhs) && IsEqual(rhs);
    }

    bool Cell::operator!=(const Cell& rhs) const {
        return !(*this == rhs);
    }

}
