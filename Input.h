#pragma once

#include <iostream>
#include <string>

template<typename T>
void ReadVariable(T& varRef, const std::string& prompt)
{
    std::cout << prompt << "\n";
    std::cin >> varRef;
}
