#pragma once
#include "microcontroller_consts.h"
#include <string>

struct memory_allocation {
    int startLocation;
    int size;
    std::string name;

    memory_allocation(int start, int sz, std::string& nm);

    void free();

    // define the equality operator for the struct to be maybe used in remove
    bool operator==(const memory_allocation& other) const;
};

struct int_allocation {
    memory_allocation alloc; // allocation in compiler
    int val;

    int_allocation(int v, std::string nm);

    void free();
};

struct char_allocation {
    memory_allocation alloc; // allocation in compiler
    unsigned char val;

    char_allocation(unsigned char v, std::string nm);

    void free();
};

struct general_allocation {
    memory_allocation alloc;
    unsigned char* val;

    // generalized for any struct T
    template <typename T>
    general_allocation(unsigned char* v, std::string nm);

    void free();
};