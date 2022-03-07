#include <iostream>
#include <vector>
using namespace std;

class Container
{
protected:
    Container(){};

public:
    virtual unsigned int Count() const = 0;
    virtual bool IsEmpty() const { return Count() == 0; };
    virtual bool IsFull() const = 0;
    virtual void MakeNull() = 0;
};

template <typename T>
class PriorityQueue : public Container
{
public:
    virtual void Enqueue(T element) = 0;
    virtual T FindMin() const = 0;
    virtual T DequeueMin() = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
protected:
    int count;
    std::vector<T> data;

public:
    BinaryHeap(unsigned int n);
    ~BinaryHeap() { ; };
    void MakeNull();
    bool IsEmpty() const;
    bool IsFull() const;
    unsigned int Count() const { return count; }
    void Enqueue(T element);
    T FindMin() const;
    T DequeueMin();
};

template <typename T>
BinaryHeap<T>::BinaryHeap(unsigned int n)
{
    count = 0;
    data.reserve(n);
}

template <typename T>
void BinaryHeap<T>::MakeNull()
{
    count = 0;
}

template <typename T>
bool BinaryHeap<T>::IsFull() const
{
    return data.capacity == count;
}

template <typename T>
T BinaryHeap<T>::FindMin() const
{
    if (!data.empty())
    {
        return data.front();
    }
}

template <typename T>
void BinaryHeap<T>::Enqueue(T element)
{
    if (data.size() == count)
    {
        data.resize(count + 1);
    }
}

template <typename T>
T BinaryHeap<T>::DequeueMin()
{
}

int main()
{
    BinaryHeap<int> bh = BinaryHeap<int>(10);
    return 0;
}