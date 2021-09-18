#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>
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

int main(int argc, char** argv)
{
    ostream_iterator<int> out(cout, " ");
    vector<int>vec{0, 1, 2, 3, 4, 5};
    deque<int> deq(vec.begin(), vec.end());

    copy(deq.begin(), deq.end(), out);  // copy到ostream的迭代器中
    cout <<  endl;

    copy(vec.begin(), vec.begin() + 2, front_inserter(deq));    // front_inserter(deq)函数返回一个指向deq的front_insert_iterator
    copy(deq.begin(), deq.end(), out); 
    cout <<  endl;

    copy(deq.begin(), deq.begin() + 2, inserter(deq, deq.begin() + 5));    //  inserter)函数返回一个指向deq.begin() + 5的insert_iterator
    copy(deq.begin(), deq.end(), out); 
    cout <<  endl;

    copy(deq.rbegin(), deq.rend(), out);    // 反向迭代器
    cout <<  endl;

    istream_iterator<int> in(cin), eof;  // eof: ctrl +  d
    copy(in, eof, back_inserter(vec));
    copy(vec.begin(), vec.end(), out); 
    cout <<  endl;

    return 0;
}
