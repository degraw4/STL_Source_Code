#ifndef __HEAD
#define __HEAD
#include <iostream>
#include <cstdio>
#include <memory>
#include <new>
#include <stdexcept>
#include <cstddef>
#include <algorithm>

using namespace std;

template<class T1, class T2>
inline void construct(T1* p, const T2& value){
    new (p) (T1)(value);
}
template<class T>
inline void destroy(T* ptr){
    ptr->~T();
}

template<int ints>
class __malloc_alloc_template{

private:
    // oom: out of memory
    static void* oom_malloc(size_t);
    static void* oom_realloc(void*, size_t);
    static void (*__malloc_alloc_oom_handler)();

public:
    static void* allocate(size_t n){
        void* result = malloc(n);
        if(0 == result){
            result = oom_malloc(n);
        }
        return result;
    }

    static void deallocate(void* p, size_t /* n */){
        free(p);
    }

    static void* reallocate(void* p, size_t /* old_sz */, size_t new_sz){
        void* result = realloc(p, new_sz);
        if(0 == result){
            result = oom_realloc(p, new_sz);
        }
        return result;
    }

    // 指定自己的set_malloc_handler()
    // 此函数接受一个函数指针作为形参，返回一个函数指针
    static void (*set_malloc_handler(void (*f)())) (){
        void (*old)() = __malloc_alloc_oom_handler();
        __malloc_alloc_oom_handler() = f;
        return old;
    }

};

// 静态函数指针成员的类外定义：类名加在*后和函数指针名字前，且带有模板实参
template<int ints>
void (* __malloc_alloc_template<ints>::__malloc_alloc_oom_handler)() = 0;

template<int ints>
void* __malloc_alloc_template<ints>::oom_malloc(size_t n){
    void (*my_malloc_handler)();
    void* result;
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(0 == my_malloc_handler) { throw bad_alloc(); }
        (*my_malloc_handler)(); // 调用处理函数
        result = malloc(n);     // 再次尝试分配内存
        if(result)  return result;
    }
}

template<int ints>
void* __malloc_alloc_template<ints>::oom_realloc(void* p, size_t n){
    void (*my_malloc_handler)();
    void* result;
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(0 == my_malloc_handler) { throw bad_alloc(); }
        (*my_malloc_handler)();     // 调用处理函数
        result = realloc(p, n);     // 再次尝试分配内存
        if(result)  return result;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;

template<class T, class Alloc = alloc>
class sample_alloc{
public:
    static T* allocate(size_t n){
        return n == 0 ? 0 : (T*)Alloc::allocate(n * sizeof(T));
    }
    static T* allocate(void){
        return (T*)Alloc::allocate(sizeof(T));
    }
    static void deallocate(T* p, size_t n){
        if(0 != n)  Alloc::deallocate(p, n * sizeof(T));
    }
    static void deallocate(T* p){
            Alloc::deallocate(p, sizeof(T));
    }
};

#endif
