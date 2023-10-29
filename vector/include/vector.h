#pragma once
#include <algorithm>
#include <initializer_list>

template<class T> class Vector
{
    public:
        Vector();
        explicit Vector(const int& n);
        explicit Vector(std::initializer_list<T> l ) : Vector(l.size())
        {
            for(auto elem : l)
            {
                insert(elem);
            }
        };
        ~Vector();
        Vector(const Vector& other);
        Vector(Vector&& rh);

        T* begin() {return data_;};
        T* end() {return data_+size_;};
        const T* begin() const {return data_;};
        const T* end() const {return data_+size_;};
        
        Vector<T>& insert(const T& n);
        const int size() const {return size_; };

        T operator[] (int index) const
        {
            return data_[index];
        }
        bool operator==(const Vector& other) const
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

    Vector& operator=(Vector other)
    {
        for(int i = 0; i < other.size(); ++i)
        {
            insert(other[i]);
        }
        return *this;
    }

    private:
        int size_{};
        int capacity{};
        T* data_{};
};

template<class T>
Vector<T>::Vector()
{
    data_ = (T*)new T[1];
    capacity = 1;
    if(!data_)
    {
        throw std::bad_alloc();
    }
}
template<class T>
Vector<T>::Vector(const int& n)
{
    data_ = (T*)new T[n];
    if(!data_)
    {
        throw std::bad_alloc();
    }
    capacity = n;
}

template <class T>
Vector<T>::Vector(Vector &&rh) {
    std::swap(this->data_, rh.data_);
    std::swap(this->size_, rh.size_);
    std::swap(this->capacity, rh.capacity);
};
template<class T>
Vector<T>::~Vector()
{
    if(data_)
    {
        for(int i = 0; i < size(); ++i)
        {
            data_[i].~T();
        }
        delete[] data_;
    }
}

template<class T>
Vector<T>::Vector(const Vector& other) : Vector(other.size())
{
    for(int i = 0; i < other.size(); ++i)
    {
        insert(other[i]);
    }
}

template<class T>
Vector<T>& Vector<T>::insert(const T& n)
{
    if(size_ >= capacity)
    {
        auto* tmp = new T[capacity *= 2];
        if(!tmp)
        {
            throw std::bad_alloc();
        }
        for(int i = 0; i < size_; ++i)
        {
            tmp[i] = data_[i];
        }
        tmp[size_++] = n;
        delete[] data_;
        data_ = tmp;
    }
    else
    {
        data_[size_++] = n;
    }
    return *this;
}