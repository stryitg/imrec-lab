#pragma once

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <cstring>

struct ResourceOwner;
struct NotResourceOwner;

template <typename RO>
class ImgContainer {
public:
    ImgContainer() noexcept;
    
    template <typename Dummy = void, 
              typename std::enable_if_t<std::is_same_v<RO, ResourceOwner>, Dummy>* = nullptr>
    ImgContainer(size_t hight, size_t width) noexcept
        : _data(new uint8_t [hight * width])
        , _hight(hight)
        , _width(width) {}

    template <typename Dummy = void,
              typename std::enable_if_t<!std::is_same_v<RO, ResourceOwner>, Dummy>* = nullptr>
    ImgContainer(uint8_t* data, size_t hight, size_t width) noexcept
        : _data(data)
        , _hight(hight)
        , _width(width) {}

    ImgContainer(ImgContainer&& rhs) noexcept;
    
    template <typename U_RO>
    ImgContainer(const ImgContainer<U_RO>& rhs) noexcept   
        : ImgContainer<RO>(rhs) {}
    
    ImgContainer(const ImgContainer& rhs) noexcept;
    
    ~ImgContainer();
    
    const uint8_t& operator()(size_t i, size_t j) const noexcept;
    uint8_t& operator()(size_t i, size_t j) noexcept;
        
    ImgContainer<NotResourceOwner> GetWindow(size_t begin_row, size_t hight) const noexcept;
        
    size_t GetHight() const noexcept;
    size_t GetWidth() const noexcept;
        
private:
    size_t ToIndex(size_t row, size_t col) const noexcept;

private:
    uint8_t* _data;
    size_t _hight;
    size_t _width;
};

using Img = ImgContainer<ResourceOwner>;
using ImgView = ImgContainer<NotResourceOwner>;

