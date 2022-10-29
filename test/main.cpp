#include <bits/stdc++.h>
#include "head.h"
using namespace std;
int main()
{
    int a[5] = {0, 3, 4, 6, 3};
    int b[5];
    counting_sort(a, 4, 10, b);
    for (int i=1; i<=4; i++) printf("%d ", b[i]);
    return 0;
}