#ifndef __DEQUE
#define __DEQUE
#include "head.h"

using namespace std;

// deque部分实现

// iterator
template<class T, class Alloc = alloc>
class __deque_iterator{
public:
    T* cur;
    T* first;
    T* last;
    T** node;

    void set_node(T** new_node){
        // 将当前的迭代器转移到new_node所指的缓冲区上
    }
};

template<class T, class Alloc = alloc>
class deque{
public:
    typedef __deque_iterator<T, Alloc>  iterator;
    typedef sample_alloc<T, Alloc>      value_allocator;
    typedef sample_alloc<T*, Alloc>     map_allocator;

    T** map; // 指向中控器map的起始点
    size_t map_size;
    iterator start;     // deque首元素iter
    iterator finish;    // deque尾元素尾后iter

    bool empty() { return true; }
    size_t size() { return 10; }

    T& front() { return *start; }
    T& back() { return *(finish - 1); }

    deque(){
        /*
        先分配map的空间，从map空间的中间选取nstart和nfinish
        对nstart和nfinish之间的map分配缓冲区
        设定start和finish迭代器
        为缓冲区uninitialized_fill赋初值
        */
    }

    void push_back(const T& x){
        /*
        不在缓冲区最后push，直接构造
        在缓冲区最后，构造完成后，查看后面有没有多余的map节点
        有则指向新分配的缓冲区，调整deque的迭代器
        没有则调用reallocate_map
        */
    }

    void push_front(const T& x){}

    void reallocate_map(size_t n){
        /*
        当头/尾没有足够的map空间时，先看整体map空间够不够
        够的话copy/copy_backwards到中间来，调整deque的迭代器
        不够就从新分配，copy，析构旧的，调整deque的迭代器
        */
    }

    void pop_back(){
        /*
        要pop的不是该缓冲区的唯一一个，直接析构
        是唯一一个，则调整deque的迭代器，释放旧的缓冲区
        */
    }

    void pop_front(){}

    void clear(){
        /*
        clear后留一个空的缓冲区
        先将第一个map之后和最后一个map之前之间的缓冲区释放
        剩下的首尾若为一个，析构元素
        若为两个，只析构和释放一个，另一个只析构
        调整deque的迭代器
        */
    }

    void erase(iterator pos){
        /*
        pos之前的元素少，则前半部分copy_backwards后移一位，pop_front
        pos之后的元素少，则后半部分copy前移一位，pop_back
        */
    }

    void erase(iterator first, iterator last){
        /*
        区间前方元素少，copy_backwards，析构，释放冗余缓冲区
        区间后方元素少，copy，析构，释放冗余缓冲区
        */
    }

    void insert(iterator pos){
        /*
        首尾插入，直接push
        中间插入，看前后元素的多少
        前方元素少，首端push首元素，中间元素向前copy，插入位置构造，调整deque的迭代器
        后方元素少，尾端push尾元素，中间元素向后copy_backwards，插入位置构造，调整deque的迭代器
        */
    }

};

#endif