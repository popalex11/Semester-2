#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>
#include <stdexcept>

SortedIndexedList::SortedIndexedList(Relation r) : relation(r) , head(-1), capacity(10), size_list(0) {
	next = new int[capacity];
	elements = new TComp[capacity];

	for (int i = 0; i < capacity; i++) {
		next[i] = -1;
	}
}

int SortedIndexedList::size() const {
	return size_list;
	return 0;
}

bool SortedIndexedList::isEmpty() const {
	return size_list == 0;
	return false;
}

TComp SortedIndexedList::getElement(int pos) const{
	if (pos < 0 || pos >= size_list) {
		throw std::out_of_range("Invalid position");
	}
	int current = head;
	for ( int j = 0; j < pos; j++) {
		current = next[current];
	}
	return elements[current];
}

TComp SortedIndexedList::remove(int pos) {
	if (pos < 0 || pos >= size_list) {
        throw std::out_of_range("Invalid position");
    }
    if (pos == 0) {
        int removed = head;
        head = next[head];
        --size_list;
        return elements[removed];
    }
    int current = head;
    int prev = -1;
    for (int i = 0; i < pos; ++i) {
        prev = current;
        current = next[current];
    }
    next[prev] = next[current];
    --size_list;
    return elements[current];
	
}

int SortedIndexedList::search(TComp e) const {
	int current = head;
    int pos = 0;
    if(current == elements[current]) {
        return pos;
    }
    while (current != -1 && next[current]!=-1 && relation(elements[current], e)) {
        ++pos;
        current = next[current];
    }
    if (current != -1 && elements[current] == e) {
        return pos;
    }
    return -1;
}

void SortedIndexedList::add(TComp e) {
	if (size_list == capacity) {
        // Resize the arrays
        int new_capacity = 2 * capacity;
        int* new_next = new int[new_capacity];
        TComp* new_elements = new TComp[new_capacity];
        for (int i = 0; i < capacity; ++i) {
            new_next[i] = next[i];
            new_elements[i] = elements[i];
        }
        for (int i = capacity; i < new_capacity; ++i) {
            new_next[i] = -1;
        }
        delete[] next;
        delete[] elements;
        next = new_next;
        elements = new_elements;
        capacity = new_capacity;
    }
    int prev = -1;
    int current = head;
    while (current != -1 && relation(elements[current], e)) {
        prev = current;
        current = next[current];
    }
    int new_position = size_list;
    elements[new_position] = e;
    if (prev == -1) {
        next[new_position] = head;
        head = new_position;
    } else {
        next[new_position] = next[prev];
        next[prev] = new_position;
    }
    ++size_list;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete[] next;
	delete[] elements;
}
