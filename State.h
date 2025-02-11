#pragma once

#include "Dynamic_Array.h"

struct State
{
    int totalValue;
    int totalWeight;
    int totalVolume;
    DynamicArray<bool> selectedItems;

    explicit State(int countOfItems)
        : totalValue(0), totalWeight(0), totalVolume(0),
        selectedItems(false, countOfItems) {}

    State& operator=(const State& other)
    {
        if (this == &other) return *this;

        totalValue = other.totalValue;
        totalWeight = other.totalWeight;
        totalVolume = other.totalVolume;
        selectedItems = other.selectedItems;

        return *this;
    }

    int GetLength() const
    {
        return selectedItems.GetLength();
    }
    bool Get(int i) const
    {
        return selectedItems[i];
    }
    void Set(int i, bool val)
    {
        selectedItems.Set(i, val);
    }
};
