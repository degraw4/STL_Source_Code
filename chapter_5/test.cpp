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

int main(int argc, char** argv)
{
    multiset<int> mse{1,2,3,4,5,1};
    for(auto iter: mse)
        cout << iter << " ";
    cout << endl;
    cout << mse.count(1) << endl;

    multimap<string, int> mmp;
    mmp.insert({"a", 1});
    mmp.insert({"a", 2});
    mmp.insert({"b", 1});
    for(auto iter: mmp)
        cout << iter.first << " " << iter.second << endl;
    cout << mmp.count("a") << endl;
    return 0;
}
