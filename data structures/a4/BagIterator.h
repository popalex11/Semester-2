#include "Bag.h"

class BagIterator {
    friend class Bag;

private:
    const Bag& bag;
    int currentPos;

    BagIterator(const Bag& c);

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};
