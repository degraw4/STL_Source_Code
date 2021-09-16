#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <numeric>
#include <typeinfo>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <stdexcept>

using namespace std;

template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
    if(first == last)   return last;
    ForwardIterator next = first;   // 查找模板1
    while(++next != last){
        if(*next == *first)
            return first;
    }
    return last;
}

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& x){
    while(first != last && *first != x) // 查找模板2
        ++first;
    return first;
}

template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& x){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first)   // 查找模板3
        if(*first == x)
            ++n;
    return n;
}

template<class _FI1, class _FI2>
_FI1 search(_FI1 first1, _FI1 last1, _FI2 first2, _FI2 last2){  // search的简介模板
    int d1 = last1 - first1;
    int d2 = last2 - first2;
    if(d1 < d2) return last1;
    _FI1 cur1 = first1;
    _FI1 cur2 = first2;
    while(cur2 != last2){
        if(*cur1 == *cur2){
            ++cur1;
            ++cur2;
        }
        else
            if(d1 == d2)    return last1;
            else{
                cur1 = ++first1;
                cur2 = first2;
                --d1;
            }
    }
    return first1;
}

template<class _FI, class T>
_FI search_n(_FI first, _FI last, int count, const T& x){
    if(count < 0)   return first;
    first = find(first, last, x);
    while(first != last){
        int n = count - 1;
        _FI i = first;
        ++i;
        while(n > 0 && i != last && *i == x){
            --n;
            ++i;
        }
        if(!n)  return first;
        else first = find(first, last, x);  
    }
    return last;
}

// 找出序列2在序列1中最后一次出现的起点
// 找出第一次出现的起点，用search
// 找出序列2中某元素第一次出现，用find_first_of
template<class InputIterator1, class InputIterator2>
InputIterator1 find_end(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2){
    if(first2 == last2) return last1;
    InputIterator1 result = last1;
    while(true){
        InputIterator1 new_result = search(first1, last1, first2, last2);
        if(new_result == last1)
            return result;
        else{   // 继续寻找后面有没有
            result = new_result;
            first1 = ++new_result;
        }
    }
}

// 默认用于递增的序列，比较用less
template<class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2){
    while(first1 != last1 && first2 != last2){
        if(*first2 < *first1)
            return false;
        else if(*first1 < *first2)
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}

// 自定义比较，递增用less，递减用greater
template<class InputIterator1, class InputIterator2, class Compare>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2, Compare cmp){
    while(first1 != last1 && first2 != last2){
        if(cmp(*first2, *first1))
            return false;
        else if(cmp(*first1, *first2))
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}

// not stable的划分
// 首尾元素划分更简单直接，但是注意条件为while(first<=last)
template<class _BI, class Predict>
_BI partition(_BI first, _BI last, Predict prec){   // iter划分模板
    while(true){
        while(true)
            if(first == last)
                return first;
            else if (pred(*first))
                ++first;
            else
                break;
        --last;
        while(true)
            if(first == last)
                return first;
            else if(!pred(*last))
                --last;
            else break;
        iter_swap(first, last);
        ++first;
    }
}

// remove，并不是真的删除，而是放在后面
template<class _FI, class _OI, class T>
_OI remove_copy(_FI first, _FI last, _OI result, const T& x){
    for(; first != last; ++first)
        if(*first != x){
            *result = *first;
            ++result;
        }
    return result;
}

template<class _FI, class T>
_FI remove(_FI first, _FI last, const T& x){
    first = find(first, last, x);   // 先找到第一个要remove的，作为result的起点，然后从其后面继续remove_copy
    _FI next = first;
    return first == last ? first: remove_copy(++next, last, first, x);
}

// BI不能用<，所以要特殊处理
template<class _BI, class T>
void reverse(_BI first, _BI last){
    while(true)
        if(first == last || first == --last)
            return;
        else    
            iter_swap(first++, last);
}

template<class _RI, class T>
void reverse(_RI first, _RI last){
    while(first < last)
        iter_swap(first++, --last);
}

// 前向迭代器，无法--，无法<，只能迭代
template<class _FI>
void rotate(_FI first, _FI middle, _FI last){
    if(first == middle || middle == last)   return;
    _FI i = middle;
    while(true){
        iter_swap(first, i);
        ++first;
        if(first == middle){
            if(i == last)   return;
            middle = i;
        }
        else if(i == last)  return;
        i = middle;
    }
}

// BI，三次reverse
template<class _BI>
void rotate(_BI first, _BI middle, _BI last){
    if(first == middle || middle == last)   return;
    reverse(first, middle);
    reverse(middle, last);
    reverse(first, last);
}

template<class _RI>
void rotate(_RI first, _RI middle, _RI last){
    // 涉及数论知识，整体上类似于循环移位
}

int main(int argc, char** argv)
{
    

    return 0;
}
