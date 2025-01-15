// atmega328p.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "flash_alloc.h"
#include <string>

int main()
{
    std::string name("a");
    int_allocation a = int_allocation(5, name);
    int_allocation b = int_allocation(5, name);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

