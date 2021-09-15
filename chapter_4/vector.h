#ifndef __VECTOR
#define __VECTOR
#include "head.h"

using namespace std;

// vector部分实现

// vector内部最重要的数据成员：start, finish, end_of_storage

template<class T, class Alloc = alloc>
class vector{

public:
    typedef T               value_type;
    typedef value_type*     pointer;
    typedef value_type*     iterator;
    typedef value_type&     reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

protected:
    typedef sample_alloc<value_type, Alloc> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;

    void insert_aux(iterator position, const T& value);

    void deallocate(){
        if(start){
            data_allocator::deallocate(start, end_of_storage - start);
        }
    }
    void fill_initialize(size_type n, const T& value){
        start = allocate_and_fill(n, value);
        finish = end_of_storage = start + n;
    }

    iterator allocate_and_fill(size_type n, const T& value){
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, value);
        return result;
    }

public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() const { return size_type(start - finish); }
    size_type capacity() const { return size_type(end_of_storage - start); }
    bool empty() { return start == finish; }
    reference operator[] (size_type n) { return *(start + n); }

    vector(): start(0), finish(0), end_of_storage(0) {}
    vector(size_type n, const T& value) { fill_initialize(n, value); }
    ~vector(){
        destory(start, finish);
        deallocate();
    }

    reference front() { return *begin(); }
    reference back() { return *(end() - 1); }

    void push_back(const T& value){
        if(finish != end_of_storage){
            construct(finish, value);
            ++finish;
        }else{
            insert_aux(finish, value);
        }
    }

    void pop_back(){
        if(!empty()){
            --finish;
            destory(finish);
        }
    }

    void insert(iterator position, const T& value){
        insert_aux(position, value);
    }

    void insert(iterator position, size_type n, const T& value);

    iterator erase(iterator position){
        if(position != end() - 1){
            copy(position + 1, finish, position);
        }
        --finish;
        destroy(finish);
        return position;
    }

    iterator erase(iterator first, iterator last){
        iterator i = copy(last, finish, first);
        destory(i, finish);
        finish = finish - (last -first);
        return first;
    }

    void resize(size_type new_sz, const T& value = 0){
        if(new_sz < size()){
            erase(begin() + new_sz, finish);
        }else{
            insert(finish, new_sz - size(), value);
        }
    }

    void clear(){
        erase(start, finish);
    }

};

template<class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& value){
    if(finish !=  end_of_storage){
        construct(finish, *(finish - 1));
        ++finish,
        copy_backward(position, finish - 2, finish - 1);
        *position = value;
    }else{
        const size_type old_sz = size();
        const size_type new_sz = old_sz == 0 ? 1 : 2 * old_sz;
        iterator new_start = data_allocator::allocate(new_sz); // 本身就有异常处理
        iterator new_finish = new_start;
        try{
            new_finish = uninitialized_copy(start, position, start);
            construct(position, value);
            ++new_finish;
            new_finish = uninitialized_copy(position, finish, new_finish);
        }catch(...){
            /*commit or rollback*/
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, new_sz);
            throw;
        }
        destory(start, finish);
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + new_sz;
    }
}

template<class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T& value){
    if(n != 0){
        if(end_of_storage - finish >= n){   // 空间足够
            size_type after = finish - position;
            iterator old_finish = finish;
            if(after > n){  // 插入位置之后的元素多
                uninitialized_copy(finish - n, finish, finish);
                finish += n;
                copy_backward(position, old_finish - n, old_finish);
                fill(position, position + n, value);
            }else{  // 插入的元素多
                uninitialized_fill_n(finish, n - after, value);
                finish += n - after;
                uninitialized_copy(position, old_finish, finish);
                finish += after;
                fill(position, old_finish, value);
            }
        }else{  // 空间不足
            const size_type old_sz = size();
            const size_type new_sz = old_sz + max(old_sz, n);
            iterator new_start = data_allocator::allocate(new_sz);
            iterator new_finish = new_start;
            try{
                new_finish = uninitialized_copy(start, position, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, value);
                new_finish = uninitialized_copy(position, finish, new_finish);
            }catch(...){
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_sz);
                throw;
            }
            destory(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + new_sz;
        }
    }
}

#endif