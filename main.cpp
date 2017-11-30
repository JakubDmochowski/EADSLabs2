#include <iostream>

#include "BiRing.cpp"

using namespace std;

int main()
{
    BiRing<int, int> t;
    t.push_back(5,6);
    t.push_front(1,4);
    t.add(6,4,5);
    cout << t;
    return 0;
}
