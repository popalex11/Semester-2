#pragma once

#include "SortedMultiMap.h"

class SMMIterator {
    friend class SortedMultiMap;
private:
    const SortedMultiMap& map;
    int* stack;
    int stackSize;
    int currentNode;

public:
    SMMIterator(const SortedMultiMap& map);
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
    ~SMMIterator(); // Declare the destructor
};
