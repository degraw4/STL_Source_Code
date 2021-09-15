#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <stdexcept>

using namespace std;

enum {ALIGN = 8};

int round_up(int bytes){
    return (((bytes) + ALIGN - 1) & ~(ALIGN - 1));
}

int main(int argc, char** argv)
{
    int a = 0;
    int b = 1;
    int *p1 = &a;
    int *p2 = &b;
    int* p3 = p1;
    p1 = p2;
    cout << *p3 << endl;

    return 0;
}
