#include "Set.h"
#include "SetIterator.h"
#include <iostream>

Set::Set() {
	//Initializing capacity
	cp = 1;

	//Allocating space dynamically for cp elements of type TElem
	e = new TElem[cp];

	//Initializing size
	n = 0;
}

void Set::resize() {
	//New array of double the capacity of the initial one
	TElem* eNew = new TElem[2 * cp];

	//We copy all the elements from the old array into the new one
	for (int i = 0; i < n; i++)
		*(eNew+i) = *(e+i);

	//Doubling the capacity
	cp *= 2;

	//Freeing the memory occupied by the initial array
	delete[] e;

	//Now e will refer to the newly created array
	e = eNew;
}

bool Set::add(TElem elem) {
	//elem will not be added if it already exists in the set
	if (search(elem))
		return false;
	
	//Resizing array if it has reached maximum capacity
	if (n == cp)
		resize();

	//Adding elem to the end of the array
	*(e + n) = elem;

	//Incremented the size
	n++;

	return true;
}


bool Set::remove(TElem elem) {
	if (!search(elem))
		return false;

	SetIterator it = iterator();

	while (it.getCurrent() != elem) {
		it.next();
	}

	//moving the last element to the position where elem was found
	// it.setCurrent(*(e - n + 1)); doesn't work

	TElem* ptr = it.getPointerToCurrent();
	*ptr = *(e + n - 1);

	//Decremented the size
	n--;

	return true;
}

bool Set::search(TElem elem) const {
	//Performing a sequential search on the array
	SetIterator it = iterator();

	while (it.valid()) {
		if (it.getCurrent() == elem)
			return true;

		it.next();
	}

	return false;
}


int Set::size() const {
	return n;
}


bool Set::isEmpty() const {
	return n == 0;
}


Set::~Set() {
	//Freeing the memory occupied by the elements of the set
	delete[] e;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
