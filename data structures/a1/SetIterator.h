#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;

private:
	//Reference to the iterated container
	const Set& set;

	//Constructor
	//complexity: O(1)
	SetIterator(const Set&);

	//Pointer to the current element
	TElem* current;

	//AUXILIARY FUNCTION
	//complexity: O(1)
	TElem* getPointerToCurrent();

public:
	//Sets the iterator to the first element of the set
	//complexity: O(1)
	void first();

	//Sets the iterator to the next element
	//complexity: O(1)
	void next();

	//Returns the current element
	//complexity: O(1)
	TElem getCurrent();

	//Returns whether the iterator is valid (it hasn't gone out of bounds)
	//complexity: O(1)
	bool valid() const;
};
