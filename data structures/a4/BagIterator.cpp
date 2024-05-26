#include "BagIterator.h"
#include "Bag.h"
#include <exception>

using namespace std;

BagIterator::BagIterator(const Bag& c) : bag(c), currentPos(0) {
    first();
}

void BagIterator::first() {
    currentPos = 0;
    while (currentPos < bag.capacity && bag.elements[currentPos] == NULL_TELEM) {
        currentPos++;
    }
}

void BagIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentPos++;
    while (currentPos < bag.capacity && bag.elements[currentPos] == NULL_TELEM) {
        currentPos++;
    }
}

bool BagIterator::valid() const {
    return currentPos < bag.capacity && bag.elements[currentPos] != NULL_TELEM;
}

TElem BagIterator::getCurrent() const {
    if (!valid()) {
        throw exception();
    }
    return bag.elements[currentPos];
}
