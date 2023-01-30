#include <Cell.hpp>

#include <typeinfo>

namespace csv {
    Cell::~Cell() { }

    bool operator==(const Cell& lhs, const Cell& rhs) {
        return typeid(lhs) == typeid(rhs) && lhs.IsEqual(rhs);
    }

    bool operator!=(const Cell& lhs, const Cell& rhs) {
        return !(lhs == rhs);
    }

}
