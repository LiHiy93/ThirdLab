#pragma once

#include <iostream>
#include <optional>
#include "Dynamic_Array.h"
#include "Hash_Table.h"
#include "IDictionary.h"

template <typename ValT>
class SparseVector : public IDictionary<int, ValT>
{
private:
    HashTable<int, ValT> hashData_;
    ValT defaultVal_;

public:
    explicit SparseVector(ValT defVal = ValT()) : defaultVal_(defVal) {}

    void Add(const int& index, const ValT& value) override
    {
        SetValue(index, value);
    }

    void Add(const ValT* arr, int size)
    {
        for (int i = 0; i < size; ++i)
            if (arr[i] != defaultVal_)
                SetValue(i, arr[i]);
    }
    void Add(const DynamicArray<ValT>& arr)
    {
        for (int i = 0; i < arr.GetLength(); ++i)
            if (arr[i] != defaultVal_)
                SetValue(i, arr[i]);
    }

    void SetValue(int idx, ValT val)
    {
        if (val != defaultVal_)
            hashData_.Add(idx, val);
        else
            hashData_.Remove(idx);
    }

    // Реализация IDictionary
    std::optional<ValT> GetValue(const int& key) const override
    {
        auto res = hashData_.GetValue(key);
        if (res)
            return *res;
        return defaultVal_;
    }
    bool ContainsKey(const int& k) const override
    {
        return hashData_.ContainsKey(k);
    }
    void Remove(const int& k) override
    {
        hashData_.Remove(k);
    }
    int GetCount() const override
    {
        return hashData_.GetCount();
    }
    int GetCapacity() const override
    {
        return hashData_.GetCapacity();
    }

    size_t MemoryUsage() const
    {
        // Условная оценка
        return static_cast<size_t>(hashData_.GetCount()) * (sizeof(size_t) + sizeof(ValT));
    }
};
