#pragma once

#include <iostream>
#include <string>
#include "State.h"
#include "Dynamic_Array.h"
#include "Hash_Table.h"

template <typename T>
void PrintValue(const T& val, std::ostream& os)
{
    os << val;
}

template <typename X>
void PrintValue(const DynamicArray<X>& arr, std::ostream& os)
{
    os << "[";
    for (int i = 0; i < arr.GetLength(); ++i)
    {
        PrintValue(arr[i], os);
        if (i < arr.GetLength() - 1) os << ", ";
    }
    os << "]";
}

template <typename K, typename V, typename H = std::hash<K>>
void PrintValue(const HashTable<K, V, H>& ht, std::ostream& os)
{
    for (int i = 0; i < ht.GetCapacity(); ++i)
    {
        if (ht.IndexContains(i))
        {
            PrintValue(ht.GetKeyByIndex(i), os);
            os << " : ";
            PrintValue(ht.GetValueByIndex(i), os);
            os << "\n";
        }
    }
}

template <typename>
void PrintSolution(const State& st, std::ostream& os)
{
    os << "Solution - Total Value: " << st.totalValue
        << ", Total Weight: " << st.totalWeight
        << ", Total Volume: " << st.totalVolume
        << ", Items: ";

    for (int i = 0; i < st.GetLength(); ++i)
    {
        if (st.selectedItems[i] == true)
            os << (i + 1) << " ";
    }
    os << "\n";
}
