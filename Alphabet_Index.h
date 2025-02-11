#pragma once

#include <string>
#include "Dynamic_Array.h"
#include "Hash_Table.h"

DynamicArray<std::string> SplitIntoWords(const std::string& textContent);

void BuildAlphabetIndex(
    HashTable<std::string, DynamicArray<int>>& wordPageMap,
    const std::string& inputText,
    int pageSize,
    bool isByWords
);
