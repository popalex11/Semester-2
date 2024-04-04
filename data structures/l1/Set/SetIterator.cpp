#include "SetIterator.h"
#include "Set.h"
#include <stdexcept>

SetIterator::SetIterator(const Set& m) : set(m)
{
	this->elements = this->set.setElements;
	this->firstElem = 0;
}


void SetIterator::first() {
	this->firstElem = 0;
}


void SetIterator::next() {
	/// should throw exception if the iterator is not valid or the set is empty
	if (this->firstElem == this->set.nrOfElements || this->set.nrOfElements == 0)
		throw std::out_of_range("Iterator is out of range");

	this->firstElem++;
}


TElem SetIterator::getCurrent()
/// should throw exception if the iterator is not valid or the set is empty and return the current element
{
	if (this->firstElem == this->set.nrOfElements || this->set.nrOfElements == 0)
		throw std::out_of_range("Iterator is out of range");
	return this->elements[this->firstElem];
}

bool SetIterator::valid() const {
	if (this->set.size() == 0)return 0;
	if(this->firstElem == this->set.nrOfElements)
		return 0;
	return 1;
}