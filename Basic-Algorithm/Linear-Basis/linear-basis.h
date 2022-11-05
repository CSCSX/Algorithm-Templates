#ifndef LINEAR_BASIS_H
#define LINEAR_BASIS_H

class LinearBasis
{
public:
    vector<long long> p, q;
    bool zero;
    int m; //number of bits
    LinearBasis(int n) :  p(vector<long long>(n, 0)), q(vector<long long>(n, 0)), zero(false), m(n) {}
    void insert(long long x)
    {
        for (int i=m-1; i>=0; i--) if (x & (1LL << i))
            if (!p[i]) { p[i] = x; return; }
            else x ^= p[i];
        zero = true;
    }
    long long qmax()
    {
        long long ret = 0;
        for(int i=m-1; i>=0; i--) ret = max(ret, ret ^ p[i]);
        return ret;
    }
    long long qmin()
    {
        if (zero) return 0;
        for (int i=0; i<=m-1; i++) if (p[i]) return p[i];
        return 0; //impossible
    }
    bool check(long long x)
    {
        for (int i=m-1; i>=0; i--) if (x & (1LL << i))
            if (p[i]) x ^= p[i];
            else return false;
        return true;
    }
    long long query_k(long long k)
    {
        k -= zero;
        if (!k) return 0;
        int cnt = 0;
        long long ret;
        for (int i=0; i<m; i++)
        {
            for (int j=i-1; j>=0; j--) if (p[i] & (1LL << j)) p[i] ^= p[j];
            if (p[i]) q[cnt++] = p[i];
        }
        if (k >= (1LL << cnt)) return -1; // k is too big
        for (int i=0; i<cnt; i++) if (k & (1LL << i)) ret ^= q[i];
        return ret;
    }
};

#endif