#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Test.h"
int main()
{
    {
        TestBattle();
    }
    _CrtDumpMemoryLeaks();
}