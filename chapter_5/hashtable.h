#ifndef __HASH_TABLE
#define __HASH_TABLE
#include <iostream>
#include <vector>
#include "head.h"

using namespace std;

template<class Value> class hashtable_node;
template<class Key, class Value, class Alloc = alloc> class hashtable_iterator;
template<class Key, class Value, class Alloc = alloc> class hashtable;

// hashtable_node
template<class Value> 
class hashtable_node{
    hashtable_node<Value>* next;
    Value data;
};

// hashtable_iterator
template<class Key, class Value, class Alloc = alloc> 
class hashtable_iterator{
public:
    typedef hashtable_node<Value> node;
    typedef hashtable_iterator<Key, Value> iterator;
    typedef hashtable<Key, Value> hashtable;

    node* ptr;  // 指向某一node
    hashtable* table;   // 保持迭代器对容器的连接关系

    hashtable_iterator(node* p, hashtable* h): ptr(p), table(h) {}

    Value& operator*() const { return ptr->data; }
    Value* operator->() const { return &(operator*()); }

    iterator& operator++(){
        node* old = ptr;
        ptr = ptr->next;
        if(!ptr){
            size_t bucket_num = table->bkt_num(old->data);
            while(!ptr && ++bucket_num < table->buckets.size()) // 寻找下一个不空的bucket
                ptr = table->buckets[bucket_num];
        }
        return *this;
    }
    iterator operator++(int){
        iterator tmp = this;
        ++*this;
        return tmp;
    }

    bool operator==(const iterator& it) const { return ptr == it.ptr; }
    bool operator!=(const iterator& it) const { return ptr != it.ptr; }
};

// hashtable
template<class Key, class Value, class Alloc = alloc> 
class hashtable{
private:
    typedef hashtable_node<Value> node;
    typedef hashtable_iterator<Key, Value> iterator;
    typedef sample_alloc<Value, Alloc> node_allocator;
    typedef hashtable<Key, Value, Alloc> hashtable;

    vector<node*, Alloc> buckets;
    size_t element_num;

private:
    node* new_node(const Value& v){
        node* tmp = node_allocator::allocate();
        tmp->next = 0;
        construct(&(tmp->data), v);
        return tmp;
    }

    void delete_node(node* p){
        destory(&(p->data));
        node_allocator::deallocate();
    }

    size_t bkt_num(const Value& v){
        // ...
        return 1;
    }

    void initialize_buckets(size_t n){
        buckets.reserve(n);
        element_num = 0;
        // 在end之前插入，且插入的元素为指针node*，不是node
        buckets.insert(backets.end(), n, (node*)0);
    }

    void clear(){
        for(auto i = 0; i < buckets.size(); ++i){
            node* cur = buckets[i];
            while(cur){
                node* next = cur->next;
                delete_node(cur);
                cur = next;
            }
            buckets[i] = 0; // 将vector内容设置为0
        }
        element_num = 0;
    }

    void resize(size_t n){
        size_t old_size = buckets.size();
        if(n > old_size){
            size_t new_size = max(n, old_size<<1);
            vector<node*, Alloc> tmp(new_size, (node*)0);
            for(size_t i = 0; i < old_size; ++i){
                node* first = buckets[i];
                while(first){
                    size_t index = bkt_num(first->data);
                    buckets[i] = first->next;
                    first->next = tmp[index];
                    tmp[index] = first;
                    first = buckets[i];
                }
            }
            buckets.swap(tmp);
        }
    }

    pair<iterator, bool> insert_unique_noresize(const Value& x){
        size_t index = bkt_num(x);
        node* first = buckets[index];
        // 只是遍历当前的list，插入还是在头上插
        for(node* cur = first; cur; cur = cur->next){
            if(cur->data == x)  return pair<iterator, bool>(iterator(cur, this), false);
        }
        node *tmp = new_node(x);
        tmp->next = first;
        buckets[index] = tmp;
        ++element_num;
        return pair<iterator, bool>(iterator(tmp, this), true);
    }

    iterator insert_equal_noresize(const Value& x){
        size_t index = bkt_num(x);
        node* first = buckets[index];
        node *tmp = new_node(x);
        for(node* cur = first; cur; cur = cur->next){
            // 发现相同的，在其后面插入，然后返回
            if(cur->data == x){
                tmp->next = cur->next;
                cur->next = tmp;
                ++element_num;
                return iterator(tmp, this);
            }
        }
        // 无相同的，头插
        tmp->next = first;
        buckets[index] = tmp;
        ++element_num;
        return iterator(tmp, this);
    }

public:
    hashtable() {}
    hashtable(size_t n) { initialize_buckets(n); }
    ~hashtable() { clear(); }

    size_t bucket_count() const { return buckets.size(); }
    size_t size() const { return element_num; }

    // 便于定义iterator
    iterator begin() const {
        if(!size()) return iterator(0, this);
        for(int i = 0; i < buckets.size(); i++){
            if(buckets[i])  return iterator(&(buckets[i]->data), this);
        }
    }
    iterator end() const { return iterator(0, this); }

    pair<iterator, bool> insert_unique(const Value& x){
        resize(element_num + 1);
        return insert_unique_noresize(x);
    }

    iterator insert_unique(){
        resize(element_num + 1);
        return insert_equal_noresize(x);
    }

    void copy_from(const hashtable& hash){
        buckets.clear();
        buckets.reserve(hash.bucket_count());
        buckets.insert(buckets.end(), hash.bucket_count(), (node*)0);
        element_num = hash.element_num;
        for(int i = 0; i < buckets.size(); ++i){
            // 赋值 + if判断
            if(const node* cur = hash.buckets[i]){  // 第一个
                node* copy = new_node(cur->data);
                buckets[i] = copy;
                for(node* next = cur->next; next; cur = next, next = cur->next){
                    copy->next = new_node(next->data);
                    copy = copy->next;
                }
            }
        }
    }

};

#endif
