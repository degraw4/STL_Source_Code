#ifndef __LIST
#define __LIST
#include "head.h"

using namespace std;

// list部分实现


// list 节点
template<class T>
class __list_node{
public:
    __list_node<T>* prev;
    __list_node<T>* next;
    T data;
};

//  list iterator，相当于对指向list节点的指针做了封装
template<class T, class Ref, class Ptr>
class __list_iterator{
public:
    typedef __list_iterator<T, T&, T*>      iterator;
    typedef __list_iterator<T, Ref, Ptr>    self;

    typedef T               value_type;
    typedef Ptr             pointer;
    typedef Ref             reference;
    typedef __list_node<T>*  link_type;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

    link_type node;

    __list_iterator() {}
    __list_iterator(link_type x): node(x) {}
    __list_iterator(const iterator& x): node(x.node) {}

    bool operator==(const self& x) const {
        return node == x.node;
    }
    bool operator!=(const self& x) const {
        return node != x.node;
    }

    reference operator*() const {
        return (*node).data;
    }
    pointer operator->() const {
        return &(this->operator*());
    }

    self& operator++(){
        node = (*node).next;
        return *this;
    }
    self operator++(int){
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--(){
        node = (*node).prev;
        return *this;
    }
    self operator--(int){
        self tmp = *this;
        --*this;
        return tmp;
    }
};

// list，最重要的数据成员为指向尾后空节点的指针node
template<class T, class Alloc = alloc>
class list{

protected:
    typedef __list_node<T>              list_node;
    typedef __list_iterator<T, T&, T*>  iterator;
    typedef sample_alloc<T, Alloc>      list_allocator;

public:
    typedef list_node* link_type;

protected:
    link_type node; // 指向尾后空节点

public:
    iterator begin() { return (*node).next; }
    iterator end() { return node; }
    bool empty() const { return node->next == node; }
    size_t size() { return 10; /*To be continued...*/ }

    // begin or back
    T& front() { return begin().node.data; }
    T& back() { return *(end()--); }

protected:
    link_type get_node(){
        return list_allocator::allocate();
    }
    void put_node(link_type p){
        list_allocator::deallocate(p);
    }
    link_type create_node(const T& x){
        link_type p =get_node();
        construct(&(p->data), x); // warning
        return p;
    }
    void destory_node(link_type p){
        destroy(&(p->data));
        put_node(p);
    }

    // 构造空白list
    void empty_initialize(){
        node = get_node();
        node->next = node;
        node->prev = node;
    }

public:
    list(){ empty_initialize(); }

    iterator insert(iterator position, const T& x){
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        position.node->prev->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }
    iterator erase(iterator position){
        link_type prev_node = position.node->prev;
        link_type next_node = position.node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destory_node(position);
        return iterator(next_node);
    }

    void push_front(const T& x){
        insert(begin(), x);
    }
    void push_back(const T& x){
        insert(end(), x);
    }
    void pop_front(){
        erase(begin());
    }
    void pop_back(){
        iterator tmp = end();
        erase(--tmp);
    }

    void clear(){   // link_type
        link_type cur = node->next; // begin()
        while(cur != node){
            link_type tmp = cur;
            cur = cur->next;
            destory_node(tmp);
        }
        node->next = node;  // 置空
        node->next = node;
    }
    void remove(const T& x){    // iterator
        iterator first = begin();
        iterator last = end();
        while(first != last){
            iterator tmp = first++;
            if(*tmp == x)   erase(tmp);
        }
    }
    void unique(){
        iterator first = begin();
        iterator last = end();
        if(first == last)   return;
        iterator next = first;
        while(++next != last){
            if(*first == *next){
                erase(next);
                next = first;
            }
            else
                first = next;
        }
    }

    void transfer(iterator position, iterator first, iterator last){
        if(position != last){
            last.node->prev = position.node;
            first.node->prev->next = last.node;
            position.node->prev->next = first.node;
            link_type tmp = position.node->prev;
            position.node->prev = last.node->prev;
            last.node->prev = first.node->prev;
            first.node->prev = tmp;
        }
    }

    void splice(iterator position, list& x){
        transfer(position, x.begin(), x.end());
    }
    void splice(iterator position, iterator i){
        iterator j = i;
        ++j;
        if(position == i || position == j)  return;
        transfer(position, i, j);
    }

    void merge(list& x){
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = x.begin();
        iterator last2 = x.end();

        while(first1 != last1 && first2 != last2){
            if(*first1 < *first2){
                ++first1;
            }else{
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            }
        }
        if(first2 != last2)
            transfer(last1, first2, last2);
    }

    void reverse(){
        if(node->next == node || node->next->next == node)  return;
        iterator first = begin();
        ++first;
        while(first != end()){
            iterator old = first;
            first++;
            transfer(begin(), old, first);
        }
    }

    void sort(){
        if(node->next == node || node->next->next == node)  return;
        list<T, Alloc> carry;
        list<T, Alloc> counter[64];
        int fill = 0;
        while(!empty()){
            carry.splice(carry.begin(), begin());
            int i = 0;
            while(i < fill && !counter[i].empty()){
                counter[i].merge(carry);
                swap(carry, counter[i++]);
            }
            swap(carry, counter[i]);
            if(i == fill) ++fill;
        }
        for(int i = 0; i < fill; i++){
            counter[i].merge(counter[i - 1]);
        }
        swap(*this, counter[fill - 1]);
    }
};

#endif