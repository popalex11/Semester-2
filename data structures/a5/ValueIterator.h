#pragma once

#include "SortedMultiMap.h"

class ValueIterator {
    friend class SortedMultiMap;
private:
    const SortedMultiMap& map;
    TKey key;
    int* positions;
    int size;
    int currentIndex;

public:
    ValueIterator(const SortedMultiMap& map, TKey k);
    void first();
    void next();
    bool valid() const;
    TValue getCurrent() const;
    ~ValueIterator();
};
