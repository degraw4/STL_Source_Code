#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <stdexcept>

using namespace std;

// traits
// 简单的提取iter的value_type的traits

template<typename T>
class iter{
public:
    // 声明类型内嵌 
    typedef T value_type;
    T* ptr;
    iter(T* p = 0): ptr(p) {}
    T& operator*() { return *ptr; }
    // ...
};

template<class Iter>
class iter_traits{
public:
    typedef typename Iter::value_type value_type;
};

// iter_traits针对内置指针及其const做的特例化
template<typename T>
class iter_traits<T*>{
public:
    typedef T value_type;
};

template<typename T>
class iter_traits<const T*>{
public:
    typedef T value_type;
};

// 通过函数模板以及iter_traits萃取出iter的value_type
template<typename I>
typename iter_traits<I>::value_type func(I i){
    return *i;
}


int main(int argc, char** argv)
{
    iter<int> i1;
    iter<string> i2;
    iter<vector<string>> i3;
    int* p1;
    vector<string>* p2;
    const double* p3;

    auto a1 = func(i1);
    auto a2 = func(i2);
    auto a3 = func(i3);

    typename iter_traits<int*>::value_type a;
    typename iter_traits<vector<string>*>::value_type b;
    typename iter_traits<const double*>::value_type c;

    // auto a4 = func(p1);
    // auto a5 = func(p2);
    // auto a6 = func(p3);

    return 0;
}
