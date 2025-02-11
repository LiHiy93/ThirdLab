#include <cassert>
#include <string>

#include "Alphabet_Index.h"
#include "Back_pack.h"
#include "Dynamic_Array.h"
#include "Hash_Table.h"
#include "Item.h"
#include "Sparse_Vector.h"
#include "State.h"
#include "Print.h"
#include "Tests.h"

namespace HashTableTests
{
    const std::string keyA = "alpha";
    const std::string keyB = "beta";
    const std::string keyC = "gamma";

    const int valA = 101;
    const int valB = 202;
    const int valC = 303;

    void SetUp(HashTable<std::string, int>& tbl)
    {
        tbl.Add(keyA, valA);
        tbl.Add(keyB, valB);
        tbl.Add(keyC, valC);
    }

    void AddElements()
    {
        HashTable<std::string, int> tbl;
        SetUp(tbl);
        assert(tbl.ContainsKey(keyA));
        assert(tbl.ContainsKey(keyB));
        assert(tbl.ContainsKey(keyC));
        auto optA = tbl.GetValue(keyA);
        auto optB = tbl.GetValue(keyB);
        auto optC = tbl.GetValue(keyC);
        assert(optA.has_value() && optA.value() == valA);
        assert(optB.has_value() && optB.value() == valB);
        assert(optC.has_value() && optC.value() == valC);
    }

    void UpdateValue()
    {
        HashTable<std::string, int> tbl;
        SetUp(tbl);
        int newVal = 999;
        tbl.Add(keyA, newVal);
        auto updatedOpt = tbl.GetValue(keyA);
        assert(updatedOpt.has_value() && updatedOpt.value() == newVal);
    }

    void ContainsKey()
    {
        HashTable<std::string, int> tbl;
        SetUp(tbl);
        assert(tbl.ContainsKey(keyB));
        assert(!tbl.ContainsKey("omega"));
    }

    void RemoveElement()
    {
        HashTable<std::string, int> tbl;
        SetUp(tbl);
        tbl.Remove(keyB);
        assert(!tbl.ContainsKey(keyB));
        assert(tbl.GetCount() == 2);
    }

    void ResizeUp()
    {
        HashTable<std::string, int> tbl;
        SetUp(tbl);
        for (int i = 0; i < 80; ++i)
        {
            std::string k = "key" + std::to_string(i);
            tbl.Add(k, i + 500);
        }
        assert(tbl.GetCount() == 83);
        assert(tbl.GetCapacity() > 20);
    }

    void IsEmpty()
    {
        HashTable<std::string, int> emptyTbl;
        assert(emptyTbl.IsEmpty());
        assert(emptyTbl.GetCount() == 0);
    }

    void ResizeDown()
    {
        HashTable<std::string, int> tbl;
        SetUp(tbl);
        for (int i = 0; i < 70; ++i)
        {
            std::string k = "test" + std::to_string(i);
            tbl.Add(k, 800 + i);
        }
        for (int i = 0; i < 70; ++i)
        {
            std::string k = "test" + std::to_string(i);
            tbl.Remove(k);
        }
        assert(tbl.GetCount() == 3);
        assert(tbl.GetCapacity() < 80);
    }

    void Collisions()
    {
        HashTable<int, int> tbl(4);
        tbl.Add(4, 1000);
        tbl.Add(8, 2000);
        auto resA = tbl.GetValue(4);
        auto resB = tbl.GetValue(8);
        assert(resA.has_value() && resA.value() == 1000);
        assert(resB.has_value() && resB.value() == 2000);
    }
}

namespace SparseVectorTests
{
    const int defaultVal = -1;
    const int valX = 10;
    const int valY = 20;
    const int valZ = 30;
    const int idxX = 5;
    const int idxY = 15;
    const int idxZ = 25;

    void SetUp(SparseVector<int>& vec)
    {
        vec.Add(idxX, valX);
        vec.Add(idxY, valY);
        vec.Add(idxZ, valZ);
    }

    void AddElements()
    {
        SparseVector<int> vec(defaultVal);
        SetUp(vec);
        assert(vec.ContainsKey(idxX));
        assert(vec.ContainsKey(idxY));
        assert(vec.ContainsKey(idxZ));
        auto optX = vec.GetValue(idxX);
        auto optY = vec.GetValue(idxY);
        auto optZ = vec.GetValue(idxZ);
        assert(optX.has_value() && optX.value() == valX);
        assert(optY.has_value() && optY.value() == valY);
        assert(optZ.has_value() && optZ.value() == valZ);
    }

