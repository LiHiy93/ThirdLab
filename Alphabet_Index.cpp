#include <sstream>
#include <string>
#include "Alphabet_Index.h"

DynamicArray<std::string> SplitIntoWords(const std::string& textContent)
{
    std::istringstream iss(textContent);
    DynamicArray<std::string> result;
    std::string temp;

    while (iss >> temp)
        result.Append(temp);

    return result;
}

void BuildAlphabetIndex(
    HashTable<std::string, DynamicArray<int>>& wordPageMap,
    const std::string& inputText,
    int pageSize,
    bool isByWords
)
{
    auto wordsArray = SplitIntoWords(inputText);
    int currentPageNumber = 1;
    int usedOnThisPage = 0;

    for (int i = 0; i < wordsArray.GetLength(); ++i)
    {
        std::string w = wordsArray[i];
        int chunkLen = (isByWords ? 1 : static_cast<int>(w.size()));
        bool canFit = false;

        if (currentPageNumber == 1)
            canFit = (usedOnThisPage + chunkLen <= pageSize / 2);
        else if (currentPageNumber % 10 == 0)
            canFit = (usedOnThisPage + chunkLen <= (pageSize * 3 / 4));
        else
            canFit = (usedOnThisPage + chunkLen <= pageSize);

        if (canFit)
        {
            usedOnThisPage += (isByWords ? 1 : (static_cast<int>(w.size()) + 1));
        }
        else
        {
            currentPageNumber++;
            usedOnThisPage = (isByWords ? 1 : static_cast<int>(w.size()));
        }

        if (wordPageMap.ContainsKey(w))
        {
            auto pagesOpt = wordPageMap.GetValue(w);
            if (pagesOpt.has_value())
            {
                auto& pagesRef = pagesOpt.value();
                pagesRef.Append(currentPageNumber);
                wordPageMap.Add(w, pagesRef);
            }
        }
        else
        {
            DynamicArray<int> newPages;
            newPages.Append(currentPageNumber);
            wordPageMap.Add(w, newPages);
        }
    }
}
