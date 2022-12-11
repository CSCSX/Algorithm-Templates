#ifndef SPLAY_H
#define SPLAY_H

template <class T>
class Splay
{
private:
    typedef struct 
    {
        int fa, ch[2], siz, cnt;
        T val;
    } SplayNode;
    SplayNode* t;
    int root, tot;
    void init(int x);
    int id(int x);
    void upd(int x);
    void connect(int x, int y, int id);
    void rotate(int x);
    void splay(int x, int target=0);
    int find_less(T val);
    int find_greater(T val);
    T pre(T x);
    T nxt(T x);
public:
    Splay() : root(0), tot(0) {}
    Splay(int n) : root(0), tot(0)
    {
        t = new SplayNode[n+3];
        for (int i = 0; i < n + 3; ++i) init(i);
        insert(inf);
        insert(-inf);
    }
    ~Splay() { delete []t; }
    void insert(T val);
    int get_rank(T val);
    T rank(int k);
    void delete_interval(T l, T r);
    void delete_one(T val);
    T get_pre(T x);
    T get_nxt(T x);
    int shit() { return t[root].siz; }
};

template <class T>
void Splay<T>::init(int x)
{
    t[x].fa = t[x].ch[0] = t[x].ch[1] = t[x].siz = t[x].cnt = 0; 
}

template <class T>
int Splay<T>::id(int x)
{
    if (x == t[t[x].fa].ch[1]) return 1;
    if (x == t[t[x].fa].ch[0]) return 0;
    return -1;
}

template <class T>
void Splay<T>::upd(int x)
{
    // assert(x);
    int ls = t[x].ch[0], rs = t[x].ch[1];
    t[x].siz = t[ls].siz + t[rs].siz + t[x].cnt;
}

template <class T>
void Splay<T>::connect(int x, int y, int id)
{
    if (x) t[x].fa = y;
    if (y && id != -1) t[y].ch[id] = x;
}

template <class T>
void Splay<T>::rotate(int x)
{
    int y = t[x].fa, z = t[y].fa, idx = id(x), idy = id(y);
    int u = t[x].ch[idx ^ 1];
    connect(u, y, idx);
    connect(y, x, idx ^ 1);
    connect(x, z, idy);
    upd(y), upd(x);
}

template <class T>
void Splay<T>::splay(int x, int target)
{
    while (t[x].fa != target)
    {
        int y = t[x].fa;
        if (t[y].fa != target) rotate(id(x) ^ id(y) ? x : y);
        rotate(x);
    }
    if (!target) root = x;
}

template <class T>
int Splay<T>::find_less(T val)
{
    get_rank(val);
    int now = t[root].ch[0];
    while (t[now].ch[1]) now = t[now].ch[1];
    return now;
}

template <class T>
int Splay<T>::find_greater(T val)
{
    get_rank(val);
    int now = t[root].ch[1];
    while (t[now].ch[0]) now = t[now].ch[0];
    return now;
}

template <class T>
void Splay<T>::insert(T val)
{
    int now = root, fa = 0;
	while (now && t[now].val != val)
	{
		fa = now;
		now = t[now].ch[val > t[now].val]; 
	}
	if(now) t[now].cnt++;
	else
	{
		now = ++tot;
        connect(now, fa, val > t[fa].val);
		t[tot].val = val;
		++t[tot].cnt;
	}
    upd(now), upd(fa);
	splay(now);
}

template <class T>
int Splay<T>::get_rank(T val)
{
    int now = root;
    while(t[now].ch[val > t[now].val] && val != t[now].val)
		now = t[now].ch[val > t[now].val];
    splay(now);
    return t[t[now].ch[0]].siz;
}

template <class T>
T Splay<T>::rank(int k)
{
    ++k;
    int now = root;
    while (true)
    {
        if (t[now].ch[0] && k <= t[t[now].ch[0]].siz) now = t[now].ch[0];
        else
        {
            k -= t[t[now].ch[0]].siz + t[now].cnt;
            if (k <= 0)
            {
                splay(now);
                return t[now].val;
            }
            now = t[now].ch[1];
        }
    }
}

template <class T>
void Splay<T>::delete_interval(T l, T r)
{
    assert(l <= r);
    int x = find_less(l), y = find_greater(r);
    splay(x), splay(y, x);
    t[y].ch[0] = 0;
    upd(y), upd(x);
}

template <class T>
void Splay<T>::delete_one(T val)
{
    int x = find_less(val), y = find_greater(val);
    splay(x), splay(y, x);
    int now = t[y].ch[0];
    assert(!t[now].ch[0] && !t[now].ch[1]);
    --t[now].cnt;
    if (!t[now].cnt) t[y].ch[0] = 0;
    upd(now), upd(y), upd(x);
}
template <class T>
T Splay<T>::pre(T x)
{
    int index = find_less(x);
    return t[index].val;
}
template <class T>
T Splay<T>::nxt(T x)
{
    int index = find_greater(x);
    return t[index].val;
}
template <class T>
T Splay<T>::get_pre(T x)
{
    insert(x);
    T ret = pre(x);
    delete_one(x);
    return ret;
}
template <class T>
T Splay<T>::get_nxt(T x)
{
    insert(x);
    T ret = nxt(x);
    delete_one(x);
    return ret;
}
#endif