    void UpdateValue()
    {
        SparseVector<int> vec(defaultVal);
        SetUp(vec);
        int newVal = 777;
        vec.SetValue(idxX, newVal);
        assert(vec.GetValue(idxX).value() == newVal);
        assert(vec.GetValue(idxY).value() == valY);
    }

    void RemoveElement()
    {
        SparseVector<int> vec(defaultVal);
        SetUp(vec);
        vec.Remove(idxY);
        assert(!vec.ContainsKey(idxY));
        assert(vec.GetCount() == 2);
    }

    void AddArray()
    {
        SparseVector<int> vec(defaultVal);
        int arr[] = { -1, 10, -1, -1, 20, -1, 30 };
        vec.Add(arr, 7);
        assert(vec.ContainsKey(1));
        assert(vec.ContainsKey(4));
        assert(vec.ContainsKey(6));
        assert(vec.GetValue(1).value() == 10);
        assert(vec.GetValue(4).value() == 20);
        assert(vec.GetValue(6).value() == 30);
    }

    void MemoryUsage()
    {
        SparseVector<int> vec(defaultVal);
        SetUp(vec);
        size_t memUsed = vec.MemoryUsage();
        size_t expected = vec.GetCount() * (sizeof(size_t) + sizeof(int));
        assert(memUsed == expected);
    }

    void DefaultValueBehavior()
    {
        SparseVector<int> vec(defaultVal);
        assert(vec.GetValue(100).value() == defaultVal);
        vec.SetValue(100, defaultVal);
        assert(!vec.ContainsKey(100));
    }

    void EmptyVector()
    {
        SparseVector<int> vec(defaultVal);
        assert(vec.GetCount() == 0);
    }
}

namespace BackPackTests
{
    void TestMemoKey()
    {
        std::string key = MemoKey(7, 60, 40);
        assert(key == "7_60_40");
    }

    void EmptyBackPack()
    {
        DynamicArray<Item> items;
        int maxW = 50;
        int maxV = 30;
        State result = Package(items, maxW, maxV);
        assert(result.totalValue == 0);
        assert(result.totalWeight == 0);
        assert(result.totalVolume == 0);
        for (int i = 0; i < result.GetLength(); ++i)
            assert(!result.selectedItems[i]);
    }

    void SingleItemFits()
    {
        DynamicArray<Item> items(1);
        items[0] = Item(12, 3, 9);
        int maxW = 50;
        int maxV = 30;
        State res = Package(items, maxW, maxV);
        assert(res.totalValue == 9);
        assert(res.totalWeight == 12);
        assert(res.totalVolume == 3);
        assert(res.selectedItems[0]);
    }

    void SingleItemDoesNotFit()
    {
        DynamicArray<Item> items(1);
        items[0] = Item(55, 35, 99);
        int maxW = 50;
        int maxV = 30;
        State res = Package(items, maxW, maxV);
        assert(res.totalValue == 0);
        assert(res.totalWeight == 0);
        assert(res.totalVolume == 0);
        assert(!res.selectedItems[0]);
    }

    void MultipleItems()
    {
        DynamicArray<Item> items(3);
        items[0] = Item(10, 5, 50);
        items[1] = Item(25, 10, 120);
        items[2] = Item(20, 15, 90);
        int maxW = 45;
        int maxV = 20;
        State res = Package(items, maxW, maxV);
        assert(res.totalValue == 170);
        assert(res.selectedItems[0]);
        assert(res.selectedItems[1]);
        assert(!res.selectedItems[2]);
    }

    void BackPackFullCapacity()
    {
        DynamicArray<Item> items(4);
        items[0] = Item(4, 4, 12);
        items[1] = Item(5, 3, 14);
        items[2] = Item(6, 2, 16);
        items[3] = Item(1, 1, 4);
        int maxW = 10;
        int maxV = 7;
        State res = Package(items, maxW, maxV);
        assert(res.totalValue == 28);
        assert(res.selectedItems[0]);
        assert(res.selectedItems[2]);
        assert(!res.selectedItems[1]);
        assert(!res.selectedItems[3]);
    }

