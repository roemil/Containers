#pragma once
#include <iterator>
#include <initializer_list>
#include <algorithm>

template<typename T, std::size_t Size> struct Array
{
        T array_[Size];
        constexpr T* begin() {return array_;}
        constexpr T* end() {return array_+Size;}
        constexpr const T* begin() const {return array_;}
        constexpr const T* end() const {return array_+Size;}

        constexpr std::size_t size() noexcept {return Size;}
        constexpr auto maxSize() noexcept {return size();}
        constexpr const std::size_t size() const noexcept {return Size;}
        constexpr const std::size_t maxSize() const noexcept {return size();}
        constexpr T& operator[](const std::size_t ind) noexcept {return array_[ind];}
        constexpr const T& operator[](const std::size_t ind) const noexcept {return array_[ind];}
        constexpr Array<T, Size> operator=(const Array& rh)
        {
            T array_[Size] = rh.array_;
        }

        constexpr T& at(const std::size_t ind) noexcept {return array_[ind];}
        constexpr const T& at(const std::size_t ind) const noexcept {return array_[ind];}

        constexpr T& front() noexcept {return array_[0];}
        constexpr T& back() noexcept {return array_[Size - 1];}
        constexpr const T& front() const noexcept {return array_[0];}
        constexpr const T& back() const noexcept {return array_[Size - 1];}
        constexpr bool empty() const noexcept {return Size == 0;}

        constexpr T* data() noexcept {return array_;}
        constexpr const T* data()  const noexcept {return array_;}

        constexpr Array& swap(Array& rh) noexcept
        {
            std::swap(array_, rh.array_);
            return *this;
        }

        constexpr void fill(const T& value)
        {
            for(auto& elem : array_)
            {
                elem = value;
            }
        }

};

template<typename T, std::size_t Size>
constexpr void swap(Array<T, Size>& lh, Array<T, Size>& rh)
{
    std::swap(lh.array_, rh.array_);
}
template<typename T, std::size_t Size>
constexpr bool operator==(const Array<T, Size>& lh, const Array<T, Size>& rh)
{
    for(decltype(Size) i = 0; i < Size; ++i)
    {
        if(lh.array_[i] != rh.array_[i])
        {
            return false;
        }
    }
    return true;
}

template<typename T, std::size_t Size>
constexpr bool operator!=(const Array<T, Size>& lh, const Array<T, Size>& rh)
{
    return !(lh == rh);
}