#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>
using namespace std;

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->stack = new int[map.capacity];
    this->stackSize = 0;
    this->currentNode = -1;
    this->first();
}

void SMMIterator::first() {
    this->stackSize = 0;
    this->currentNode = map.root;
    while (this->currentNode != -1) {
        this->stack[this->stackSize++] = this->currentNode;
        this->currentNode = map.left[this->currentNode];
    }
    if (this->stackSize > 0) {
        this->currentNode = this->stack[--this->stackSize];
    } else {
        this->currentNode = -1;
    }
}

void SMMIterator::next() {
    if (!this->valid()) {
        throw exception();
    }
    int node = this->currentNode;
    if (map.right[node] != -1) {
        node = map.right[node];
        while (node != -1) {
            this->stack[this->stackSize++] = node;
            node = map.left[node];
        }
    }
    if (this->stackSize > 0) {
        this->currentNode = this->stack[--this->stackSize];
    } else {
        this->currentNode = -1;
    }
}

bool SMMIterator::valid() const {
    return this->currentNode != -1;
}

TElem SMMIterator::getCurrent() const {
    if (!this->valid()) {
        throw exception();
    }
    return map.elements[this->currentNode];
}

SMMIterator::~SMMIterator() {
    delete[] this->stack;
}
