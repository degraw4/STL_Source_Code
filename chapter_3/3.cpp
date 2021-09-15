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

using namespace std;

// 设计自己的类及其特例化的__type_traits

class Base{ };

struct __true_type_degraw { };
struct __false_type_degraw { };

// __type_traits
template<class T>
struct __type_traits{
    typedef __false_type_degraw    has_trival_default_constructor;
    typedef __false_type_degraw    has_trival_copy_constructor;
    typedef __false_type_degraw    has_trival_assign_operator;
    typedef __false_type_degraw    has_trival_destructor;
    typedef __false_type_degraw    is_POD_type;
};

// 特例化
template<>
struct __type_traits<Base>{
    typedef __false_type_degraw    has_trival_default_constructor;
    typedef __false_type_degraw    has_trival_copy_constructor;
    typedef __false_type_degraw    has_trival_assign_operator;
    typedef __false_type_degraw    has_trival_destructor;
    typedef __false_type_degraw    is_POD_type;
};



int main(int argc, char** argv)
{
    

    return 0;
}
