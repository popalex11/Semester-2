#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

KeyNode *MultiMap::checkKey(TKey key) const {
    KeyNode *current = this->head;
    KeyNode *sol = nullptr;

    while (current != nullptr) {
        if (current->info == key) {
            sol = current;
            return sol;
        }
        current = current->next;
    }

    return sol;
}

void MultiMap::addNewKey(TKey k) {
    auto *node = new KeyNode;

    node->info = k;
    node->v = nullptr;
    node->next = nullptr;

    if (this->head == nullptr) {
        this->head = node;
        this->tail = node;
        return;
    }

    this->tail->next = node;
    this->tail = this->tail->next;
}

void MultiMap::addValueToKey(TKey k, TValue v) {
    KeyNode *currentNodeKey = this->head;

    // Find the key in the list of keys
    while (currentNodeKey != nullptr && currentNodeKey->info != k) {
        currentNodeKey = currentNodeKey->next;
    }

    auto *nodeVal = new ValueNode;
    nodeVal->info = v;
    nodeVal->next = nullptr;

    // If the key is not found, create a new key node
    if (currentNodeKey == nullptr) {
        addNewKey(k);
        currentNodeKey = this->tail;
    }

    // Check if the key already has values
    if (currentNodeKey->v == nullptr) {
        currentNodeKey->v = nodeVal;
    } else {
        // Traverse to the end of the values for the key and append nodeVal
        ValueNode *currentNodeValue = currentNodeKey->v;
        while (currentNodeValue->next != nullptr) {
            currentNodeValue = currentNodeValue->next;
        }
        currentNodeValue->next = nodeVal;
    }
}

void MultiMap::freeValues(ValueNode *head) {
    while (head != nullptr) {
        ValueNode *tmp = head;
        head = head->next;
        delete tmp;
    }
}

MultiMap::MultiMap() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}


void MultiMap::add(TKey c, TValue v) {
    KeyNode *key = this->checkKey(c);

    // if the key is not in the multimap
    if (key == nullptr) {
        this->addNewKey(c);
    }

    // add the value
    this->addValueToKey(c, v);

    this->length++;
}


bool MultiMap::remove(TKey c, TValue v) {
    KeyNode *currentKey = head;
    KeyNode *previousKey = nullptr;
    ValueNode *currentValue = nullptr;
    ValueNode *previousValue = nullptr;

    // Find the key node corresponding to key 'c'
    while (currentKey != nullptr && currentKey->info != c) {
        previousKey = currentKey;
        currentKey = currentKey->next;
    }

    // If key not found
    if (currentKey == nullptr) {
        return false;
    }

    // Find the value node corresponding to value 'v' in the key node
    currentValue = currentKey->v;
    while (currentValue != nullptr && currentValue->info != v) {
        previousValue = currentValue;
        currentValue = currentValue->next;
    }

    // If value node not found
    if (currentValue == nullptr) {
        return false;
    }

    // If value found, remove it
    if (previousValue == nullptr) {
        currentKey->v = currentValue->next;
    } else {
        previousValue->next = currentValue->next;
    }

    delete currentValue;
    length--;

    // If the key node has no more values, remove the key node
    if (currentKey->v == nullptr) {
        if (previousKey != nullptr) {
            previousKey->next = currentKey->next;
        } else {
            head = currentKey->next;
        }
        delete currentKey;
    }

    return true;
}



vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> sol;

    KeyNode *node = this->checkKey(c);

    if (node == nullptr) {
        return sol;
    }

    ValueNode *currentValue = node->v;

    while (currentValue != nullptr) {
        sol.push_back(currentValue->info);
        currentValue = currentValue->next;
    }

    return sol;
}


int MultiMap::size() const {
    return this->length;
}


bool MultiMap::isEmpty() const {
    return this->length == 0;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    while (this->head != nullptr) {
        KeyNode *tmp = this->head;
        this->freeValues(this->head->v);
        this->head = this->head->next;
        delete tmp;
    }
}