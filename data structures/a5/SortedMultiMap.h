#pragma once
// DO NOT INCLUDE SMMITERATOR

// DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::make_pair(-111111, -111111)
using namespace std;

class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class SortedMultiMap {
    friend class SMMIterator;
private:
    Relation relation;
    int capacity;
    int root;
    int firstFree;
    int mapSize; // Renamed from size to mapSize
    TElem* elements;
    int* left;
    int* right;

    // Method to resize the arrays
    void resize();

public:
    // Constructor
    SortedMultiMap(Relation r);

    // Adds a new key-value pair to the sorted multi-map
    void add(TKey c, TValue v);

    // Returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    // Removes a key-value pair from the sorted multi-map
    // Returns true if the pair was removed (it was part of the multi-map), false if nothing is removed
    bool remove(TKey c, TValue v);

    // Returns the number of key-value pairs in the sorted multi-map
    int size() const;

    // Verifies if the sorted multi-map is empty
    bool isEmpty() const;

    // Returns an iterator for the sorted multi-map
    // The iterator will return the pairs as required by the relation (given to the constructor)
    SMMIterator iterator() const;

    // Destructor
    ~SortedMultiMap();
};
