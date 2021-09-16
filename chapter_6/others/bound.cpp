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

// 比较时只用<，便于传递自定义的运算符
template<class _RI, class T>
_RI lower_bound(_RI first, _RI last, const T& x){
    int len = last - first;
    int half = 0;
    _RI middle;
    while(len > 0){
        half = len >> 1;
        middle = first + half;
        if(*middle < x){    // 寻找第一个大于等于，因此if条件要可以分为大于等于和else
            first = middle + 1;
            len = len - half - 1;
        }
        else 
            len = half;
    }
    return first;
}

template<class _RI, class T>
_RI upper_bound(_RI first, _RI last, const T& x){
    int len = last - first;
    int half;
    _RI middle;
    while(len > 0){
        half = len >> 1;
        middle = first + half;
        if(x < *middle)     // 寻找第一个大于，因此if条件要可以分为大于和else
            len = half;
        else{
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

template<class _RI, class T>
bool binary_search(_RI first, _RI last, const T& x){
    _RI result = lower_bound(first, last, x);
    return result != last && *result == x;  //先判断不是last，再解引用
}

int main(int argc, char** argv)
{
    

    return 0;
}
