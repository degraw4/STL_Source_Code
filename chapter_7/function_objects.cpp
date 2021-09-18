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
#include <stdexcept>

using namespace std;

template<class T>
class _function_object_test: public binary_function<T, T, T>{
public:
    T operator()(const T& x1, const T& x2){
        return x1 * x2;
    }
};

int main(int argc, char** argv)
{
    _function_object_test<int> a;
    cout << a(3, 4) << endl;
    typename _function_object_test<int>::first_argument_type f1 = 0;
    typename _function_object_test<int>::second_argument_type f2 = 0;
    typename _function_object_test<int>::result_type f3 = 0;

    return 0;
}
