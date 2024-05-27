#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

void BagIterator::move() {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    while (currentElement < bag.m && (bag.elems[currentElement] == NULL_TELEM || bag.elems[currentElement] == DELETED))
        currentElement++;
}

BagIterator::BagIterator(const Bag &c) : bag(c) {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    currentElement = 0;
    move();
    currentFreq = 1;
}

void BagIterator::first() {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    currentElement = 0;
    move();
    currentFreq = 1;
}


void BagIterator::next() {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    if (currentFreq + 1 > bag.frequencies[currentElement]) {
        currentElement ++;
        move();
        currentFreq = 1;
    } else currentFreq++;
}


bool BagIterator::valid() const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    //TODO - Implementation
    return (currentElement < bag.m && currentFreq <= bag.frequencies[currentElement]);
}


TElem BagIterator::getCurrent() const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    //TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    return bag.elems[currentElement];
}
