#include <iostream>
#include "rb-tree.h"

using namespace std;

int main(int argc, char** argv)
{
    rb_tree<int, int> tree;
    cout << tree.size() << endl;

    tree.insert_equal(10);
    cout << tree.size() << endl;
    tree.insert_equal(7);
    tree.insert_equal(8);
    tree.insert_equal(15);
    tree.insert_equal(5);
    tree.insert_equal(6);
    tree.insert_equal(11);
    tree.insert_equal(13);
    tree.insert_equal(12);

    cout << tree.size() << endl;
    for(auto iter = tree.begin(); iter != tree.end(); iter++)
        cout << *iter << "(" << iter.node->color <<  ")  ";
    cout << endl;

    return 0;
}
