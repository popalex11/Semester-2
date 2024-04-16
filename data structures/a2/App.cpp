#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ExtendedTest.cpp"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include "MultiMap.cpp"
#include "MultiMapIterator.cpp"
#include "ShortTest.cpp"

using namespace std;


int main() {
// ADT MultiMap–using a SLL with unique keys.
// Every key will be associated with a SLL of the values belonging to that key.

	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
