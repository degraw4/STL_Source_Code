#ifndef __QUEUE
#define __QUEUE
#include "deque.h"

using namespace std;

// queue底层容器默认是deque
// 双向开口的容器都可以当作stack的底层容器，单向开口也可以编译通过，但是调用相关操作的编译时会报错
// queue无迭代器

template<class T, class Sequence = deque<T> >
class queue{

protected:
    Sequence c; // 底层容器

public:
    queue() = default;
    ~queue() = default;
    /* ... */

    bool empty() { return c.empty(); }
    size_t size() { return c.size(); }

    T& front() { return c.front(); }
    const T& front()const { return c.front(); }
    T& back() { return c.back(); }
    const T& back() const { return c.back(); }

    void push(const T& x) { c.push_back(x); }
    void pop() { c.pop_front(); }

};

#endif
