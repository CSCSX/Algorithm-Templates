//计数排序
//元素个数n[1, n], 元素值域w[1, w]
class Counting_sort
{
    static void counting_sort(int a[], int n, int w, int b[])  
    {
        int *cnt = new int[w + 1];
        for (int i=0; i<=w; i++) cnt[i] = 0;
        for (int i=1; i<=n; i++) cnt[a[i]]++;
        for (int i=1; i<=w; i++) cnt[i] += cnt[i-1];
        for (int i=n; i; i--) b[cnt[a[i]]--] = a[i];
        delete []cnt;
    }
};
