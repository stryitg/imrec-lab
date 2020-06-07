#include <cassert>

#include "img.hpp"

#ifdef DEBUG
    #define ASSERT(x) assert(x); 
#else
    #define ASSERT(x) void ();
#endif

template <typename RO>
ImgContainer<RO>::ImgContainer() noexcept
    : _data(nullptr) {}

template <typename RO>
ImgContainer<RO>::ImgContainer(ImgContainer<RO>&& rhs) noexcept
    : _data(rhs._data)
    , _hight(rhs._hight)
    , _width(rhs._width) {
    rhs._data = nullptr;
}

template <typename RO>
ImgContainer<RO>::ImgContainer(const ImgContainer<RO>& rhs) noexcept
    : _hight(rhs._hight)
    , _width(rhs._width) {
    if constexpr (std::is_same_v<RO, ResourceOwner>) {
        _data = new uint8_t [_hight * _width];
        memcpy(_data, rhs._data, _hight * _width);
    } else {
        _data = rhs._data;
    }
}

template <typename RO>
ImgContainer<RO>::~ImgContainer() {
    if constexpr (std::is_same_v<RO, ResourceOwner>)
        delete [] _data;;
}

template <typename RO>
const uint8_t& ImgContainer<RO>::operator()(size_t row, size_t col) const noexcept {
    ASSERT(row < _hight);
    ASSERT(col < _width);
    
    return _data[ToIndex(row, col)];
}

template <typename RO>
uint8_t& ImgContainer<RO>::operator()(size_t row, size_t col) noexcept {
    ASSERT(row < _hight);
    ASSERT(col < _width);
    
    return _data[ToIndex(row, col)];
}

template <typename RO>
ImgView ImgContainer<RO>::GetWindow(size_t begin_row, size_t hight) const noexcept {
    ASSERT(begin_row + hight <= _hight);
    
    const auto view_data = _data + ToIndex(begin_row, 0);
    return ImgView(view_data, hight, _width);
}

template <typename RO>
size_t ImgContainer<RO>::GetHight() const noexcept {
    return _hight;
}

template <typename RO>
size_t ImgContainer<RO>::GetWidth() const noexcept {
    return _width;
}


template <typename RO>
size_t ImgContainer<RO>::ToIndex(size_t row, size_t col) const noexcept {
    return (row * _width) + col;
};

template class ImgContainer<ResourceOwner>; 
template class ImgContainer<NotResourceOwner>;
