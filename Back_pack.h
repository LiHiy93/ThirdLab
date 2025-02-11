#pragma once

#include <string>
#include "Dynamic_Array.h"
#include "Hash_Table.h"
#include "Item.h"
#include "State.h"

std::string MemoKey(int idx, int weight, int volume);

void Explore(
    const DynamicArray<Item>& things,
    int maxW,
    int maxV,
    State curState,
    int index,
    State& bestState,
    int& bestVal,
    HashTable<std::string, int>& memoTable
);

State Package(const DynamicArray<Item>& items, int maxWeight, int maxVolume);
