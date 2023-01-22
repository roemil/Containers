#pragma once
#include <algorithm>
#include <memory>

template<class T> class SmartVector
{
    public:
        SmartVector();
        explicit SmartVector(const int& n);
        ~SmartVector() = default;
        SmartVector(const SmartVector& other);
        SmartVector(SmartVector&& other);
        
        SmartVector& insert(const T& n);
        const int size() const {return size_; };
        std::unique_ptr<T[]> getData() {return std::move(data_);};

        int operator[] (int index) const
        {
            return data_[index];
        }
        int operator==(const SmartVector& other) const
        {
            if(size_ != other.size())
            {
                return false;
            }
            for(int i = 0; i < size_; ++i)
            {
                if(data_[i] != other[i])
                {
                    return false;
                }
            }
            return true;
        }

    SmartVector& operator=(SmartVector other)
    {
        for(int i = 0; i < other.size(); ++i)
        {
            insert(other[i]);
        }
        return *this;
    }

    private:
        std::unique_ptr<T[]> data_;
        int size_ = 0;
        int capacity;
};

template<class T>
SmartVector<T>::SmartVector()
{
    data_ = std::make_unique<int[]>(1);
    capacity = 1;
    if(!data_)
    {
        throw std::bad_alloc();
    }
}
template<class T>
SmartVector<T>::SmartVector(const int& n)
{
    data_ = std::make_unique<int[]>(n);
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
SmartVector<T>::SmartVector(SmartVector&& other) : SmartVector(other.size())
{
    data_ = std::move(other.getData());
}

template <class T>
SmartVector<T>& SmartVector<T>::insert(const T& n)
{
    if(size_ >= capacity)
    {
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(capacity *= 2);
        if(!tmp)
        {
            throw std::bad_alloc();
        }
        for(int i = 0; i < size_; ++i)
        {
            tmp[i] = data_[i];
        }
        tmp[size_++] = n;
        data_.reset();
        data_ = std::move(tmp);
    }
    else
    {
        data_[size_++] = n;
    }
    return *this;
}