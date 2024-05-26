#pragma once

// DO NOT INCLUDE BAGITERATOR

// DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
class BagIterator;

class Bag {
private:
    TElem* elements; // Array for elements
    int* frequencies; // Array for frequencies
    int* next; // Array for chaining
    int firstEmpty; // Index of the first empty slot
    int capacity; // Capacity of the hashtable
    int sizeOfBag; // Number of elements in the bag
    int hash(TElem e) const; // Hash function

    // Helper methods
    int findPosition(TElem e) const;
    void resize();

    // DO NOT CHANGE THIS PART
    friend class BagIterator;

public:
    // constructor
    Bag();

    // adds an element to the bag
    void add(TElem e);

    // removes one occurrence of an element from a bag
    // returns true if an element was removed, false otherwise (if e was not part of the bag)
    bool remove(TElem e);

    // checks if an element appears in the bag
    bool search(TElem e) const;

    // returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;

    // returns the number of elements from the bag
    int size() const;

    // returns an iterator for this bag
    BagIterator iterator() const;

    // checks if the bag is empty
    bool isEmpty() const;

    // destructor
    ~Bag();
};
