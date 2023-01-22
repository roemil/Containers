#pragma once
#include <algorithm>

namespace Utility
{
    class Vector
    {
        public:
            Vector();
            explicit Vector(const int& n);
            ~Vector();
            Vector(const Vector& other);
            
            Vector& insert(const int& n);
            const int size() const {return size_; };

            int operator[] (int index) const
            {
                return data_[index];
            }
            int operator==(const Vector& other) const
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
            int* data_;
            int size_ = 0;
            int capacity;
    };
}