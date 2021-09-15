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
#include <cstddef>

using namespace std;

// iterator类
template<class Category,
         class T,
         class Distance = ptrdiff_t,
         class Pointer = T*,
         class Reference = T&>
class iterator{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

int main(int argc, char** argv)
{
    

    return 0;
}
