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
class ValueIterator;
typedef bool(*Relation)(TKey, TKey);

class SortedMultiMap {
    friend class SMMIterator;
    friend class ValueIterator;
private:
    Relation relation;
    int capacity;
    int root;
    int firstFree;
    int mapSize; // Renamed from size to mapSize
    TElem* elements;
    int* left;
    int* right;

    void resize();

public:
    SortedMultiMap(Relation r);

    // Adds a new key-value pair to the sorted multi-map
    void add(TKey c, TValue v);

    vector<TValue> search(TKey c) const;

    // Returns true if the pair was removed (it was part of the multi-map), false if nothing is removed
    bool remove(TKey c, TValue v);

    int size() const;

    bool isEmpty() const;

    // The iterator will return the pairs as required by the relation (given to the constructor)
    SMMIterator iterator() const;

    ValueIterator iteratorForKey(TKey k) const;

    ~SortedMultiMap();
};
