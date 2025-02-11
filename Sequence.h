#pragma once

template <class T>
class Sequence
{
public:
    virtual ~Sequence() = default;

    virtual T& GetFirstElement() = 0;
    virtual T& GetLastElement() = 0;
    virtual T& GetElement(int index) = 0;
    virtual void Swap(T& left, T& right) = 0;
    virtual void Set(int index, T value) = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
    virtual int GetLength() const = 0;
    virtual bool IsEmpty() const { return GetLength() == 0; }
    virtual void Append(T item) = 0;
    virtual void Append(T* data, int dataSize) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual void Union(Sequence<T>* other) = 0;

    class Iterator
    {
    public:
        virtual ~Iterator() = default;
        virtual bool operator==(const Iterator& other) const = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
        virtual T& operator*() = 0;
        virtual Iterator& operator++() = 0;
    };

    virtual Iterator* ToBegin() = 0;
    virtual Iterator* ToEnd() = 0;
};
