#include <iostream>
using namespace std;

typedef int elementtype;

struct celltype
{
    elementtype element;
    celltype *next;
};
typedef celltype *position;

class Queue
{
protected:
    position Front;
    position Rear;

public:
    Queue();
    ~Queue();
    void Enqueue(elementtype x);
    void Dequeue();
    elementtype FrontElem();
    bool Empty();
};

Queue::Queue()
{
    Front = new celltype;
    Front->next = NULL;
    Rear = Front;
}

Queue::~Queue()
{
    while (Front->next != NULL)
    {
        position tmp = Front;
        Front = Front->next;
        delete tmp;
    }
    delete Front;
}

void Queue::Enqueue(elementtype x)
{
    position p = new celltype;
    p->next = NULL;
    p->element = x;
    Rear->next = p;
    Rear = p;
}

bool Queue::Empty()
{
    if (Front->next == NULL)
        return true;
    else
        return false;
}

void Queue::Dequeue()
{
    if (Empty() == false)
    {
        position tmp = Front;
        Front = Front->next;
        delete tmp;
    }
}

elementtype Queue::FrontElem()
{
    if (Empty() == false)
        return Front->next->element;
}

int main()
{
    Queue k;

    if (k.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    k.Enqueue(5);

    if (k.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    cout << k.FrontElem() << endl;
    k.Dequeue();

    if (k.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    k.Enqueue(4);
    k.Enqueue(3);
    k.Enqueue(2);
    cout << k.FrontElem() << endl;
    k.Enqueue(1);
    cout << k.FrontElem() << endl;
    k.Dequeue();
    cout << k.FrontElem() << endl;
    k.Enqueue(6);
    cout << k.FrontElem() << endl;
    k.Dequeue();
    k.Dequeue();
    cout << k.FrontElem() << endl;

    if (k.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}