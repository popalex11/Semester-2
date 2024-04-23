#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>
#include <assert.h>
using namespace std;

int main() {
	
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;

	return 0;
}
