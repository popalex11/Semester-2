#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    this->current = list.head;
}

void ListIterator::first(){
    this->current = list.head;
}

void ListIterator::next(){
    if(!this->valid())
        throw std::exception();
    this->current = list.next[current];
}

bool ListIterator::valid() const{
    return this->current != -1;
}

TComp ListIterator::getCurrent() const{
    if ( !this->valid() )
        throw std::exception();
    return list.elements[current];
}



