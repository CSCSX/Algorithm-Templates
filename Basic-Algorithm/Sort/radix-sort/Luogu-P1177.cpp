// P1177 快速排序
// https://www.luogu.com.cn/problem/P1177

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, *arr;

void radix_sort(int a[], int n, int k)
{
    int width = 32 / k;
    int *cnt = new int[1 << width];
    int *b = new int[n];
    int msk = (1 << width) - 1;
    int *x = a, *y = b;
    for (int i=0; i<32; i+=width)
    {
        for (int j=0; j<=msk; j++) cnt[j] = 0;
        for (int j=1; j<=n; j++) cnt[(x[j] >> i) & msk]++;
        for (int j=1; j<=msk; j++) cnt[j] += cnt[j-1];
        for (int j=n; j; j--) y[cnt[(x[j] >> i) & msk]--] = x[j];
        std::swap(x, y);
    }
    delete []cnt;
    delete []b;
}

int main()
{
    scanf("%d", &n);
    arr = new int[n + 1];
    for (int i=1; i<=n; i++) scanf("%d", &arr[i]);
    radix_sort(arr, n, 4);
    for (int i=1; i<=n; i++) printf("%d ", arr[i]);
    delete []arr;
    return 0;
}