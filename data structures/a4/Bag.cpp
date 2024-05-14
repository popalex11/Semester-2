// Bag.cpp

#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;

Bag::Bag() {
    capacity = INITIAL_CAPACITY;
    elements = new Node[capacity];
    size_of_bag = 0;
}

void Bag::add(TElem elem) {
    if (size_of_bag == capacity)
        resize();
    int index = hashFunction(elem, capacity);
    while (elements[index].valid && elements[index].value != elem) {
        index = (index + 1) % capacity;
    }
    if (!elements[index].valid) {
        elements[index].value = elem;
        elements[index].frequency = 1;
        elements[index].valid = true;
        size_of_bag++;
    } else {
        elements[index].frequency++;
    }
}

bool Bag::remove(TElem elem) {
    int index = hashFunction(elem, capacity);
    while (elements[index].valid && elements[index].value != elem) {
        index = (index + 1) % capacity;
    }
    if (elements[index].valid && elements[index].value == elem) {
        if (elements[index].frequency > 1) {
            elements[index].frequency--;
        } else {
            elements[index].valid = false;
            size_of_bag--;
        }
        return true;
    }
    return false;
}

bool Bag::search(TElem elem) const {
    int index = hashFunction(elem, capacity);
    while (elements[index].valid && elements[index].value != elem) {
        index = (index + 1) % capacity;
    }
    return elements[index].valid && elements[index].value == elem;
}

int Bag::nrOccurrences(TElem elem) const {
    int index = hashFunction(elem,capacity);
    while (elements[index].valid && elements[index].value != elem) {
        index = (index + 1) % capacity;
    }
    if (elements[index].valid && elements[index].value == elem) {
        return elements[index].frequency;
    }
    return 0;
}

int Bag::size() const {
    return size_of_bag;
}

bool Bag::isEmpty() const {
    return size_of_bag == 0;
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

Bag::~Bag() {
    delete[] elements;
}

void Bag::resize() {
    int new_capacity = capacity * 2;
    Node* new_elements = new Node[new_capacity];
    for (int i = 0; i < capacity; i++) {
        if (elements[i].valid) {
            int index = hashFunction(elements[i].value, new_capacity); 
            while (new_elements[index].valid) {
                index = (index + 1) % new_capacity;
            }
            new_elements[index] = elements[i];
        }
    }
    delete[] elements;
    elements = new_elements;
    capacity = new_capacity;
}


int Bag::hashFunction(TElem elem, int capacity) const {
    return std::hash<TElem>{}(elem) % capacity;
}

