#ifndef __STACK
#define __STACK
#include "deque.h"

using namespace std;

// stack底层容器默认是deque
// 含有empty, size, back, push_back, pop_back操作的容器都可以当作stack的底层容器
// stack无迭代器

template<class T, class Sequence = deque<T> >
class stack{

protected:
    Sequence c; // 底层容器

public:
    stack() = default;
    ~stack() = default;
    /* ... */

    bool empty() { return c.empty(); }
    size_t size() { return c.size(); }
    T& top() { return c.back(); }
    const T& top() const { return c.back(); }

    void push(const T& x) { c.push_back(x); }
    void pop() { c.pop_back(); }

};

#endif
