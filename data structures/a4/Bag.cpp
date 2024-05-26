#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;

Bag::Bag() {
    capacity = 10; // Initial capacity
    elements = new TElem[capacity];
    frequencies = new int[capacity];
    next = new int[capacity];
    firstEmpty = 0;
    for (int i = 0; i < capacity; i++) {
        elements[i] = NULL_TELEM;
        frequencies[i] = 0;
        next[i] = i + 1;
    }
    next[capacity - 1] = -1; // End of the empty positions list
    sizeOfBag = 0;
}

int Bag::hash(TElem e) const {
    return abs(e) % capacity;
}

void Bag::add(TElem e) {
    if (sizeOfBag == capacity) {
        resize();
    }

    int pos = findPosition(e);
    if (pos != -1) {
        frequencies[pos]++;
    } else {
        int index = hash(e);
        if (elements[index] == NULL_TELEM) {
            elements[index] = e;
            frequencies[index] = 1;
            next[index] = -1;
        } else {
            int current = index;
            while (next[current] != -1) {
                current = next[current];
            }
            int empty = firstEmpty;
            firstEmpty = next[firstEmpty];
            next[current] = empty;
            elements[empty] = e;
            frequencies[empty] = 1;
            next[empty] = -1;
        }
        sizeOfBag++;
    }
}

bool Bag::remove(TElem e) {
    int pos = findPosition(e);
    if (pos == -1) {
        return false;
    }

    frequencies[pos]--;
    if (frequencies[pos] == 0) {
        elements[pos] = NULL_TELEM;
        next[pos] = firstEmpty;
        firstEmpty = pos;
        sizeOfBag--;
    }

    return true;
}

bool Bag::search(TElem e) const {
    return findPosition(e) != -1;
}

int Bag::nrOccurrences(TElem e) const {
    int pos = findPosition(e);
    return (pos == -1) ? 0 : frequencies[pos];
}

int Bag::size() const {
    return sizeOfBag;
}

bool Bag::isEmpty() const {
    return sizeOfBag == 0;
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

Bag::~Bag() {
    delete[] elements;
    delete[] frequencies;
    delete[] next;
}

int Bag::findPosition(TElem e) const {
    int index = hash(e);
    int current = index;
    while (current != -1) {
        if (elements[current] == e) {
            return current;
        }
        current = next[current];
    }
    return -1;
}

void Bag::resize() {
    int oldCapacity = capacity;
    capacity *= 2;
    TElem* oldElements = elements;
    int* oldFrequencies = frequencies;
    int* oldNext = next;

    elements = new TElem[capacity];
    frequencies = new int[capacity];
    next = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        elements[i] = NULL_TELEM;
        frequencies[i] = 0;
        next[i] = i + 1;
    }
    next[capacity - 1] = -1;
    firstEmpty = oldCapacity;
    sizeOfBag = 0;

    for (int i = 0; i < oldCapacity; i++) {
        if (oldElements[i] != NULL_TELEM) {
            for (int j = 0; j < oldFrequencies[i]; j++) {
                add(oldElements[i]);
            }
        }
    }

    delete[] oldElements;
    delete[] oldFrequencies;
    delete[] oldNext;
}
