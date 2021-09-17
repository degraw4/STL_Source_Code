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

const int _stl_sort_threshold = 16;
int middle_3 = 0;

int _lg(int n){
    int k;
    for(k = 0; n > 1; n >>= 1)  ++k;
    return k;
}

template<class _RI>
void _insert_sort(_RI first, _RI last){
    if(first == last)   return; // 判空
    for(_RI i = first + 1; i != last; ++i)  // 一个元素自动退出循环
        _linear_insert(first, i);     // 在子区间first-i内排序，其中i为新加入的，且不是尾后iter，除i之外都为升序
}

template<class _RI>
void linear_insert(_RI first, _RI last){
    typename iterator_traits<_RI>::value_type value = *last;
    if(value < *first){ // 新加入的比首段最小的还小，直接移过去
        copy_backward(first, last, last + 1);   // 注意iter区间，_insert_aux传入的last并非尾后iter
        *first = value;
    }
    else
        _unguarded_linear_insert(last, value); // 此函数无需额外的区间判断，可以让last一直--，直至找到位置
}

template<class _RI, class T>
void _unguarded_linear_insert(_RI last, T value){
    _RI prev = last - 1;
    while(value < *prev){
        *last = *prev;
        --last;
        --prev;
    }
    *last = value; //此时的*prev <= value
}

// 按枢轴划分，返回后段的第一个iter
template<class _RI, class T>
_RI _partition(_RI first, _RI last, T pivot){
    while(true){
        while(*first < pivot) ++first;
        --last;
        while(pivot < *last)  --last;
        if(!(first < last)) return first;
        iter_swap(first, last);
        ++first;
    }
}

// STL sort
template<class _RI>
void _sort(_RI first, _RI last){
    if(first != last){
        _intro_sort_loop(first, last, 2 * _lg(last - first));   // 快排循环
        _final_insert_sort(first, last);    // 序列已经排成了许多个几乎有序的小序列
    }
}

template<class _RI>
void _intro_sort_loop(_RI first, _RI last, int depth){
    while(last - first > _stl_sort_threshold){
        if(depth == 0){
            partial_sort(first, last, last);    // 恶意划分，转为heap_sort
            return;
        }
        --depth;
        _RI cut = _partition(first, last, *(first + middle_3));
        _intro_sort_loop(first, cut, depth);
        _intro_sort_loop(cut, last, depth);
    }
}

template<class _RI>
void _final_insert_sort(_RI first, _RI last){
    if(last - first > _stl_sort_threshold){
        _insert_sort(first, first + _stl_sort_threshold); 
        for(_RI i = first + _stl_sort_threshold; i != last; ++i)
            _unguarded_linear_insert(i, *i);
    }
    else
        _insert_sort(first, last);
}

int main(int argc, char** argv)
{
    

    return 0;
}
