#include <bits/stdc++.h>
#include "head.h"
using namespace std;
int main()
{
    MinHeap<int> heap(100);
    for (int i=2; i<=100; i++) heap.insert(i);
    int x;
    heap.pop(x);
    printf("%d\n", x);
    return 0;
}