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



int main(int argc, char** argv)
{
    ostream_iterator<int> out(cout, " ");
    vector<int>vec{0, 1, 2, 3, 4, 5};

    //for_each(vec.begin(), vec.end(), compose1(bind2nd(multiplies<int>(), 3), bind2nd(plus<int>(), 2)));
    // c++ standard has no compose1?
    
    return 0;
}
