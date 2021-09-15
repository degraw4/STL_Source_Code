#ifndef __HEAP
#define __HEAP
#include <vector>

using namespace std;

// heap简单实现，只针对底层容器为vector<int>的大顶堆，否则要使用traits，较为麻烦
// heap更像是一组算法，而非容器

// push_heap操作时，新元素已经插入底层容器
template<class RandomIterator>
void push_heap(RandomIterator first, RandomIterator last){
    int holeIndex = last - first - 1;
    int topIndex = 0;
    int value = *(first + holeIndex);
    int parent = (holeIndex - 1) / 2;   // 新插入节点的parent
    while(holeIndex > topIndex && value > *(first + parent)){
        *(first + holeIndex) = *(first + parent);   // 只把父节点拉下来，并不需要子节点上去，因为top调整未必结束
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

// 对first在first到len长度的范围内做down调整
template<class RandomIterator>
void adjust_down(RandomIterator first, int len){
    int holeIndex = 0;
    int downIndex = len - 1;
    int secondChild = 2 * holeIndex + 2;
    int value = *(first);
    while(secondChild <= downIndex){
        if(*(first + secondChild) < *(first + secondChild - 1))
            --secondChild;
        if(*(first + secondChild) < value)
            return;
        *(first + holeIndex) = *(first + secondChild);
        *(first + secondChild) = value;
        holeIndex = secondChild;
        secondChild = 2 * holeIndex + 2;
    }
    if(--secondChild > downIndex)   return;
    if(*(first + secondChild) < value)   return;
    *(first + holeIndex) = *(first + secondChild);
    *(first + secondChild) = value;
}

// pop_heap操作只是把根节点放在last-1的位置，然后对first到last-2调整为heap
// 根节点没有真正被pop
template<class RandomIterator>
void pop_heap(RandomIterator first, RandomIterator last){
    int tmp = *first;
    *first = *(last - 1);
    *(last - 1) = tmp;
    adjust_down(first, last - first - 1);
}

template<class RandomIterator>
void sort_heap(RandomIterator first, RandomIterator last){
    while(last > first + 1){
        pop_heap(first, last--);
    }
}

template<class RandomIterator>
void make_heap(RandomIterator first, RandomIterator last){
    if(last - first < 2)    return;
    int topIndex = 0;
    int downIndex = last -first - 1;
    int parent = (downIndex - 1) / 2;
    while(true){
        adjust_down(first + parent, last - first - parent);
        if(parent == 0) return;
        parent--;
    }
}

#endif
