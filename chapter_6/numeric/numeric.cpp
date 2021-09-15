#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <typeinfo>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <stdexcept>

using namespace std;

template<class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init){
    for(; first != last; ++first)
        init = init + *first;
    return init;
}

template<class InputIterator, class T, class BinaryOp>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOp op){
    for(; first != last; ++first)
        init = op(init, *first);    // 将默认的加法改为其余的二元操作符
    return init;
}

template<class ForwardInterator>
void adjacent_difference(ForwardInterator first, ForwardInterator last){
    if(first == last)   return;
    typename iterator_traits<ForwardInterator>::value_type value = *first;   // 使用迭代器的traits提取其元素类型
    while(++first != last){ // 对于从第二个开始遍历的，用 while(++first != last)
        typename ForwardInterator::value_type tmp = *first;
        *first = tmp - value;
        value = tmp;
    }
}

template<class ForwardInterator, class BinaryOp>
void adjacent_difference(ForwardInterator first, ForwardInterator last, BinaryOp op){
    if(first == last)   return;
    typename iterator_traits<ForwardInterator>::value_type value = *first;
    while(++first != last){ 
        typename ForwardInterator::value_type tmp = *first;
        *first = op(first, value);    // 将默认的减法改为其余的二元操作符
        value = tmp;
    }
}

template<class ForwardInterator>
void partial_sum(ForwardInterator first, ForwardInterator last){
    if(first == last)   return;
    typename iterator_traits<ForwardInterator>::value_type value = *first;
    while(++first != last){
        *first = *first + value;
        value = *first;
    }
}

template<class ForwardInterator, class BinaryOp>
void partial_sum(ForwardInterator first, ForwardInterator last, BinaryOp op){
    if(first == last)   return;
    typename iterator_traits<ForwardInterator>::value_type value = *first;
    while(++first != last){
        *first = op(first, value); 
        value = *first;
    }
}



int main(int argc, char** argv)
{
    vector<int> vec{1,2,3,4,5};
    adjacent_difference(vec.begin(), vec.end());
    for(auto iter: vec)
        cout << iter << " ";
    cout << endl;

    partial_sum(vec.begin(), vec.end());
    for(auto iter: vec)
        cout << iter << " ";
    cout << endl;

    return 0;
}
