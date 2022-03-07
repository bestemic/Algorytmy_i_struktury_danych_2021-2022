#include <iostream>
using namespace std;

const int maxlength = 50;
typedef int elementtype;
typedef int position;
class Kolejka
{
protected:
    elementtype Queue[maxlength];
    position Front; // Indeks elementu czołowego
    position Rear;  // Indeks ostatniego elementu
public:
    Kolejka();
    int AddOne(int i);
    void Enqueue(elementtype x);
    void Dequeue();
    elementtype FrontElem();
    void Makenul();
    bool Empty();
};

Kolejka::Kolejka()
{
    Front = 0;
    Rear = maxlength - 1;
}

int Kolejka::AddOne(int i)
{
    int x = (i + 1) % maxlength;
    return x;
}

void Kolejka::Enqueue(elementtype x)
{
    if (AddOne(AddOne(Rear)) != Front)
    {
        Rear = AddOne(Rear);
        Queue[Rear] = x;
    }
}

void Kolejka::Dequeue()
{
    if (Empty()==false)
    {
        Front = AddOne(Front);
    }
}

elementtype Kolejka::FrontElem()
{
    if (Empty()==false)
    {
        return Queue[Front];
    }
}

void Kolejka::Makenul()
{
    Front = 0;
    Rear = maxlength - 1;
}

bool Kolejka::Empty()
{
    if ((AddOne(Rear)) == Front)
    {
        return true;
    }
    else
        return false;
}

int main()
{
    Kolejka k;

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
    k.Makenul();

    if (k.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}