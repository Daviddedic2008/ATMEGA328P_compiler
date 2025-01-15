#pragma once

#include "microcontroller_consts.h"
#include <string>
#include <list>

bool regsInUse[16];

struct memory_allocation {
    int startLocation;
    int size;
    int register_location = -1;
    std::string name;

    memory_allocation(){}

    memory_allocation(int start, int sz, std::string& nm);

    void free();

    // define the equality operator for the struct to be maybe used in remove
    bool operator==(const memory_allocation& other) const;

    void move_to_regs();

    void move_back_to_flash();
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

std::list<memory_allocation> allocations;