#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    testAllExtended();
    testRemoveBetween();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}