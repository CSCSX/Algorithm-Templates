#ifndef SA_H
#define SA_H

class SA_optimized
{
public:
    static void getSA(int n, char s[], int sa[], int rk[])
    {
        if (n == 1) return void(sa[1] = rk[1] = 1);
        int *cnt = new int[max(130, n) + 1], *tmp = new int[2 * n + 1];
        int m = 130;
        std::fill(cnt, cnt + max(130, n) + 1, 0);
        std::fill(tmp, tmp + 2 * n + 1, 0);
        for (int i=1; i<=n; i++) cnt[rk[i] = s[i]]++;
        for (int i=1; i<=m; i++) cnt[i] += cnt[i-1];
        for (int i=n; i; i--) sa[cnt[rk[i]]--] = i;
        for (int w = 1; w <= n; w <<= 1)
        {
            for (int i = n; i + w > n; i--) tmp[n - i + 1] = i;
            for (int i = 1, p = w; i <= n; i++) if (sa[i] > w) tmp[++p] = sa[i] - w;
            std::fill(cnt, cnt + m + 1, 0);
            for (int i = 1; i <= n; i++) cnt[rk[tmp[i]]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
            for (int i = n; i; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i];
            m = 0;
            auto key = [&](const int &x) { return std::make_pair(rk[x], rk[x + w]); };
            for (int i = 1; i <= n; i++) tmp[sa[i]] = (key(sa[i]) == key(sa[i-1])) ? m : ++m;
            memcpy(rk + 1, tmp + 1, sizeof(int) * n);
            if (m == n) break;
        }
    }
    static void getHeight(int n, char s[], int height[], int sa[], int rk[])
    {
        for (int i = 1, k = 0; i <= n; i++)
        {
            if (k) --k;
            while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
            height[rk[i]] = k;
        }
    }
};

class SA
{
private:
    static void init(int n, char* s, int *sa, int *rk)
    {
        sa[0] = rk[0] = 0;
        for (int i = 1; i <= n; i++) rk[i] = s[i], sa[i] = i;
        std::fill(sa + n + 1, sa + 2 * n + 1, 0);
        std::fill(rk + n + 1, rk + 2 * n + 1, 0);
    }
    static void radix_sort(int m, int n, int *sa, int *rk, int *cnt, int *tmp, int tag)
    {
        std::fill(cnt, cnt + m + 1, 0);
        for (int i=1; i<=n; i++) cnt[rk[sa[i] + tag]]++;
        for (int i=1; i<=m; i++) cnt[i] += cnt[i-1];
        for (int i=n; i; i--) tmp[cnt[rk[sa[i] + tag]]--] = sa[i];
    }
public:
    static void getSA_nlog2n(int n, char* s, int *sa, int *rk)
    {
        if (n == 1) return void (sa[1] = rk[1] = 1);
        init(n, s, sa, rk);
        int *tmp = new int[n+1];
        for (int w = 1; w <= n; w <<= 1)
        {
            auto key = [&](const int &x) { return std::make_pair(rk[x], rk[x + w]); };
            std::sort(sa + 1, sa + n + 1, [=](const int &x, const int &y){ return key(x) < key(y); });
            for (int i = 1, p = 0; i <= n; i++) tmp[sa[i]] = key(sa[i]) == key(sa[i-1]) ? p : ++p;
            memcpy(rk + 1, tmp + 1, sizeof(int) * n);
        }
    }
    static void getSA_nlogn(int n, char* s, int *sa, int *rk)
    {
        if (n == 1) return void (sa[1] = rk[1] = 1);
        init(n, s, sa, rk);
        int m = std::max(130, n);
        int *tmp = new int[2 * n+1], *cnt = new int[m + 1];
        std::fill(tmp, tmp + 2 * n + 1, 0);
        for (int w = 1; w <= n; w <<= 1)
        {
            radix_sort(m, n, sa, rk, cnt, tmp, w);
            radix_sort(m, n, tmp, rk, cnt, sa, 0);
            auto key = [&](const int &x) { return std::make_pair(rk[x], rk[x + w]); };
            for (int i=1, p=0; i<=n; i++) tmp[sa[i]] = key(sa[i]) == key(sa[i-1]) ? p : ++p;
            memcpy(rk + 1, tmp + 1, sizeof(int) * n);
        }
    }
    static void getSA_nlogn_optimized(int n, char* s, int *sa, int *rk)
    {
        if (n == 1) return void (sa[1] = rk[1] = 1);
        init(n, s, sa, rk);
        int m = 130;
        int *tmp = new int[2 * n+1], *cnt = new int[max(n, m) + 1];
        std::fill(tmp, tmp + 2 * n + 1, 0);
        radix_sort(m, n, sa, rk, cnt, tmp, 0);
        memcpy(sa + 1, tmp + 1, sizeof(int) * n);
        for (int w = 1; w <= n; w <<= 1)
        {
            for (int i = n; i + w > n; i--) tmp[n- i + 1] = i;
            for (int i = 1, p = w; i <= n; i++) if (sa[i] > w) tmp[++p] = sa[i] - w;
            radix_sort(m, n, tmp, rk, cnt, sa, 0);
            m = 0;
            auto key = [&](const int &x) { return std::make_pair(rk[x], rk[x + w]); };
            for (int i=1; i<=n; i++) tmp[sa[i]] = key(sa[i]) == key(sa[i-1]) ? m : ++m;
            memcpy(rk + 1, tmp + 1, sizeof(int) * n);
            if (m == n) break;
        }
    }
};

#endif