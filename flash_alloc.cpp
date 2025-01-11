#include "flash_alloc.h"
#include "asm_commands.h"

#include <list>
#include <string>
#include <iostream>

bool memInUse[FLASH_SIZE]; // keep track of what bytes are allocated

// list to keep track of all allocations
std::list<memory_allocation> allocations;

struct memory_allocation {
    int startLocation;
    int size;
    std::string name;

    memory_allocation() : startLocation(-1), size(-1) {} // default constructor, -1 to make it invalid

    memory_allocation(int start, int sz, std::string nm) : startLocation(start), size(sz), name(nm) {
        allocations.push_back(*this);
        for (int offset = 0; offset < size; offset++) {
            if (memInUse[startLocation + offset]) {
                allocations.pop_back();

                for (int offset_c = 0; offset_c < offset; offset_c++) {
                    memInUse[startLocation + offset_c] = false;
                }

                std::cerr << "allocating to used memory" << std::endl;
                break;
            }
            memInUse[startLocation + offset] = true;
        }
    }

    void free() {
        std::list<memory_allocation>::iterator it = std::find(allocations.begin(), allocations.end(), *this);
        if (it != allocations.end()) {
            allocations.erase(it);
            for (int m = startLocation; m < startLocation + size; m++) {
                memInUse[m] = false;
            }
        }
    }

    // define the equality operator for the struct to be maybe used in remove
    bool operator==(const memory_allocation& other) const {
        return (startLocation == other.startLocation) && (size == other.size) && (name == other.name);
    }
};

// function to get a valid start index for malloc
int get_valid_pos(int size) {
    int i = 0;
    int final = -1;
    for (; i < FLASH_SIZE; i++) {
        for (int o = 0; o < size; o++) {
            if (memInUse[i + o]) {
                goto skpbreak;
            }
        }
        final = i;
        break;
    skpbreak:;
    }
    return final;
}

struct int_allocation {
    memory_allocation alloc; // allocation in compiler
    int val;

    int_allocation(int v, std::string nm) : val(v), alloc(memory_allocation(get_valid_pos(4), 4, nm)) {
        for (int c = 0; c < 4; c++) {
            push(16);
            ldi(16, ((unsigned char*)&val)[c]);
            sts(alloc.startLocation + c, 16);
            pop(16);
        }
    }

    void free() {
        alloc.free();
    }
};

struct char_allocation {
    memory_allocation alloc; // allocation in compiler
    unsigned char val;

    char_allocation(unsigned char v, std::string nm) : val(v), alloc(memory_allocation(get_valid_pos(1), 1, nm)) {
        push(16);
        ldi(16, val);
        sts(alloc.startLocation, 16);
        pop(16);
    }

    void free() {
        alloc.free();
    }
};

struct general_allocation {
    memory_allocation alloc;
    unsigned char* val;

    // generalized for any struct T
    template <typename T>
    general_allocation(unsigned char* v, std::string nm) : alloc(memory_allocation(get_valid_pos(sizeof(T)), sizeof(T), nm)) {
        for (int i = 0; i < sizeof(T); i++) {
            val[i] = v[i];
            push(16);
            ldi(16, val[i]);
            sts(alloc.startLocation + i, 16);
            pop(16);
        }
    }

    void free() {
        alloc.free();
    }
};
