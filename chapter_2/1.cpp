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
#include <cstddef>
#include <cstdlib>
#include <climits>

// SGI的标准空间配置器allocator，简单封装operator new和delete
// 对象的构造和析构由全集函数construct和destroy负责

// STL容器中用的是alloc，而不是allocator
// alloc分为一级和二级配置器，且不含construct和destroy成员函数

namespace degraw{
    template<class T>
    // 函数定义可以不写参数名字
    inline T* _allocate(ptrdiff_t size, T*){
        std::set_new_handler(0);
        T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
        if(tmp == 0){
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }
        return tmp;
    }

    template<class T>
    inline void _deallocate(T* buffer){
        ::operator delete(buffer);
    }

    // 模板类型可当构造函数和析构函数用
    // 以下两个函数未出现在allocator类中，allocator类使用的是全局函数
    template<class T1, class T2>
    inline void _construct(T1* p, const T2& value){
        new (p) T1(value);
    }

    template<class T>
    inline void _destory(T* ptr){
        ptr->~T();
    }

    template<class T>
    class allocator{
        //...
    };
}

static void (*set_malloc_handler(void (*f)())) (){

}

int main(int argc, char** argv)
{

    return 0;
}
