
#include "BagIterator.h"
#include "Bag.h"
#include <stdexcept>

BagIterator::BagIterator(const Bag& c) : bag(c) {
    current_position = 0;
    while (current_position < bag.capacity && !bag.elements[current_position].valid) {
        current_position++;
    }
}

void BagIterator::first() {
    current_position = 0;
    while (current_position < bag.capacity && !bag.elements[current_position].valid) {
        current_position++;
    }
}

void BagIterator::next() {
    if (!valid()) {
        throw std::runtime_error("Invalid iterator");
    }
    current_position++;
    while (current_position < bag.capacity && !bag.elements[current_position].valid) {
        current_position++;
    }
}

bool BagIterator::valid() const {
    return current_position < bag.capacity;
}

TElem BagIterator::getCurrent() const {
    if (!valid()) {
        throw std::runtime_error("Invalid iterator");
    }
    return bag.elements[current_position].value;
}
