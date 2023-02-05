#pragma once

#include <CellCRTP.hpp>

namespace csv {
    class Cell : public CellCRTP<Cell> {
    public:
        Cell() : CellCRTP() { }
        Cell(const std::string& str) : CellCRTP(str) { }
        Cell(std::string&& str) : CellCRTP(std::move(str)) { }
    };
}
