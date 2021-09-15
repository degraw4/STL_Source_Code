#include <iostream>
#include "heap.h"

using namespace std;

int main(){
    vector<int> vec{4,2,7,5,3,8,0,1};
    make_heap(vec.begin(), vec.end());
    for(auto iter: vec){
        cout << iter << " ";
    }
    cout << endl;

    vec.push_back(10);
    push_heap(vec.begin(), vec.end());
    for(auto iter: vec){
        cout << iter << " ";
    }
    cout << endl;

    pop_heap(vec.begin(), vec.end());
    for(auto iter: vec){
        cout << iter << " ";
    }
    cout << endl;
    vec.pop_back();
    
    sort_heap(vec.begin(), vec.end());
    for(auto iter: vec){
        cout << iter << " ";
    }
    cout << endl;
}