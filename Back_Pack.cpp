#include <sstream>
#include <string>
#include "Back_pack.h"

std::string MemoKey(int idx, int weight, int volume)
{
    std::ostringstream oss;
    oss << idx << "_" << weight << "_" << volume;
    return oss.str();
}

void Explore(
    const DynamicArray<Item>& things,
    int maxW,
    int maxV,
    State curState,
    int index,
    State& bestState,
    int& bestVal,
    HashTable<std::string, int>& memoTable
)
{
    if (index == things.GetLength())
    {
        if (curState.totalWeight <= maxW && curState.totalVolume <= maxV)
        {
            if (curState.totalValue > bestVal)
            {
                bestVal = curState.totalValue;
                bestState = curState;
            }
        }
        return;
    }

    auto keyStr = MemoKey(index, curState.totalWeight, curState.totalVolume);
    auto memoVal = memoTable.GetValue(keyStr);
    if (memoVal.has_value() && memoVal.value() >= curState.totalValue)
        return;

    memoTable.Add(keyStr, curState.totalValue);

    // Пропустить предмет
    Explore(things, maxW, maxV, curState, index + 1, bestState, bestVal, memoTable);

    // Взять предмет (если помещается)
    if (index < curState.GetLength() &&
        (curState.totalWeight + things[index].weight <= maxW) &&
        (curState.totalVolume + things[index].volume <= maxV))
    {
        curState.totalWeight += things[index].weight;
        curState.totalVolume += things[index].volume;
        curState.totalValue += things[index].value;
        curState.selectedItems[index] = true;

        Explore(things, maxW, maxV, curState, index + 1, bestState, bestVal, memoTable);
    }
}

State Package(const DynamicArray<Item>& items, int maxWeight, int maxVolume)
{
    State bestSolution(items.GetLength());
    int bestVal = 0;
    HashTable<std::string, int> memo(1000);

    Explore(items, maxWeight, maxVolume, State(items.GetLength()), 0, bestSolution, bestVal, memo);
    return bestSolution;
}
