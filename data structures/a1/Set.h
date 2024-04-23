#pragma once

#define NULL_TELEM -111111
typedef int TElem; //Generic data type - here it is int
class SetIterator;

class Set {
	friend class SetIterator;

    private:
        //capacity
        int cp;

        //size (actual number of elements)
        int n;

        //elements
        TElem* e;

        //the resizing operation
        void resize();

    public:
        //default constructor
        //complexity: O(1)
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        //complexity: O(n)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        //complexity: O(n)
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        //complexity: O(n)
        bool search(TElem elem) const;

        //returns the number of elements;
        //complexity: O(1)
        int size() const;

        //check whether the set is empty or not;
        //complexity: O(1)
        bool isEmpty() const;

        //return an iterator for the set
        //complexity: O(1)
        SetIterator iterator() const;

        // destructor
        //complexity: O(1)
        ~Set();
};
