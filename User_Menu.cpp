#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

#include "Alphabet_Index.h"
#include "Back_pack.h"
#include "Choice.h"
#include "Dynamic_Array.h"
#include "Work_with_files.h"
#include "Input.h"
#include "Item.h"
#include "Print.h"
#include "Sparse_Vector.h"
#include "Tests.h"

void OpenMenu()
{
    std::cout
        << "=== Добро пожаловать! Выберите команду ===\n"
        << "1) " << CMD_PACK_KNAPSACK << " - Решить задачу о рюкзаке\n"
        << "2) " << CMD_CREATE_FILE << " - Сгенерировать файл со списком предметов\n"
        << "3) " << CMD_SPARSE_VECTOR << " - Создать разреженный вектор\n"
        << "4) " << CMD_ALPHABET_INDEX << " - Построить \"алфавитный индекс\"\n"
        << "5) " << CMD_TEST_ALL << " - Запустить все тесты\n\n"
        << "Введите команду (или что-то иное, чтобы выйти):\n";

    bool keepLooping = true;

    while (keepLooping)
    {
        std::string userCmd;
        if (!std::getline(std::cin, userCmd))
        {
            std::cout << "Ввод прерван.\n";
            break;
        }
        while (!userCmd.empty() && std::isspace((unsigned char)userCmd.front()))
            userCmd.erase(userCmd.begin());
        while (!userCmd.empty() && std::isspace((unsigned char)userCmd.back()))
            userCmd.pop_back();
        if (userCmd.empty())
        {
            std::cout << "Пустая команда. Повторите ввод или введите любой непустой текст для выхода.\n";
            continue;
        }
        std::transform(userCmd.begin(), userCmd.end(), userCmd.begin(),
            [](unsigned char c) { return (unsigned char)std::tolower(c); });

        if (userCmd == CMD_PACK_KNAPSACK)
        {
            int maxWeight = 0;
            int maxVolume = 0;
            std::string itemsFile;
            ReadVariable(itemsFile, "Укажите название файла, где лежат предметы:");
            ReadVariable(maxWeight, "Какой максимальный вес рюкзака?");
            ReadVariable(maxVolume, "Какой максимальный объем рюкзака?");
            std::cout << "\nСейчас загрузим предметы из файла...\n";
            auto listOfItems = ReadItemsFromFile(itemsFile);
            if (listOfItems.GetLength() == 0)
            {
                std::cerr << "Файл пустой или не найден. Пропускаем.\n";
                continue;
            }
            std::cout << "Запускаем алгоритм поиска лучшего набора...\n";
            auto solution = Package(listOfItems, maxWeight, maxVolume);
            PrintSolution<void>(solution, std::cout);
        }
        else if (userCmd == CMD_CREATE_FILE)
        {
            int howMany = 0;
            int mWeight = 0;
            int mVolume = 0;
            int mValue = 0;
            std::string outName;
            ReadVariable(outName, "Введите имя нового файла:");
            ReadVariable(howMany, "Сколько предметов создать?");
            ReadVariable(mWeight, "Максимальный вес одного предмета?");
            ReadVariable(mVolume, "Максимальный объем одного предмета?");
            ReadVariable(mValue, "Максимальная ценность одного предмета?");
            std::cout << "\nГенерируем предметы...\n";
            GenerateItemsToFile(outName, howMany, mWeight, mVolume, mValue);
            std::cout << "Готово! Предметы записаны в \"" << outName << "\"\n";
        }
        else if (userCmd == CMD_SPARSE_VECTOR)
        {
            int count = 0;
            int nullPercent = 0;
            ReadVariable(count, "Сколько всего элементов будет в массиве?");
            ReadVariable(nullPercent, "Процент \"пустых\" (нулевых) элементов? (0..100)");
            if (nullPercent < 0) nullPercent = 0;
            if (nullPercent > 100) nullPercent = 100;
            SparseVector<Item> sparse;
            DynamicArray<Item> normalArr(count);
            std::cout << "\nЗаполняем обычный массив...\n";
            for (int i = 0; i < count; i++)
            {
                int chance = 1 + std::rand() % 100;
                if (chance <= nullPercent)
                    normalArr[i] = Item();
                else
                    normalArr[i] = Item(i + 1, i + 1, i + 1);
            }
            std::cout << "Создаем разреженный вектор...\n";
            sparse.Add(normalArr);
            size_t normalMem = sizeof(Item) * (size_t)count;
            size_t sparseMem = sparse.MemoryUsage();
            std::cout << "Память под обычный массив: " << normalMem << " байт\n";
            std::cout << "Память под разреженный вектор: " << sparseMem << " байт\n";
        }
        else if (userCmd == CMD_ALPHABET_INDEX)
        {
            std::string inFile;
            std::string outFile;
            int pgSize = 0;
            bool byWords = false;
            ReadVariable(inFile, "Введите файл с исходным текстом:");
            ReadVariable(outFile, "Куда сохранить результат?");
            ReadVariable(pgSize, "Какой условный размер \"страницы\"?");
            ReadVariable(byWords, "Считать по словам? (1 - да, 0 - нет):");
            auto textData = ReadTextFromFile(inFile);
            if (textData.empty())
            {
                std::cerr << "Файл пуст или не найден.\n";
                continue;
            }
            HashTable<std::string, DynamicArray<int>> indexTable;
            std::cout << "\nПостроение индекса...\n";
            BuildAlphabetIndex(indexTable, textData, pgSize, byWords);
            WriteAlphabetIndexToFile(outFile, indexTable);
            std::cout << "Алфавитный индекс сохранен в \"" << outFile << "\"\n";
        }
        else if (userCmd == CMD_TEST_ALL)
        {
            std::cout << "\n=== Тестируем HashTable ===\n";
            TestHashTable();
            std::cout << "Хеш-таблица: тесты пройдены.\n\n";
            std::cout << "=== Тестируем SparseVector ===\n";
            TestSparseVector();
            std::cout << "Разреженный вектор: тесты пройдены.\n\n";
            std::cout << "=== Тестируем Backpack ===\n";
            TestBackPack();
            std::cout << "Рюкзак: тесты пройдены.\n\n";
            std::cout << "=== Тестируем AlphabetIndex ===\n";
            TestAlphabetIndex();
            std::cout << "Алфавитный индекс: тесты пройдены.\n\n";
        }
        else
        {
            std::cout << "Неизвестная команда или выход.\n";
            keepLooping = false;
        }
        if (keepLooping)
        {
            std::cout << "\nВведите следующую команду (или пустую строку/EOF для выхода):\n";
        }
    }
    std::cout << "Программа завершена.\n";
}
