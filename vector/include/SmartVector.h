#pragma once
#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <iostream>

template<class T> class SmartVector
{
    public:
        using value_type = T;
        SmartVector();
        explicit SmartVector(const int& n);
        ~SmartVector();
        SmartVector(const SmartVector& other);
        SmartVector(SmartVector&& other) noexcept(std::is_nothrow_move_constructible_v<T>);

        explicit SmartVector(std::initializer_list<T> list ) noexcept(std::is_nothrow_constructible_v<T>)
            : SmartVector(list.size())
        {
            std::uninitialized_copy(list.begin(), list.end(), reinterpret_cast<T*>(&data_[0]));
            size_ = std::distance(list.begin(), list.end());
        };

        template <typename... ArgsT>
        T& emplace_back(ArgsT&& ...args)
        {
            emplace_back_helper(args...);
            return back();
        }

        T& front()
        {
            return getElem(0);
        }
        const T& front() const
        {
            return getElem(0);
        }
        T& back()
        {
            return getElem(size_-1);
        }
        const T& back() const
        {
            return getElem(size_-1);
        }

        SmartVector& insert(const T& n);
        const int size() const {return size_; };
        T* data()
        {
            return reinterpret_cast<T*>(data_);
        }
        const T* data() const
        {
            return reinterpret_cast<const T*>(data_.get());
        }

        const T& operator[] (int index) const noexcept
        {
            return *reinterpret_cast<const T*>(&data_[index]);
        }
        T& operator[] (int index) noexcept
        {
            return *reinterpret_cast<T*>(&data_[index]);
        }
        bool operator==(const SmartVector& other) const
        {
            if(size_ != other.size())
            {
                return false;
            }
            for(int i = 0; i < size_; ++i)
            {
                if(data()[i] != other[i])
                {
                    return false;
                }
            }
            return true;
        }

    SmartVector& operator=(const SmartVector& other)
    {
        for(int i = 0; i < other.size(); ++i)
        {
            insert(other[i]);
        }
        return *this;
    }

    private:
        using RawData = std::aligned_storage_t<sizeof(T), alignof(T)>;
        std::unique_ptr<RawData[]> data_;
        int size_ {};
        int capacity {};

        // Helper functions
        T& getElem(const int index);

        template <typename TypeT, typename... ArgsT>
        void emplace_back_helper(TypeT&& first, ArgsT&&... rest)
        {
            insert(std::forward<TypeT>(first));
            if constexpr (sizeof...(rest) > 0)
            {
                emplace_back_helper(rest...);
            }
        }
};

template<class T>
T& SmartVector<T>::getElem(const int index)
{
    return *reinterpret_cast<T*>(&data_[index]);
}

template<class T>
SmartVector<T>::~SmartVector()
{
    if(data_)
    {
        for(int i = 0; i < size(); ++i)
        {
            getElem(i).~T();
        }
    }
}

template<class T>
SmartVector<T>::SmartVector()
{
    data_ = std::make_unique<RawData[]>(1);
    capacity = 1;
    if(!data_)
    {
        throw std::bad_alloc();
    }
}
template<class T>
SmartVector<T>::SmartVector(const int& n)
{
    data_ = std::make_unique<RawData[]>(n);
    if(!data_)
    {
        throw std::bad_alloc();
    }
    capacity = n;
}

template<class T>
SmartVector<T>::SmartVector(const SmartVector& other) : SmartVector(other.size())
{
    for(int i = 0; i < other.size(); ++i)
    {
        insert(other[i]);
    }
}

template<class T>
SmartVector<T>::SmartVector(SmartVector&& other) noexcept(std::is_nothrow_move_constructible_v<T>)
{
    std::swap(size_, other.size_);
    std::swap(capacity, other.capacity);
    std::swap(data_, other.data_);
}

template <class T>
SmartVector<T>& SmartVector<T>::insert(const T& n)
{
    if(size_ >= capacity)
    {
        auto tmp = std::make_unique<RawData[]>(capacity *= 2);
        if(!tmp)
        {
            throw std::bad_alloc();
        }
        for(int i = 0; i < size_; ++i)
        {
            tmp[i] = std::move(data_[i]);
        }
        new(reinterpret_cast<T*>(&tmp[size_++])) T{n};
        data_.reset();
        data_ = std::move(tmp);
    }
    else
    {
        new(reinterpret_cast<T*>(&data_[size_++])) T{n};
    }
    return *this;
}