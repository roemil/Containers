#include "SmartVector.h"
#include <stdexcept>
#include <new>
#include <iostream>
#include <memory>

namespace Utility
{
    SmartVector::SmartVector()
    {
        data_ = std::make_unique<int[]>(1);
        capacity = 1;
        if(!data_)
        {
            throw std::bad_alloc();
        }
    }
    SmartVector::SmartVector(const int& n)
    {
        data_ = std::make_unique<int[]>(n);
        if(!data_)
        {
            throw std::bad_alloc();
        }
        capacity = n;
    }

    SmartVector::SmartVector(const SmartVector& other) : SmartVector(other.size())
    {
        for(int i = 0; i < other.size(); ++i)
        {
            insert(other[i]);
        }
    }

    SmartVector& SmartVector::insert(const int& n)
    {
        if(size_ >= capacity)
        {
            std::unique_ptr<int[]> tmp = std::make_unique<int[]>(capacity *= 2);
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
}