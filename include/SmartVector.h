#pragma once
#include <algorithm>
#include <memory>

namespace Utility
{
    class SmartVector
    {
        public:
            SmartVector();
            explicit SmartVector(const int& n);
            ~SmartVector() = default;
            SmartVector(const SmartVector& other);
            
            SmartVector& insert(const int& n);
            const int size() const {return size_; };

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
            std::unique_ptr<int[]> data_;
            int size_ = 0;
            int capacity;
    };
}