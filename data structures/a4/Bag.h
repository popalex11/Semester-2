#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define MAX 1048
#define DELETED -111112
typedef int TElem;

class BagIterator;

class Bag {

private:
    //TODO - Representation
    int m;
    TElem *elems;
    int *frequencies;
    int cont;
    float c1, c2;

    int h(TElem e) const;

    int hashFunction(TElem e, int i) const;

    int findPosition(TElem e);

    //DO NOT CHANGE THIS PART
    friend class BagIterator;

    void resize();

public:
    //constructor
    Bag();

    //adds an element to the bag
    void add(TElem e);

    //removes one occurrence of an element from a bag
    //returns true if an element was removed, false otherwise (if e was not part of the bag)
    bool remove(TElem e);

    //checks if an element appearch in the bag
    bool search(TElem e) const;

    //returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;

    //returns the number of elements from the bag
    int size() const;

    //returns an iterator for this bag
    BagIterator iterator() const;

    //checks if the bag is empty
    bool isEmpty() const;

    //adds nr occurrences of elem to the bag
    //throws an exception if nr is negative
    void addOccurrences(int nr, TElem elem);

    //destructor
    ~Bag();
};