#include "vector.h"
#include <stdexcept>
#include <new>
#include <iostream>

namespace Utility
{
    Vector::Vector()
    {
        data_ = new int[1];
        capacity = 1;
        if(!data_)
        {
            throw std::bad_alloc();
        }
    }
    Vector::Vector(const int& n)
    {
        data_ = new int[n];
        if(!data_)
        {
            throw std::bad_alloc();
        }
        capacity = n;
    }
    Vector::~Vector()
    {
        if(data_)
        {
            delete[] data_;
        }
    }

    Vector::Vector(const Vector& other) : Vector(other.size())
    {
        for(int i = 0; i < other.size(); ++i)
        {
            insert(other[i]);
        }
    }

    Vector& Vector::insert(const int& n)
    {
        if(size_ >= capacity)
        {
            auto* tmp = new int[capacity *= 2];
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
}