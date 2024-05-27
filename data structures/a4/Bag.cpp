#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;

int hashCode(TElem e) {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    return abs(e);
}

int Bag::h(TElem e) const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    return hashCode(e) % m;
}

int Bag::hashFunction(TElem e, int i) const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    return (int) ((float) h(e) + c1 * (float) i + c2 * (float) i * (float) i) % m;
}

Bag::Bag() {
    /*
     * Best case: theta(1)
     * Worst case: theta(m)
     * Average case: O(m)
     */
    //TODO - Implementation
    m = MAX;
    cont = 0;
    c1 = 0.5;
    c2 = 0.5;
    elems = new TElem[m];
    frequencies = new int[m];
    for (int i = 0; i < m; i++) {
        elems[i] = NULL_TELEM;
        frequencies[i] = 0;
    }
}

int Bag::findPosition(TElem e) {
    /*
     * Best case: theta(1)
     * Worst case: theta(m)
     * Average case: O(m)
     */
    int i = 0;
    while (i < m) {
        int pos = hashFunction(e, i);
        if (elems[pos] == e || elems[pos] == NULL_TELEM || elems[pos] == DELETED)
            return pos;
        i++;
    }
    return -1;
}

void Bag::resize() {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    TElem *newElems = new TElem[2 * m];
    int *newFreq = new int[2 * m];

    for (int i = 0; i < 2 * m; i++) {
        newElems[i] = NULL_TELEM;
        newFreq[i] = 0;
    }

    m = 2 * m;

    for (int j = 0; j < m / 2; j++) {
        if (elems[j] != NULL_TELEM) {
            int i = 0;
            int position;
            do {
                position = hashFunction(elems[j], i);
                i++;
            } while (newElems[position] != NULL_TELEM);
            newElems[position] = elems[j];
            newFreq[position] = frequencies[j];
        }
    }

    delete[] elems;
    delete[] frequencies;
    elems = newElems;
    frequencies = newFreq;
}

void Bag::add(TElem elem) {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    if (cont / m >= 0.7)
        resize();
    int position = findPosition(elem);
    if (elems[position] == elem)
        frequencies[position]++;
    else {
        elems[position] = elem;
        frequencies[position] = 1;
    }
    cont++;
}


bool Bag::remove(TElem elem) {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    int i = 0;
    while (i < m) {
        int pos = hashFunction(elem, i);
        if (elems[pos] == elem) {
            frequencies[pos]--;
            if (frequencies[pos] == 0)
                elems[pos] = DELETED;
            cont--;
            return true;
        }
        i++;
    }
    return false;
}


bool Bag::search(TElem elem) const {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    int i = 0;
    while (i < m && elems[hashFunction(elem, i)] != NULL_TELEM) {
        int pos = hashFunction(elem, i);
        if (elems[pos] == elem)
            return true;
        i++;
    }
    return false;
}

int Bag::nrOccurrences(TElem elem) const {
    /*
     * Best case: theta(1)
     * Worst case: theta(n)
     * Average case: O(n)
     */
    //TODO - Implementation
    int i = 0;
    while (i < m) {
        int pos = hashFunction(elem, i);
        if (elems[pos] == elem)
            return frequencies[pos];
        i++;
    }
    return 0;
}

int Bag::size() const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    //TODO - Implementation
    return cont;
}


bool Bag::isEmpty() const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    //TODO - Implementation
    return cont == 0;
}

BagIterator Bag::iterator() const {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    return BagIterator(*this);
}

void Bag::addOccurrences(int nr, TElem elem) {
    if (nr < 0)
        throw std::exception();
    if (!search(elem))
        throw std::exception();
    int i = 0;
    int pos = hashFunction(elem, i);
    while (i < m && elems[pos] != NULL_TELEM){
        if (elems[pos] == elem) {
            frequencies[pos] += nr;
            break;
        }
        i ++;
    }
}

Bag::~Bag() {
    /*
     * Best case: theta(1)
     * Worst case: theta(1)
     * Average case: theta(1)
     */
    //TODO - Implementation
    delete[] elems;
    delete[] frequencies;
}

