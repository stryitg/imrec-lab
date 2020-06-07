#include <cmath>

#include "symbol.hpp"

Symbol::Symbol(Img&& img, char symbol) noexcept
    : _img(std::move(img))
    , _symbol(symbol) {}
    
size_t Symbol::Compare(const ImgView& img_view) const noexcept {
    size_t diff = 0;
    for(size_t i = 0; i < _img.GetHight(); ++i) {
        for(size_t j = 0; j < _img.GetWidth(); ++j) {
            diff += std::abs(img_view(i, j) - _img(i, j)); 
        }
    }
    return diff;
}

size_t Symbol::GetHight() const noexcept {
    return _img.GetHight();
}

char Symbol::GetSymbol() const noexcept {
    return _symbol;
}
