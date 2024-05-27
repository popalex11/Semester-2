#include "ValueIterator.h"
#include "SortedMultiMap.h"
#include <exception>
#include <vector>
using namespace std;

ValueIterator::ValueIterator(const SortedMultiMap& map, TKey k) : map(map), key(k) {
//    Initializes the iterator with a reference to the map and a key.

    vector<int> tempPositions;
    int current = map.root;
    while (current != -1) {
        if (map.elements[current].first == key) {
            tempPositions.push_back(current);
        }
        if (map.relation(key, map.elements[current].first)) {
            current = map.left[current];
        } else {
            current = map.right[current];
        }
    }
    this->size = tempPositions.size();
    this->positions = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        this->positions[i] = tempPositions[i];
    }
    this->currentIndex = 0;
    if (this->size == 0) {
        this->currentIndex = -1;
    }
}

void ValueIterator::first() {
    this->currentIndex = (this->size > 0) ? 0 : -1;
}

void ValueIterator::next() {
    if (!this->valid()) {
        throw exception();
    }
    this->currentIndex++;
    if (this->currentIndex >= this->size) {
        this->currentIndex = -1;
    }
}

bool ValueIterator::valid() const {
    return this->currentIndex != -1;
}

TValue ValueIterator::getCurrent() const {
    if (!this->valid()) {
        throw exception();
    }
    return map.elements[this->positions[this->currentIndex]].second;
}

ValueIterator::~ValueIterator() {
    delete[] this->positions;
}
