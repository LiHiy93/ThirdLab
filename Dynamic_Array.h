#pragma once

#include "Sequence.h"

template <class T>
class DynamicArray : public Sequence<T>
{
private:
    T* elements_;
    int count_;

    void ResizeCapacity(int newSize)
    {
        T* newBlock = new T[newSize];
        int limit = (newSize < count_) ? newSize : count_;

        for (int i = 0; i < limit; ++i)
            newBlock[i] = elements_[i];

        delete[] elements_;
        elements_ = newBlock;
        count_ = newSize;
    }

public:
    // Вложенный класс-итератор
    class DynamicArrayIterator : public Sequence<T>::Iterator
    {
    private:
        T* current_;
    public:
        explicit DynamicArrayIterator(T* pointer) : current_(pointer) {}

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            auto casted = dynamic_cast<const DynamicArrayIterator*>(&other);
            return (casted && current_ == casted->current_);
        }
        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }
        T& operator*() override
        {
            return *current_;
        }
        typename Sequence<T>::Iterator& operator++() override
        {
            current_++;
            return *this;
        }
    };

    // Итераторы начала и конца
    typename Sequence<T>::Iterator* ToBegin() override
    {
        return new DynamicArrayIterator(elements_);
    }
    typename Sequence<T>::Iterator* ToEnd() override
    {
        return new DynamicArrayIterator(elements_ + count_);
    }

    // Конструкторы
    DynamicArray(T* items, int size)
    {
        count_ = size;
        elements_ = new T[size];
        for (int i = 0; i < size; ++i)
            Set(i, items[i]);
    }

    DynamicArray(T exampleValue, int size)
    {
        count_ = size;
        elements_ = new T[size];
        for (int i = 0; i < size; ++i)
            Set(i, exampleValue);
    }

    explicit DynamicArray(int size = 0)
    {
        count_ = size;
        elements_ = new T[size];
    }

    DynamicArray(const DynamicArray& other)
    {
        count_ = other.count_;
        elements_ = new T[count_];
        for (int i = 0; i < count_; ++i)
            elements_[i] = other.elements_[i];
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other) return *this;
        delete[] elements_;

        count_ = other.count_;
        elements_ = new T[count_];
        for (int i = 0; i < count_; ++i)
            elements_[i] = other.elements_[i];
        return *this;
    }

    ~DynamicArray()
    {
        delete[] elements_;
    }

    // Оператор[]
    T& operator[](int index)
    {
        return elements_[index];
    }
    T& operator[](int index) const
    {
        return elements_[index];
    }

    // Методы Sequence<T>
    T& GetFirstElement() override
    {
        return GetElement(0);
    }
    T& GetLastElement() override
    {
        return GetElement(count_ - 1);
    }
    T& GetElement(int index) override
    {
        return elements_[index];
    }
    void Swap(T& left, T& right) override
    {
        T temp = left;
        left = right;
        right = temp;
    }
    void Set(int index, T value) override
    {
        elements_[index] = value;
    }

    DynamicArray<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        int len;
        if (endIndex > count_)
            len = count_ - startIndex;
        else
            len = endIndex - startIndex + 1 - (startIndex == 0 ? 1 : 0);

        T* tempItems = new T[len];
        for (int i = 0; i < len; i++)
            tempItems[i] = GetElement(startIndex + i);

        return new DynamicArray<T>(tempItems, len);
    }

    int GetLength() const override
    {
        return count_;
    }

    void Append(T data) override
    {
        InsertAt(data, count_);
    }
    void Append(T* data, int dataSize) override
    {
        int oldCount = count_;
        ResizeCapacity(count_ + dataSize);
        for (int i = oldCount; i < oldCount + dataSize; i++)
            Set(i, data[i - oldCount]);
    }
    void Prepend(T data) override
    {
        InsertAt(data, 0);
    }
    void InsertAt(T data, int index) override
    {
        ResizeCapacity(count_ + 1);
        for (int i = count_ - 1; i > index; i--)
            Set(i, GetElement(i - 1));
        Set(index, data);
    }

    void Union(Sequence<T>* other) override
    {
        for (int i = 0; i < other->GetLength(); i++)
            Append(other->GetElement(i));
    }
};
