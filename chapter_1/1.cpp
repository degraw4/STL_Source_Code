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

// 只有const成员才能有类内初始值
class A{
    const int a = 0;
    //static int b = 0;
    const static int c = 0;
    static const int b = 0;
};

// 刻意制造临时对象
// 类对()进行了重载，变成了仿函数functor
template<typename T> class print_class{
public:
    void operator() (const T& ele){
        cout << ele << endl;
    }
};

template<typename T> void print_function(const T& ele){
    cout << ele << endl;
}


int main(int argc, char** argv)
{
    vector<int> vec{1,2,3,4,5};
    // 通过类名后面跟()来调用构造函数产生临时对象
    cout << "class:\n";
    for_each(vec.begin(), vec.end(), print_class<int>());
    // 若是传入可调用对象，只传名字，不传括号()，传入后for_each会自动调用()来处理iter
    cout << "function:\n";
    for_each(vec.begin(), vec.end(), print_function<int>);

    return 0;
}
