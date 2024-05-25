#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>


SortedIndexedList::SortedIndexedList(Relation r) {

    // Set the initial capacity of the list
    this->capacity = INITIAL_CAPACITY;

    // Allocate memory for the elements and next arrays
    this->elements = new TComp[capacity];
    this->next = new int[capacity];

    // Initialize the head of the list to -1 ( indicating an empty list )
    this->head = -1;

    // Initialize the next array such that each element points to the next index
    for (int i = 0; i < capacity - 1; i++) {
        this->next[i] = i + 1;
    }

    // Set the first empty position to 1 ( the first position in the array )
    this->firstEmpty = 1;

    // Set the last element in the next array to -1 ( indicating the end of the list )
    this->next[capacity-1] = -1;

    // Set the relation
    this->relation = r;

    // Set the length of the list to 0
    this->length = 0;

}

int SortedIndexedList::size() const {
    // Complexity: Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
    // The complexity is Theta(1) because we only have to return the length of the list
    return this->length;
}

bool SortedIndexedList::isEmpty() const {
    // Complexity: Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
    // The complexity is Theta(1) because we only have to check if the length of the list is 0
    return this->length == 0;
}

TComp SortedIndexedList::getElement(int i) const{
    // Complexity: Best case: Theta(1), Worst case: O(n), Average case: O(n)
    // The complexity is O(n) because we have to iterate through the list to find the element at the given position

    /**
     * Returns the element at the given position
     *
     * @return: the element at the given position
     * @throws: exception if the position is invalid
     */

    // Check if the position is valid
    if ( i < 0 || i >= this->length){
        throw std::exception();
    }else{

        // From the head, iterate throught the list following the next pointers until the given position is reached
        int currentNode = this->head;
        int currentPosition = 0;
        while (currentPosition < i && currentNode != -1){
            currentNode = this->next[currentNode];
            currentPosition++;
        }

        if (currentNode == -1){
            throw std::exception();
        }else{
            return this->elements[currentNode];
        }
    }
}

TComp SortedIndexedList::remove(int i) {
    // Complexity: Best case: Theta(1), Worst case: O(n), Average case: O(n)
    // The complexity is O(n) because we have to iterate through the list to find the element at the given position

    if ( i <0 || i>=this->length)
        throw std::exception();

    // From the head, iterate throught the list following the next pointers until the given position is reached
    int current = this->head;
    int previous = -1;
    while (i > 0) {
        previous = current;
        current = this->next[current];
        i--;
    }

    // Once the position is reached, we store the element to be removed
    TComp removedElement = this->elements[current];


    // Update the next pointer of the previous node to skip the current node
    if (previous == -1) {
        this->head = this->next[current];
    } else {
        this->next[previous] = this->next[current];
    }


    // Mark the current position as empty & it's next pointer as the first empty position
    // and update the first empty position to the current position
    this->elements[current] = NULL_TCOMP;
    this->next[current] = this->firstEmpty;
    this->firstEmpty = current;

    // decrement the length of the list
    this->length--;

    return removedElement;
}

int SortedIndexedList::search(TComp e) const {
    // Complexity: Best case: Theta(1), Worst case: O(n), Average case: O(n)
    // The complexity is O(n) because we have to iterate through the list to find the element


    // From the head, iterate throught the list following the next pointers until the given position is reached
    int current = this->head;
    int pos = 0;
    while (current != -1 ) {
        if (this->elements[current] == e) {
            return pos;
        }
        current = this->next[current];
        pos++;
    }
    return -1;
}


void SortedIndexedList::add(TComp e) {
    // Complexity: Best case: Theta(1), Worst case: O(n), Average case: O(n)
    // The complexity is O(n) because we have to iterate through the list to find the correct position to insert the new element

    // Check if the list is full
    if (firstEmpty == -1) {

        // If the list is full, resize the list to double its current capacity
        int newCapacity = 2 * this->capacity;
        TComp* newElements = new TComp[newCapacity];
        int* newNext = new int[newCapacity];

        // Copy the existing elements and next pointers to the new arrays
        for (int i = 0; i < this->capacity; i++) {
            newElements[i] = this->elements[i];
            newNext[i] = this->next[i];
        }

        // Initialize the next pointers of the new positions
        for (int i = this->capacity; i < newCapacity - 1; i++) {
            newNext[i] = i + 1;
        }
        newNext[newCapacity - 1] = -1;

        // Delete the old arrays
        delete[] this->elements;
        delete[] this->next;

        // Update the elements, next, capacity, and firstEmpty pointers
        this->elements = newElements;
        this->next = newNext;
        this->capacity = newCapacity;
        this->firstEmpty = this->capacity;
    }

    // Get the position to add the new element
    int posToAdd = firstEmpty;
    firstEmpty = next[firstEmpty];

    // Add the new element
    this->elements[posToAdd] = e;

    // If the list is empty or the new element is smaller than the head, add the new element at the head
    if (this->head == -1 || this->relation(e, this->elements[this->head])) {
        next[posToAdd] = this->head;
        this->head = posToAdd;
    } else {
        // Otherwise, find the correct position to insert the new element
        int current = this->head;
        int prev = -1;
        while (current != -1 && this->relation(this->elements[current], e)) {
            prev = current;
            current = this->next[current];
        }

        // Insert the new element at the found position
        next[posToAdd] = current;
        if (prev != -1) {
            next[prev] = posToAdd;
        }
    }

    // Increment the length of the list
    this->length++;
}

void SortedIndexedList::removeBetween(int start, int end) {
    // Check if the start and end indices are valid
    if (start < 0 || end < start || end >= this->length) {
        throw std::exception();
    }

    // Initialize the current and previous nodes to navigate through the list
    int current = this->head;
    int previous = -1;

    // Navigate to the start index of the section to be removed
    for (int i = 0; i < start; i++) {
        previous = current;
        current = this->next[current];
    }

    // Identify the first and last nodes to be removed from the list
    int firstToRemove = current;
    int lastToRemove = current;

    // Navigate to the end index of the section to be removed
    for (int i = start; i <= end; i++) {
        lastToRemove = current;
        current = this->next[current];
    }

    // Unlink the section to be removed from the list by updating the next pointers
    if (previous == -1) {
        this->head = current;
    } else {
        this->next[previous] = current;
    }

    // Add the removed nodes to the free list and update the first empty position
    // setting the firstEmpty to the first element to be removed
    lastToRemove = this->next[lastToRemove];
    current = firstToRemove;

    // iterate through the elements to be removed
    while (current != lastToRemove) {
        int tempNext = this->next[current];
        this->elements[current] = NULL_TCOMP;
        this->next[current] = this->firstEmpty;
        this->firstEmpty = current;
        current = tempNext;
    }

    // Update the length of the list
    this->length -= (end - start + 1);
}


ListIterator SortedIndexedList::iterator(){
    return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
        delete [] this->elements;
        this->elements = nullptr;

        delete [] this->next;
        this->next = nullptr;

    this->firstEmpty = 1;
    this->head = -1;
    this->length = 0;
}