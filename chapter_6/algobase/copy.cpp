#include "copy.h"

using namespace std;

// copy唯一对外接口
template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
    return __copy_dispatch(first, last, result);
}

// 两个重载的版本
char* copy(const char* first, const char* last, char* result){
    memmove(result, first, last - first);
    return result + (last - first);
}

wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result){
    memmove(result, first, last - first);
    return result + (last - first);
}

// dispatch判断迭代器类型
template<class InputIterator, class OutputIterator>
OutputIterator __copy_dispatch(InputIterator first, InputIterator last, OutputIterator result){
    return __copy(first, last, result, __iterator_category(first));
}

// input_iterator版本
template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag){
    for(; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// random_access_iterator版本
template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, random_access_iterator_tag){
    return __copy_d(first, last, result, __distance(first));
}

template<class RandomAccessIterator, class OutputIterator, class Distance>
OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*){
    for(Distance n = last - first; n > 0; --n, ++result, ++first)
        *result = *first;
    return result;
}

// dispatch的两个特例化
template<class T>
T* __copy_dispatch(T* first, T* last, T* result){
    typedef typename __type_traits<T>::has_trivial_assignment_operator t;   // t是类型，t()是临时变量
    return __copy_t(first, last, result, t());
}

template<class T>
T* __copy_dispatch(const T* first, const T* last, T* result){
    typedef typename __type_traits<T>::has_trivial_assignment_operator t;
    return __copy_t(first, last, result, t());
}

template<class T>
T* __copy_t(const T* first, const T* last, T* result, __true_type){
    memmove(result, first, sizeof(T) * (last - first));
    return result + last - first;
}

template<class T>
T* __copy_t(const T* first, const T* last, T* result, __false_type){
    return __copy_d(first, last, result, (ptrdiff_t*)0);
}

int main(int argc, char** argv)
{
     

    return 0;
}
