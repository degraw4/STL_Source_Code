#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <typeinfo>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <stdexcept>

using namespace std;

void test(int *a){
    cout << "1\n";
}

void test(const int *a){
    cout << "2\n";
}

int main(int argc, char** argv)
{
    int a = 0;
    const int b = 0;
    test(&a);
    test(&b);

    return 0;
}
