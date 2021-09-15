#ifndef __RB_TREE
#define __RB_TREE
#include "head.h"

using namespace std;

typedef bool rb_tree_color;
rb_tree_color red = false;
rb_tree_color black = true;

// RB-Tree节点
template<class T>
class rb_tree_node{
public:
    rb_tree_color color;
    rb_tree_node<T>* parent;
    rb_tree_node<T>* left;
    rb_tree_node<T>* right;
    T value;
};

// RB-Tree iter
template<class T>
class rb_tree_iterator{
public:
    typedef rb_tree_iterator<T> iterator;
    typedef const rb_tree_iterator<T> const_iterator;

    rb_tree_node<T>* node;

    rb_tree_iterator() {}
    rb_tree_iterator(rb_tree_node<T>* x): node(x) {}
    rb_tree_iterator(const rb_tree_iterator<T>& it): node(it.node) {}

    rb_tree_iterator<T>& operator++(){
        if(node->right != 0){
            node = node->right;
            while(node->left != 0)
                node = node -> left;
        }
        else{
            rb_tree_node<T>* parent = node->parent;
            while(node = parent->right){
                node = parent;
                parent = node->parent;
            }
            // 防止寻找root的++，且root无右节点
            if(node->right != parent){
                node = parent;
            }
        }
    }
    rb_tree_iterator<T> operator++(int){
        auto tmp = *this;
        operator++();
        return tmp;
    }

    rb_tree_iterator<T>& operator--(){
        // node为header
        if(node->color == red && node->parent->parent == node)
            node = node->right;
        if(node->left != 0){
            node = node->left;
            while(node->right != 0)
                node = node->right;
        }
        else{
            rb_tree_node<T>* parent = node->parent;
            while(node = parent->leaf){
                node = parent;
                parent = node->parent;
            }
            node = parent;
        }
    }
    rb_tree_iterator<T> operator--(int){
        auto tmp = *this;
        operator--();
        return tmp;
    }

    T& operator*(){ return node->value; }
    T* operator->(){ return &(operator*()); }

    bool operator==(const rb_tree_iterator<T>& it){
        return node == it.node;
    }
    bool operator!=(const rb_tree_iterator<T>& it){
        return node != it.node;
    }

};

// RB-Tree
// rb-tree的节点存放的数据是Value类型的，但是进行比较的时候使用的是Key类型
// rb-tree没有为每个节点单独存放Key，而是定义了一个仿函数KeyOfValue，可以根据每个节点的Value提取出Key
// 对于set，可以设定rb-tree的Value为int，Key和Value一致
// 对于map，可以设置rb-tree的Value为pair，Key为pair.first
template<class Key, class Value, class Alloc = alloc>
class rb_tree{
protected:
    typedef rb_tree_node<Value>* link_type;
    typedef sample_alloc<rb_tree_node<Value>, Alloc> rb_tree_node_allocator;
    typedef Value value_type;
    typedef Value* pointer;
    typedef Value& conference;

public:
    typedef rb_tree_iterator<Value> iterator;

protected:
    link_type get_node() { return rb_tree_node_allocator::allocate(); }
    void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }

    link_type create_node(const Value& x){
        link_type tmp = get_node();
        construct(&(tmp->value), x);
        return tmp;
    }
    void destory_node(link_type p){
        destroy(&p->value);
        put_node(p);
    }

    static link_type min_node(link_type root){
        while(root->left != 0)
            root = root->left;
        return root;
    }
    static link_type max_node(link_type root){
        while(root->right != 0)
            root = root->right;
        return root;
    }

protected:
    size_t node_count;
    link_type header;

protected:
    link_type& root() const { return header->parent; }
    link_type& mostleft() const { return header->left; }
    link_type& mostright() const { return header->right; }

    static link_type& left(link_type x) { return x->left; }
    static link_type& right(link_type x) { return x->right; }
    static link_type& parent(link_type x) { return x->parent; }
    static Value& value(link_type x) { return x->value; }
    static rb_tree_color& color(link_type x) { return x->color; }

private:
    void init(){
        header = get_node();
        color(header) = red;

        root() = 0;
        mostleft() = header;
        mostright() = header;
    }

    void clear(){
        for(auto iter = begin(); iter != end(); iter++)
            destory_node(iter.node);
    }

    void __rb_tree_left_rotate(link_type x){
        link_type y = x->right;
        x->right = y->left;
        if(y->left) // 设置父节点
            y->left->parent = x;
        y->left = x;
        if(x == root())
            root() = y;
        else if(x = x->parent->left){
            x->parent->left = y;
        }
        else
            x->parent->right = y;
        x->parent = y;
    }

    void __rb_tree_right_rotate(link_type x){
        link_type y = x->left;
        x->left = y->right;
        if(y->right) // 设置父节点
            y->right->parent = x;
        y->right = x;
        if(x == root())
            root() = y;
        else if(x = x->parent->right){
            x->parent->right = y;
        }
        else
            x->parent->left = y;
        x->parent = y;
    }

    // x作为新插入的节点
    void __rb_tree_rebalance(link_type x){
        x->color = red;
        //当x不为根节点且其父节点为红色
        while(x != root() && x->parent->color == red){
            if(x->parent == x->parent->parent->left){   // 父节点为左子节点
                link_type y = x->parent->parent->right;
                if(y && y->color == red){   // case 3: 伯父节点为红
                    x->parent->color = black;
                    y->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
                }
                else{// 无伯父节点或父节点为黑
                    if(x == x->parent->right){   // case 2: 双旋
                        x = x->parent;
                        __rb_tree_left_rotate(x);// 此时x已经被旋转了下去
                    }
                    // case 1: 单旋+改颜色
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    __rb_tree_right_rotate(x->parent->parent);
                }
            }
            else{   // left和right互换
                link_type y = x->parent->parent->left;
                if(y && y->color == red){   // case 3: 伯父节点为红
                    x->parent->color = black;
                    y->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
                }
                else{// 无伯父节点或父节点为黑
                    if(x == x->parent->left){   // case 2: 双旋
                        x = x->parent;
                        __rb_tree_right_rotate(x);// 此时x已经被旋转了下去
                    }
                    // case 1: 单旋+改颜色
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    __rb_tree_left_rotate(x->parent->parent);
                }
            }   
        }
    }

    // x为插入点，必为null
    iterator __insert(link_type x, link_type y, const Value& v){
        link_type z = create_node(v);
        // 空树
        if(y == header){
            root() = z;
            mostleft() = z;
            mostright() = z;
        }
        else if(v < y->value){
            left(y) = z;
            if(y == mostleft())
                mostleft() = z;
        }
        else{
            right(y) = z;
            if(y == mostright())
                mostright() = z;
        }
        parent(z) = y;
        left(z) = 0;
        right(z) = 0;
        ++node_count;
        __rb_tree_rebalance(z);
        return iterator(z);
    }

public:
    rb_tree(): node_count(0) { init(); }
    ~rb_tree(){
        clear();
        put_node(header);
    }

    iterator begin() { return mostleft(); }
    iterator end() { return header; }
    bool empty() const { return node_count == 0; }
    bool size() const { return node_count; }

    iterator insert_equal(const Value& v){
        link_type y = header;
        link_type x = root();
        while(x != 0){
            y = x;
            x = (v > x->value) ? right(x) : left(x);
        }
        return __insert(x, y, v);
    }

    pair<iterator, bool> insert_unique(const Value& v){
        link_type y = header;
        link_type x = root();
        // ... 
        return pair<iterator, bool>(__insert(x, y, v), true);
    }

};

#endif
