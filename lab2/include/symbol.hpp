#pragma once

#include "img.hpp"

class Symbol {
public:
    Symbol() noexcept = default;
    Symbol(const Symbol&) noexcept = default;
    Symbol(Symbol&&) noexcept = default;
    
    Symbol(Img&& img, char symbol) noexcept;
    
    size_t Compare(const ImgView& img) const noexcept;
    
    size_t GetHight() const noexcept;
    char GetSymbol() const noexcept;
private:
    Img _img;
    char _symbol;
};