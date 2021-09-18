#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <typeinfo>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <functional>
#include <stdexcept>

using namespace std;

template<class Iterator>
class reverse_iterator{
protected:
    Iterator current;   // 正向迭代器
public:
    typedef Iterator iterator;
    typedef reverse_iterator<Iterator> self;

    reverse_iterator(){}
    reverse_iterator(Iterator iter): current(iter) {}
    reverse_iterator(const self& x): current(x.current) {}

    iterator base() const { return current; } // 返回正向迭代器

    typename iterator_traits<Iterator>::reference
    operator*() const {    // 正向迭代器--后对应反向迭代器
        auto tmp = current;
        return *--current;
    }

    self& operator++(){ //逆向++为正向--
        --current;
        return *this;
    }
    self operator++(int){
        auto tmp = *this;
        --current;
        return tmp;
    }

    self& operator--(){ 
        ++current;
        return *this;
    }
    self operator--(int){
        auto tmp = *this;
        ++current;
        return tmp;
    }

    self operator+(size_t n) const{
        return self(current - n);
    }
    self& operator+=(size_t n) {
        current -= n;
        return *this;
    }
    
    self operator-(size_t n) const{
        return self(current + n);
    }
    self& operator-=(size_t n) {
        current += n;
        return *this;
    }

    typename iterator_traits<Iterator>::reference
    operator[](size_t n) const {
        return *(*this + n);
    }
};

int main(int argc, char** argv)
{
    

    return 0;
}
