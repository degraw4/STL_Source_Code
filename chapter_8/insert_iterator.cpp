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
#include <functional>
#include <stdexcept>

using namespace std;

// back_insert_iterator
template<class Container>
class _back_insert_iterator{
protected:
    Container* container;   // 容器指针
public:
    typedef output_iterator_tag iterator_category;  // 类型是输出iter
    // typedef void other_type

    explicit _back_insert_iterator(Container &c): container(&c) {}

    // 将赋值运算=转换为容器的插入操作
    _back_insert_iterator& operator=(const typename Container::value_type& x){
        container->push_back(x);
        return *this;
    }
};

// 函数_back_inserter封装了_back_insert_iterator，便于使用
template<class Container>
_back_insert_iterator<Container> _back_inserter(Container& c){
    return _back_insert_iterator<Container>(c);
}

// _insert_iterator
template<class Container>
class _insert_iterator{
protected:
    Container* container;   // 容器指针
    typename Container::iterator iter;  // 插入位置的iter
public:
    typedef output_iterator_tag iterator_category;  // 类型是输出iter
    // typedef void other_type

    explicit _insert_iterator(Container &c, typename Container::iterator i): container(&c), iter(i) {}

    // 将赋值运算=转换为容器的插入操作
    _insert_iterator& operator=(const typename Container::value_type& x){
        // 在本位置插入后，iter也随之++
        iter = container->insert(iter, x);
        ++iter;
        return *this;
    }
};

template<class Container, class Iterator>
_insert_iterator<Container> _inserter(Container& c, Iterator i){
    typedef typename Container::iterator iter;
    return _back_insert_iterator<Container>(c, iter(i));
}

int main(int argc, char** argv)
{
    vector<int> vec;
    back_insert_iterator<vector<int>> i(vec);

    return 0;
}
