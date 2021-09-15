#ifndef __SET_H
#define __SET_H
#include <iostream>
#include "rb-tree.h"

using namespace std;

template<class Key, class Alloc = alloc>
class set{
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef rb_tree<key_type, value_type, Alloc> rb_tree_type;

private:
    rb_tree_type tree;

public:
    // 在底层将rb-tree的const iterator设为set的iterator，杜绝的使用iterator更改set元素的可能
    typedef typename rb_tree_type::const_iterator iterator;

    // set的操作，底层都是在调用rb-tree相应的操作
    // 区别：插入时，set调用rb-tree的insert_unique
    // multiset调用rb-tree的insert_equal
    iterator begin() const { return tree.begin(); }
    iterator end() const { return tree.end(); }
    pair<iterator, bool> insert(const Key& x){
        return tree.insert_unique(x);
    }
};

#endif
