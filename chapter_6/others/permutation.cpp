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

template<class _BI>
bool _next_permutation(_BI first, _BI last){
    if(first == last)   return false;
    _BI i = first;
    ++i;
    if(i == last)   return false;
    i = last;
    --i;
    while(true){
        _BI ii = i;
        --i;
        if(*i < *ii){
            _BI j = last;
            while(!(*i < *--j));    // 前置--，可以保证跳出循环的就是不满足循环条件的
            iter_swap(i, j);
            reverse(ii, last);
            return true;
        }
        if(i == first){
            reverse(ii, last);
            return false;
        }
    }
}

template<class _BI>
bool _prev_permutation(_BI first, _BI last){
    if(first == last)   return false;
    _BI i = first;
    ++i;
    if(i == last)   return false;
    i = last;
    --i;
    while(true){
        _BI ii = i;
        --i;
        if(*ii < *i){
            _BI j = last;
            while(!(*--j < *i));
            iter_swap(i, j);
            reverse(ii, last);
            return true;
        }
        if(i == first){
            reverse(ii, last);
            return false;
        }
    }
}

template<class _RI>
void _random_shuffle(_RI first, _RI last){
    if(first != last)
        for(_RI i = first + 1; i != last; ++i)
            iter_swap(i, first + rand((i - first) + 1));
}

int main(int argc, char** argv)
{
    vector<int> vec{1,1,2,3};
    for_each(vec.begin(), vec.end(), [](int i) { cout << i << " "; });
    cout << endl;
    while(_next_permutation(vec.begin(), vec.end())){
        for_each(vec.begin(), vec.end(), [](int i) { cout << i << " "; });
        cout << endl;
    }

    return 0;
}
