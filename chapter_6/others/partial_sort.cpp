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

template<class _RI>
void _partial_sort(_RI first, _RI middle, _RI last){
    make_heap(first, middle);
    for(_RI i = middle; i != last; ++i)
        if(*i < *first){
            iter_swap(i, first);
            // __adjust_heap()
        }
    sort_heap(first, middle);
}

// cmp自定义版本
template<class _RI, class Compare>
void _partial_sort(_RI first, _RI middle, _RI last, Compare cmp){
    make_heap(first, middle, cmp);
    for(_RI i = middle; i != last; ++i)
        if(cmp(*i, *first)){
            iter_swap(i, first);
            // __adjust_heap()
        }
    sort_heap(first, middle, cmp);
}

int main(int argc, char** argv)
{
    

    return 0;
}
