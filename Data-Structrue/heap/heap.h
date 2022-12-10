#ifndef HEAP_H
#define HEAP_H

template <class T>//小根堆
class  MinHeap 
{
private:
    static const int DefaultSize = 10000;
    T *heap;
    int nowSize, maxSize;
    void siftDown(int start, int m);
    void siftUp(int start);
public:
    MinHeap(int n = DefaultSize);
    MinHeap(T arr[], int n);
    ~MinHeap() { delete []heap; nowSize = 0; }
    bool insert(const T &x);
    bool pop(T &x);
    T top() { return heap[0]; }
    int size() { return nowSize;}
    bool empty() const { return nowSize == 0; }
    void claer() { nowSize = 0; };
};

template<class T>//构造1
MinHeap<T>::MinHeap(int n)
{
    maxSize = (DefaultSize < n) ? n : DefaultSize;
    heap = new T[maxSize];
    if (heap == nullptr)
    {
        std::cerr << "Fail to allocate storage for the heap." << std::endl;
        exit(1);    
    }
    nowSize = 0;
}

template<class T>//构造2
MinHeap<T>::MinHeap(T arr[], int n)
{
    maxSize = (DefaultSize < n) ? n : DefaultSize;
    heap = new T[maxSize];
    if (heap == nullptr)
    {
        std::cerr << "Fail to allocate storage for the heap." << std::endl;
        exit(1);    
    }
    nowSize = n;
    int nowPos = (nowSize - 2) / 2;
    while (nowPos >= 0)
    {
        siftDown(nowPos, n - 1);
        nowPos--;
    }
}

template<class T>//向下调整
void MinHeap<T>::siftDown(int start, int m)
{
    int i = start, j = 2 * i + 1, tmp = heap[i];
    while (j <= m)
    {
        if (j < m && heap[j] > heap[j + 1]) j++;
        if (tmp < heap[j]) break;
        heap[i] = heap[j];
        i = j, j = 2 * i + 1;
    }
    heap[i] = tmp;
}

template<class T>//向上调整
void MinHeap<T>::siftUp(int start)
{
    int i = start, j = (i - 1) / 2, tmp = heap[i];
    while (i)
    {
        if (tmp >= heap[j]) break;
        heap[i] = heap[j];
        i = j, j = (i - 1) / 2;
    }
    heap[i] = tmp;
}

template<class T>//插入x
bool MinHeap<T>::insert(const T& x)
{
    if (nowSize == maxSize)
    {
        std::cerr << "Heap full." << std::endl;
        return false;
    }
    heap[nowSize] = x;
    siftUp(nowSize);
    nowSize++;
    return true;
}

template<class T>//弹出最小值
bool MinHeap<T>::pop(T& x)
{
    if (!nowSize)
    {
        std::cerr << "Heap empty." << std::endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[--nowSize];
    siftDown(0, nowSize - 1);
    return true;
}

#endif