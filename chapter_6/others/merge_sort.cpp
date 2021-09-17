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

// in-place的merge操作，不需要额外空间
template<class _RI>
void _inplace_merge(_RI first, _RI middle, _RI last){
    if(first == middle || middle == last)   return;
    _RI first_cut = first, second_cut = middle;
    int d1 = middle - first, d2 = last - middle;
    if(d1 > d2){
        first_cut = first + d1 / 2;
        second_cut = lower_bound(middle, last, *first_cut);
    }
    else{
        second_cut = middle + d2 / 2;
        first_cut = upper_bound(first, middle, *second_cut);
    }
    _RI new_middle = rotate(first_cut, middle, second_cut);
    _inplace_merge(first, first_cut, new_middle);
    _inplace_merge(new_middle, second_cut, last);
}

// merge sort接口
template<class _RI>
void _merge_sort(_RI first, _RI last){
    if(first == last || first + 1 == last)  return;
    _RI middle = first + (last - first) / 2;
    _merge_sort(first, middle);
    _merge_sort(middle, last);
    _inplace_merge(first, middle, last);
}

int main(int argc, char** argv)
{
    vector<int> vec{5,6,7,8,1,2,3,4};
    _merge_sort(vec.begin(), vec.end());
    for(auto i: vec)
        cout << i << " ";
    return 0;
}
