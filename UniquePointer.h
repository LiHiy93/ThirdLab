#pragma once

template<typename U>
class UniquePtr
{
private:
    U* rawPtr_;
public:
    UniquePtr() : rawPtr_(nullptr) {}
    explicit UniquePtr(U* ptr) : rawPtr_(ptr) {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : rawPtr_(other.rawPtr_)
    {
        other.rawPtr_ = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete rawPtr_;
            rawPtr_ = other.rawPtr_;
            other.rawPtr_ = nullptr;
        }
        return *this;
    }

    U& operator*() const
    {
        return *rawPtr_;
    }
    U* operator->() const
    {
        return rawPtr_;
    }
    U* Get() const
    {
        return rawPtr_;
    }

    U* Release()
    {
        U* temp = rawPtr_;
        rawPtr_ = nullptr;
        return temp;
    }
    void Reset(U* newPtr = nullptr)
    {
        delete rawPtr_;
        rawPtr_ = newPtr;
    }

    ~UniquePtr()
    {
        delete rawPtr_;
    }
};
