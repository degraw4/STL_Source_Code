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

template<class _RI, class T>
_RI _partition(_RI first, _RI last, T pivot){
    while(true){
        while(*first < pivot) ++first;
        --last;
        while(pivot < *last)  --last;
        if(!(first < last)) return first;
        iter_swap(first, last);
        ++first;
    }
}

int main(int argc, char** argv)
{
    vector<int> vec{2,4,1,7,8,3,0};
    cout << *_partition(vec.begin(), vec.end(), 2) << endl;
    for(auto i: vec)
        cout << i << " ";
    cout << endl;
    return 0;
}
