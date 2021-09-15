#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <typeinfo>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <stdexcept>

using namespace std;

// equal只判断first1到last1与first2到给定数目的元素值是否对应相等
// 如果第二序列元素多，多出的不考虑
// 如果第一序列元素多，函数行为未定义
// 必须保证第二序列对应范围有意义，其余无所谓
template<class InputIterator1, class InputIterator2>
bool Equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
    for(; first1 != last1; ++first1, ++first2)
        if(*first1 != *first2)   return false;
    return true;
}

template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value){ // 使用ForwardIterator而不是Output的原因：Output不支持==和！=
    for(; first != last; ++first)
        *first = value;
}

template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value){ // 使用OutputIterator且返回最后插入元素的尾后迭代器
    for(; n > 0; --n, ++first)
        *first = value;
    return first;
}

// 交换两个ForwardIterator所指的内容
template<class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 a, ForwardIterator2 b){
    typename iterator_traits<ForwardIterator1>::type_name tmp = *a;
    *a = *b;
    *b = tmp;

}

// 交换两个对象本身
template<class T>
void swap(T& a, T&b){
    T tmp = a;
    a = b;
    b = tmp;
}

// 序列2至少要和序列1一样多
template<class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
    while(first1 != last1 && *first1 == *first2){
        ++first1;
        ++first2;
    }
    return (first1, first2);
}

int main(int argc, char** argv)
{
    vector<int> vec1{1,2,3};
    vector<int> vec2{1,2,3};
    // 若想判断两个容器完全相等，必须考虑容器元素个数 (P.S. 也要考虑容器类型)
    if(vec1.size() == vec2.size() && Equal(vec1.begin(), vec1.end(), vec2.begin()))
        cout << "Equal" << endl;
    return 0;
}
