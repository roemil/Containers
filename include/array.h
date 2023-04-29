#pragma once
#include <iterator>
#include <initializer_list>
#include <algorithm>

template<typename T, std::size_t Size> struct Array
{
        T array_[Size];
        constexpr T* begin() {return array_;}
        constexpr T* end() {return array_+Size;}
        constexpr T* cbegin() const {return array_;}
        constexpr T* cend() const {return array_+Size;}

        constexpr std::size_t size() noexcept {return Size;}
        constexpr T& operator[](const std::size_t ind) noexcept {return array_[ind];}

        constexpr T& at(const std::size_t ind) noexcept {return array_[ind];}
        constexpr T& at(const std::size_t ind) const noexcept {return array_[ind];}

        constexpr T& front() noexcept {return array_[0];}
        constexpr T& back() noexcept {return array_[Size - 1];}
        constexpr bool empty() const noexcept {return Size == 0;}

        constexpr T* data() noexcept {return array_;}

        constexpr Array& swap(Array& rh) noexcept
        {
            std::swap(array_, rh.array_);
            return *this;
        }

};
template<typename T, std::size_t Size>
constexpr void swap(Array<T, Size>& lh, Array<T, Size>& rh)
{
    std::swap(lh.array_, rh.array_);
}