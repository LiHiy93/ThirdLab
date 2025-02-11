#pragma once

#include <utility>

template <typename X>
class ContainerForUniquePtr
{
private:
    X* buffer_;
    int capacity_;
    int size_;

    void ResizeStorage(int newCap)
    {
        X* tempBuffer = new X[newCap];
        for (int i = 0; i < size_; ++i)
            tempBuffer[i] = std::move(buffer_[i]);

        delete[] buffer_;
        buffer_ = tempBuffer;
        capacity_ = newCap;
    }

public:
    ContainerForUniquePtr() : buffer_(nullptr), capacity_(0), size_(0) {}
    explicit ContainerForUniquePtr(int cap) : buffer_(new X[cap]), capacity_(cap), size_(0) {}

    ~ContainerForUniquePtr()
    {
        delete[] buffer_;
    }

    ContainerForUniquePtr(ContainerForUniquePtr&& other) noexcept
        : buffer_(other.buffer_), capacity_(other.capacity_), size_(other.size_)
    {
        other.buffer_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    ContainerForUniquePtr& operator=(ContainerForUniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete[] buffer_;
            buffer_ = other.buffer_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.buffer_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    ContainerForUniquePtr(const ContainerForUniquePtr&) = delete;
    ContainerForUniquePtr& operator=(const ContainerForUniquePtr&) = delete;

    X& operator[](int index)
    {
        return buffer_[index];
    }
    const X& operator[](int index) const
    {
        return buffer_[index];
    }

    void PushBack(const X& val)
    {
        if (size_ >= capacity_)
        {
            int newCap = (capacity_ == 0) ? 2 : capacity_ * 2;
            ResizeStorage(newCap);
        }
        buffer_[size_++] = val;
    }

    int GetSize() const
    {
        return size_;
    }
    int GetCapacity() const
    {
        return capacity_;
    }

    X* GetData()
    {
        return buffer_;
    }
    const X* GetData() const
    {
        return buffer_;
    }
};