    void Memoization()
    {
        DynamicArray<Item> items(3);
        items[0] = Item(3, 1, 25);
        items[1] = Item(4, 2, 40);
        items[2] = Item(5, 3, 60);
        int maxW = 9;
        int maxV = 4;
        HashTable<std::string, int> memo(50);
        State current(items.GetLength());
        State bestSolution(items.GetLength());
        int bestVal = 0;
        Explore(items, maxW, maxV, current, 0, bestSolution, bestVal, memo);
        assert(memo.GetCount() > 0);
        assert(bestVal == 85);
        assert(bestSolution.totalWeight == 8);
        assert(bestSolution.totalVolume == 4);
    }
}

namespace AlphabetIndexTests
{
    void EmptyText()
    {
        std::string text;
        HashTable<std::string, DynamicArray<int>> table;
        BuildAlphabetIndex(table, text, 50, true);
        assert(table.GetCount() == 0);
    }

    void SingleWordText()
    {
        std::string text = "morning";
        HashTable<std::string, DynamicArray<int>> table;
        BuildAlphabetIndex(table, text, 50, true);
        auto optionalPages = table.GetValue("morning");
        assert(optionalPages.has_value());
        auto& arr = optionalPages.value();
        assert(arr.GetLength() == 1);
        assert(arr[0] == 1);
    }

    void MultipleWords()
    {
        std::string text = "good day sunshine";
        HashTable<std::string, DynamicArray<int>> table;
        BuildAlphabetIndex(table, text, 100, true);
        auto optGood = table.GetValue("good");
        auto optDay = table.GetValue("day");
        auto optSun = table.GetValue("sunshine");
        assert(optGood.has_value());
        assert(optDay.has_value());
        assert(optSun.has_value());
        assert(optGood.value().GetLength() == 1);
        assert(optDay.value().GetLength() == 1);
        assert(optSun.value().GetLength() == 1);
    }

    void LongText()
    {
        std::string text = "hello hello hello world world hello";
        HashTable<std::string, DynamicArray<int>> table;
        BuildAlphabetIndex(table, text, 10, true);
        auto helloPages = table.GetValue("hello");
        assert(helloPages.has_value());
        auto& hp = helloPages.value();
        assert(hp.GetLength() >= 3);
    }

    void ByWordsAndByCharacters()
    {
        std::string text = "aaa bbb ccc";
        HashTable<std::string, DynamicArray<int>> tableWords;
        HashTable<std::string, DynamicArray<int>> tableChars;
        BuildAlphabetIndex(tableWords, text, 20, true);
        auto aOpt = tableWords.GetValue("aaa");
        assert(aOpt.has_value());
        BuildAlphabetIndex(tableChars, text, 20, false);
        auto bOpt = tableChars.GetValue("bbb");
        assert(bOpt.has_value());
        assert(bOpt.value().GetLength() == 1);
    }

    void Test()
    {
        std::string text = "cat cat dog dog dog cat cat dog";
        HashTable<std::string, DynamicArray<int>> table;
        BuildAlphabetIndex(table, text, 15, false);
        auto catOpt = table.GetValue("cat");
        assert(catOpt.has_value());
        auto& catArr = catOpt.value();
        assert(catArr.GetLength() == 4);
    }
}

void TestHashTable()
{
    using namespace HashTableTests;
    AddElements();
    UpdateValue();
    ContainsKey();
    RemoveElement();
    ResizeUp();
    IsEmpty();
    ResizeDown();
    Collisions();
}

void TestSparseVector()
{
    using namespace SparseVectorTests;
    AddElements();
    UpdateValue();
    RemoveElement();
    AddArray();
    MemoryUsage();
    DefaultValueBehavior();
    EmptyVector();
}

void TestBackPack()
{
    using namespace BackPackTests;
    TestMemoKey();
    EmptyBackPack();
    SingleItemFits();
    SingleItemDoesNotFit();
    MultipleItems();
    BackPackFullCapacity();
    Memoization();
}

void TestAlphabetIndex()
{
    using namespace AlphabetIndexTests;
    EmptyText();
    SingleWordText();
    MultipleWords();
    LongText();
    ByWordsAndByCharacters();
    Test();
}
