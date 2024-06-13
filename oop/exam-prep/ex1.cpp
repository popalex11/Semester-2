#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5 };
    vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
    v.insert(it, 7);
    it = v.begin() + 2;
    *it = 11;
    vector<int> x;
    std::copy_if(v.begin(), v.end(), back_inserter(x), [](int a) { return a % 2 == 1; });

    for (auto i : x)
        cout << i << " ";

    return 0;
}

// 123745 12 11 745 1 11 7 5