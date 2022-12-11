#ifndef SPLAY_H
#define SPLAY_H

template <class T>
class SplayNode
{
public:
    SplayNode *fa, *ch[2];
    int siz, cnt;
    T val;
};

template <class T>
class Splay
{
private:
    typedef SplayNode<T> Node;
    Node* root;
    Node* zero;
    int tot;
    void init(Node* x); // 初始化节点
    int id(Node* x); // 节点是(左\右\不是)儿子
    void upd(Node* x); // 更新子树信息
    void connect(Node* x, Node* y, int id); // 将 x 连接到 y 的 id 儿子处
    void rotate(Node* x); // 单旋
    void splay(Node* x, Node* target=nullptr); // 将 x 旋到 target 下面
    Node* find_less(T val); // 找到比 val 小的第一个节点
    Node* find_greater(T val); // 找到比 val 大的第一个节点
    T pre(T x); // 找 x 的前驱(x必须在树中)
    T nxt(T x); // 找 x 的后继(x必须在树中)
public:
    Splay(); // 构造函数
    void insert(T val); // 插入元素
    int get_rank(T val); // 获取某个元素的排名(该元素可不在树中)
    T rank(int k); // 查询排名为 k 的元素(k必须合法)
    void delete_interval(T l, T r); // 删除区间 [l,r] 的所有节点
    void delete_one(T val); // 删除一个 val 值
    T get_pre(T x); // 找 x 的前驱(x可以不在树中)
    T get_nxt(T x); // 找 x 的后继(x可以不在树中)
};
template <class T>
Splay<T>::Splay()
    : tot(0)
{
    zero = new Node;
    init(zero); 
    root = zero; 
    insert(inf);
    insert(-inf);
}
template <class T>
void Splay<T>::init(Node* x)
{
    x->fa = x->ch[0] = x->ch[1] = zero;
    x->siz = x->cnt = 0;
}
template <class T>
int Splay<T>::id(Node* x)
{
    if (x->fa == zero) return -1;
    if (x == x->fa->ch[0]) return 0;
    if (x == x->fa->ch[1]) return 1;
    return -1;
}
template <class T>
void Splay<T>::upd(Node* x)
{
    if (x == zero) return;
    Node *ls = x->ch[0], *rs = x->ch[1];
    x->siz = ls->siz + rs->siz + x->cnt;
}
template <class T>
void Splay<T>::connect(Node* x, Node* y, int id)
{
    if (x != zero) x->fa = y;
    if (y != zero && id != -1) y->ch[id] = x;
}
template <class T>
void Splay<T>::rotate(Node* x)
{
    Node *y = x->fa, *z = y->fa;
    int idx = id(x), idy = id(y);
    Node* u = x->ch[idx ^ 1];
    connect(u, y, idx);
    connect(y, x, idx ^ 1);
    connect(x, z, idy);
    upd(y), upd(x);
}
template <class T>
void Splay<T>::splay(Node* x, Node* target)
{
    if (target == nullptr) target = zero;
    while (x->fa != target)
    {
        Node* y = x->fa;
        if (y->fa != target) rotate(id(x) ^ id(y) ? x : y);
        rotate(x);
    }
    if (target == zero) root = x;
}
template <class T>
void Splay<T>::insert(T val)
{
    Node *now = root, *fa = zero;
    while (now != zero && now->val != val)
    {
        fa = now;
        now = now->ch[val > now->val];
    }
    if (now != zero) ++now->cnt;
    else
    {
        now = new Node;
        init(now);
        connect(now, fa, val > fa->val);
        now->val = val;
        ++now->cnt;
    }
    upd(now), upd(fa);
    splay(now);
}
template <class T>
int Splay<T>::get_rank(T val)
{
    Node* now = root;
    while (now->ch[val > now->val] != zero && val != now->val)
        now = now->ch[val > now->val];
    splay(now);
    return now->ch[0]->siz;
}
template <class T>
T Splay<T>::rank(int k)
{
    ++k;
    Node* now = root;
    while (true)
    {
        if (now->ch[0] != zero && k <= now->ch[0]->siz) now = now->ch[0];
        else
        {
            k -= now->ch[0]->siz + now->cnt;
            if (k <= 0)
            {
                splay(now);
                return now->val;
            }
            now = now->ch[1];
        }
    }
}
template <class T>
SplayNode<T>* Splay<T>::find_less(T val)
{
    get_rank(val);
    SplayNode<T>* now = root->ch[0];
    while (now->ch[1] != zero) now = now->ch[1];
    return now;
}
template <class T>
SplayNode<T>* Splay<T>::find_greater(T val)
{
    get_rank(val);
    SplayNode<T>* now = root->ch[1];
    while (now->ch[0] != zero) now = now->ch[0];
    return now;
}
template <class T>
T Splay<T>::pre(T x)
{
    SplayNode<T>* node = find_less(x);
    return node->val;
}
template <class T>
T Splay<T>::nxt(T x)
{
    SplayNode<T>* node = find_greater(x);
    return node->val;
}
template <class T>
void Splay<T>::delete_interval(T l, T r)
{
    SplayNode<T> *x = find_less(l), *y = find_greater(r);
    splay(x), splay(y, x);
    y->ch[0] = zero;
    upd(y), upd(x);
}
template <class T>
void Splay<T>::delete_one(T val)
{
    SplayNode<T> *x = find_less(val), *y = find_greater(val);
    splay(x), splay(y, x);
    SplayNode<T>* now = y->ch[0];
    --now->cnt;
    if (!now->cnt) y->ch[0] = zero;
    upd(now), upd(y), upd(x);
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