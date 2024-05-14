
#pragma once

#define INITIAL_CAPACITY 10

typedef int TElem;

struct Node {
    TElem value;
    int frequency;
    bool valid;
};

class BagIterator;

class Bag {
private:
    int size_of_bag;

    void resize();
	int hashFunction(TElem elem, int capacity) const;


public:
    int capacity;
    Node* elements;

    Bag();
    void add(TElem elem);
    bool remove(TElem elem);
    bool search(TElem elem) const;
    int nrOccurrences(TElem elem) const;
    int size() const;
    bool isEmpty() const;
    BagIterator iterator() const;
    ~Bag();
};

