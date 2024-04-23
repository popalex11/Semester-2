#include "SetIterator.h"
#include "Set.h"
#include <stdexcept>


SetIterator::SetIterator(const Set& m) : set(m)
{
	current = set.e; // pointer to first element in the dynamic array
}


void SetIterator::first() {
	current = set.e; // pointer to first element in the dynamic array
}


void SetIterator::next() {
	if (!valid())
		throw std::out_of_range("Iterator is already out of range");

	current++;
}


TElem SetIterator::getCurrent() {
	if (!valid())
		throw std::out_of_range("Iterator is already out of range");

	return *current;
}

bool SetIterator::valid() const {
	return current - set.e < set.n;
}

TElem* SetIterator::getPointerToCurrent() {
	return current;
}