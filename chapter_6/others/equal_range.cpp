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

// 没有一开始直接用lower和upper，而是先找出来相等的元素，分出来前后两个区间，在两个区间分别upper和lower
// 防止直接lower和upper在重复区域重复计算
template<class _RI, class T>
pair<_RI, _RI> equal_range(_RI first, _RI last, const T& x){
    int len = last -first;
    int half;
    _RI middle, right, left;
    while(len > 0){
        half = len >> 1;
        middle = first + half;
        if(*middle < x){
            first = middle + 1;
            len = len - half - 1;
        }
        else if(x < *middle)
            len = half;
        else{   // 上面和lower_bound基本一样，现在讨论==的情况
            left = lower_bound(first, middle, x);   // 此时的first和middle已经不是最初的区间了
            right = upper_bound(++middle, first + len, x);  // 此时的++middle和first + len已经不是最初的区间
            return (left, right);
        }
    }
}

int main(int argc, char** argv)
{
    

    return 0;
}
