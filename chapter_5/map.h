#ifndef __MAP_H
#define __MAP_H
#include <iostream>
#include <utility>
#include "rb-tree.h"

using namespace std;

template<class Key, class T, class Alloc = alloc>
class map{
public:
    typedef Key key_type;
    typedef T mapped_type;
    // pair的first为const，防止修改map的键值
    typedef pair<const Key, T> value_type;

private:
    typedef rb_tree<key_type, value_type, Alloc> tree_type;
    tree_type tree;

public:
    typedef typename tree_type::iterator iterator;
    typedef typename tree_type::const_iterator const_iterator;

public:
    // map的下标运算符，接收的参数是const的key，返回T的引用，使其可以作为左值或者右值
    // 先插入k和临时对象T()组成的pair，得到插入的iter，返回其指向的second
    T& operator[](const key_type& k){
        return *(tree.insert(value_type(k, T())).first).second;
    }

    // map插入的形参为pair
    pair<iterator, bool> insert(const value_type& x){
        return tree.insert(x);
    }
};

#endif