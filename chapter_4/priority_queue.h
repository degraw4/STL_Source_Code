#ifndef __PRIORITY_QUEUE
#define __PRIORITY_QUEUE
#include <functional>
#include "heap.h"

using namespace std;

template<class T, class Sequence = vector<T>>
class priority_queue{
protected:
    Sequence c;
public:
    template<class InputIterator>
    priority_queue(InputIterator first, InputIterator last): c(first, last) {
        make_heap(c.begin(), c.end());
    }

    bool empty() const { return c.empty(); }
    size_t size() const { return c.size(); }
    T& top() { return c.front(); }

    void push(const T& x){
        c.push_back(x);
        push_heap(c.begin(), c.end());
    }
    void pop(){
        pop_heap(c.begin(), c.end());
        c.pop_back();
    }
};

#endif
