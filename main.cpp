#include <iostream>
#include <string>
#include "BiRing.h"
using namespace std;

int main()
{
    BiRing<int, string> br1;
    cout << br1 << endl;

    br1.push_front(1, "one");
    cout << br1 << endl;

    br1.push_back(2, "two");
    cout << br1 << endl;

    br1.pop_front();
    cout << br1 << endl;

    br1.pop_back();
    cout << br1 << endl;

    BiRing<int, string>::iterator it = br1.begin();
    it = it.add(1, "uno");
    it = it.add(5, "cinque");
    it--;
    it.add(3, "tre");
    it.add(2, "due");
    it += 2;
    it = it.add(4, "quattro");
    cout << br1 << endl;

    BiRing<int, string> br2(br1);

    it -= 3;
    it = it.remove();
    it += 3;
    it = it.remove();
    it -= 2;
    it = it.remove();
    it--;
    it = it.remove();
    it.remove();
    cout << br1 << endl;

    BiRing<int, string>::iterator iv = br2.find_key(3);
    iv.remove();
    iv = br2.find_info("quattro");
    iv.remove();
    cout << br2 << endl;

    br1 = br2;
    cout << br1 << endl;

    return 0;
}

//Expected console output for this rudimentary test is:

//[]
//[(1,one)]
//[(1,one)(2,two)]
//[(2,two)]
//[]
//[(1,uno)(2,due)(3,tre)(4,quattro)(5,cinque)]
//[]
//[(1,uno)(2,due)(5,cinque)]
//[(1,uno)(2,due)(5,cinque)]
//
//Process returned 0 (0x0)   execution time : 0.031 s
//Press any key to continue.
