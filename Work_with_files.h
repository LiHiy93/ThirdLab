#pragma once

#include <string>
#include "Dynamic_Array.h"
#include "Hash_Table.h"
#include "Item.h"

void GenerateItemsToFile(const std::string& filename, int itemCount, int maxWeight, int maxVolume, int maxValue);
DynamicArray<Item> ReadItemsFromFile(const std::string& fileName);
std::string ReadTextFromFile(const std::string& fileName);
void WriteAlphabetIndexToFile(const std::string& fileName, const HashTable<std::string, DynamicArray<int>>& table);
