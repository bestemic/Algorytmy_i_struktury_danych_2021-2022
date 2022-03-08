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
    void Wypisz();
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
bool BinaryHeap<T>::IsEmpty() const
{
    return (count == 0);
}

template <typename T>
bool BinaryHeap<T>::IsFull() const
{
    return data.capacity() == count;
}

template <typename T>
T BinaryHeap<T>::FindMin() const
{
    if (!data.empty())
    {
        return data.front();
    }
    abort();
}

template <typename T>
void BinaryHeap<T>::Enqueue(T element)
{
    if (data.size() == count)
    {
        data.resize(count + 1);
    }

    int tmp = count;
    while (tmp > 0)
    {
        int dane = data[(tmp - 1) / 2];
        if (dane <= element)
        {
            break;
        }
        else
        {
            data[tmp] = dane;
            tmp = (tmp - 1) / 2;
        }
    }

    data[tmp] = element;
    count++;
}

template <typename T>
T BinaryHeap<T>::DequeueMin()
{
    if (IsEmpty())
    {
        abort();
    }

    T first = data[0];
    count--;
    T last = data[count];

    int tmp = 0;
    while (tmp * 2 + 1 < count)
    {
        int node = tmp * 2 + 1;
        if (node + 1 < count)
        {
            if (data[node + 1] < data[node])
            {
                node = node + 1;
            }
        }
        if (last <= data[node])
        {
            break;
        }

        data[tmp] = data[node];
        tmp = node;
    }

    data[tmp] = last;
    return first;
}

template <typename T>
void BinaryHeap<T>::Wypisz()
{
    for (int i = 0; i < count; i++)
    {
        cout << "|" << data[i] << "|";
    }
    cout << endl;
}

int main()
{
    cout << "Wielkosc 10\n";
    
    BinaryHeap<int> bh = BinaryHeap<int>(10);
    cout << bh.IsEmpty() << endl;
    bh.Enqueue(5);
    cout << bh.IsEmpty() << endl;
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.Enqueue(6);
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.Enqueue(8);
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.Enqueue(3);
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.Enqueue(9);
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.Enqueue(2);
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.Enqueue(1);
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.DequeueMin();
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.DequeueMin();
    bh.Wypisz();
    cout << bh.FindMin() << endl;
    bh.MakeNull();
    cout << bh.IsEmpty() << endl;

    cout << "\nWielkosc 2\n";

    BinaryHeap<int> bh2 = BinaryHeap<int>(2);
    cout << bh2.IsEmpty() << endl;
    bh2.Enqueue(5);
    cout << bh2.IsEmpty() << endl;
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.Enqueue(6);
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.Enqueue(8);
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.Enqueue(3);
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.Enqueue(9);
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.Enqueue(2);
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.Enqueue(1);
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.DequeueMin();
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.DequeueMin();
    bh2.Wypisz();
    cout << bh2.FindMin() << endl;
    bh2.MakeNull();
    cout << bh2.IsEmpty() << endl;

    return 0;
}