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

// 交集
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
        }
        else if(*first1 > *first2){
            *result = *first2;
            ++first2;
        }
        else{   // 对于重复值，在相等的情况下，只记录一次，两个iter都++
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }            
    return copy(first2, last2, copy(first1, last1, result));             
}

// 并集
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2)   ++first1;
        else if(*first1 > *first2)  ++first2;
        else{
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }            
    return result;             
}

// 差集
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result){
    while(first1 != last1 && first2 != last2){  // 求S1-S2，只把S1的小的记录
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first1 > *first2){
            ++first2;
        }
        else{
            ++first1;
            ++first2;
        }
    }
    return copy(first1, last1, result);
}

// 对称差集
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result){
    while(first1 != last1 && first2 != last2){  // 记录S1和S2的小的
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first1 > *first2){
            *result = *first2;
            ++first2;
            ++result;
        }
        else{
            ++first1;
            ++first2;
        }
    }     
    return copy(first2, last2, copy(first1, last1, result));                          
}


int main(int argc, char** argv)
{
    

    return 0;
}
