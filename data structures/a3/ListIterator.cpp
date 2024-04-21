#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
#include <stdexcept>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
}

void ListIterator::first(){
	current = list.head;
}

void ListIterator::next(){
	if (valid ()) {
		current = list.next[current];
	}
}

bool ListIterator::valid() const{
	return current != -1;
	return false;
}

TComp ListIterator::getCurrent() const{
	if (!valid()) {
		throw std::runtime_error("Invalid iterator position");
	}
	return list.elements[current];
}


