#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->relation = r;
    this->capacity = 100;
    this->root = -1;
    this->firstFree = 0;
    this->mapSize = 0;
    this->elements = new TElem[this->capacity];
    this->left = new int[this->capacity];
    this->right = new int[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->left[i] = this->right[i] = -1;
    }
}

void SortedMultiMap::resize() {
    int newCapacity = this->capacity * 2;
    TElem* newElements = new TElem[newCapacity];
    int* newLeft = new int[newCapacity];
    int* newRight = new int[newCapacity];

    for (int i = 0; i < this->capacity; i++) {
        newElements[i] = this->elements[i];
        newLeft[i] = this->left[i];
        newRight[i] = this->right[i];
    }
    for (int i = this->capacity; i < newCapacity; i++) {
        newLeft[i] = newRight[i] = -1;
    }

    delete[] this->elements;
    delete[] this->left;
    delete[] this->right;

    this->elements = newElements;
    this->left = newLeft;
    this->right = newRight;
    this->capacity = newCapacity;
}

void SortedMultiMap::add(TKey c, TValue v) {
    if (this->firstFree >= this->capacity) {
        this->resize();
    }

    TElem elem = make_pair(c, v);
    if (this->root == -1) {
        this->root = this->firstFree;
        this->elements[this->root] = elem;
        this->firstFree++;
        this->mapSize++;
        return;
    }

    int current = this->root;
    int parent = -1;
    while (current != -1) {
        parent = current;
        if (this->relation(c, this->elements[current].first)) {
            current = this->left[current];
        } else {
            current = this->right[current];
        }
    }

    this->elements[this->firstFree] = elem;
    if (this->relation(c, this->elements[parent].first)) {
        this->left[parent] = this->firstFree;
    } else {
        this->right[parent] = this->firstFree;
    }
    this->firstFree++;
    this->mapSize++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> result;
    int current = this->root;
    while (current != -1) {
        if (this->elements[current].first == c) {
            result.push_back(this->elements[current].second);
        }
        if (this->relation(c, this->elements[current].first)) {
            current = this->left[current];
        } else {
            current = this->right[current];
        }
    }
    return result;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    int current = this->root;
    int parent = -1;
    while (current != -1 && (this->elements[current].first != c || this->elements[current].second != v)) {
        parent = current;
        if (this->relation(c, this->elements[current].first)) {
            current = this->left[current];
        } else {
            current = this->right[current];
        }
    }
    if (current == -1) {
        return false;
    }

    if (this->left[current] == -1 || this->right[current] == -1) {
        int child = (this->left[current] != -1) ? this->left[current] : this->right[current];
        if (parent == -1) {
            this->root = child;
        } else if (this->relation(this->elements[current].first, this->elements[parent].first)) {
            this->left[parent] = child;
        } else {
            this->right[parent] = child;
        }
    } else {
        int successor = this->right[current];
        int successorParent = current;
        while (this->left[successor] != -1) {
            successorParent = successor;
            successor = this->left[successor];
        }
        this->elements[current] = this->elements[successor];
        if (successorParent != current) {
            this->left[successorParent] = this->right[successor];
        } else {
            this->right[successorParent] = this->right[successor];
        }
    }
    this->mapSize--;
    return true;
}

int SortedMultiMap::size() const {
    return this->mapSize;
}

bool SortedMultiMap::isEmpty() const {
    return this->mapSize == 0;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    delete[] this->elements;
    delete[] this->left;
    delete[] this->right;
}
