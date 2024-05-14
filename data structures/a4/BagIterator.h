
#pragma once

#include "Bag.h"

class BagIterator {
private:
    const Bag& bag;
    int current_position;

public:
    BagIterator(const Bag& c);
    void first();
    void next();
    TElem getCurrent() const;
    bool valid() const;
};
