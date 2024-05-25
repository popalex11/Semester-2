#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}


void testRemoveBetween() {
    std::cout << "Test removeBetween" << std::endl;
    SortedIndexedList list = SortedIndexedList(relation1);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    cout<<list.size()<<endl;
    for(int i = 0; i < list.size(); i++) {
        cout<<list.getElement(i)<<endl;
    }
    list.removeBetween(1, 3);
    assert(2 == list.size());
    assert(1 == list.getElement(0));
    assert(5 == list.getElement(1));

}