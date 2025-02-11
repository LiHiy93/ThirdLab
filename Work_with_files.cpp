#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "Dynamic_Array.h"
#include "Hash_Table.h"
#include "Item.h"
#include "Print.h"
#include "State.h"

void GenerateItemsToFile(const std::string& filename, int itemCount, int maxWeight, int maxVolume, int maxValue)
{
    std::ofstream outfile(filename);
    if (!outfile)
    {
        std::cerr << "Error opening file for writing\n";
        return;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < itemCount; ++i)
    {
        int w = 1 + std::rand() % maxWeight;
        int v = 1 + std::rand() % maxVolume;
        int val = 1 + std::rand() % maxValue;
        outfile << w << " " << v << " " << val << "\n";
    }
    outfile.close();
}

DynamicArray<Item> ReadItemsFromFile(const std::string& fileName)
{
    std::ifstream infile(fileName);
    DynamicArray<Item> items;
    if (!infile)
    {
        std::cerr << "Error opening file for reading\n";
        return items;
    }

    int w, vol, val;
    while (infile >> w >> vol >> val)
        items.Append(Item(w, vol, val));

    infile.close();
    return items;
}

std::string ReadTextFromFile(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open())
    {
        std::cerr << "Error: Unable to open file " << fileName << "\n";
        return "";
    }

    std::string line;
    std::string accumulated;
    while (std::getline(fin, line))
        accumulated += line + "\n";

    fin.close();
    return accumulated;
}

void WriteAlphabetIndexToFile(const std::string& fileName, const HashTable<std::string, DynamicArray<int>>& table)
{
    std::ofstream ofs(fileName);
    if (!ofs.is_open())
    {
        std::cerr << "Error: Unable to open file " << fileName << "\n";
        return;
    }

    PrintValue(table, ofs);
    ofs.close();
}
