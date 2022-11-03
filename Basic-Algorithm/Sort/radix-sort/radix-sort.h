//基数排序
//将32位整型分为k个值域 (k须为偶数)
//n为元素个数[1, n]
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