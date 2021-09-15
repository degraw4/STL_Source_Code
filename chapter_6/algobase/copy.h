#ifndef __COPY_H
#define __COPY_H
#include <iostream>
#include <cstring>
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

char* copy(const char* first, const char* last, char* result);
wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result);

template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);

template<class InputIterator, class OutputIterator>
OutputIterator __copy_dispatch(InputIterator first, InputIterator last, OutputIterator result);

template<class T>
T* __copy_dispatch(T* first, T* last, T* result);

template<class T>
T* __copy_dispatch(const T* first, const T* last, T* result);

template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag);


template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, random_access_iterator_tag);

template<class RandomAccessIterator, class OutputIterator, class Distance>
OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*);

template<class T>
T* __copy_t(const T* first, const T* last, T* result, __true_type);

template<class T>
T* __copy_t(const T* first, const T* last, T* result, __false_type);

// copy_backward，将copy的方向改为反向，将last-1复制到result-1
// 迭代器必须是BidirectionalIterator才可以反向移动
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, 
                                     BidirectionalIterator2 result);

#endif
