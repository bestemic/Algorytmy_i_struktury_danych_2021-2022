#include <iostream>
using namespace std;

const int maxlegth = 3;
typedef int elementtype;
typedef int position;

class Stos
{
    int S[maxlegth];
    position Top; //szczyt stosu
public:
    Stos();
    void Push(elementtype x);
    void Pop();
    bool Empty();
    elementtype TopElem();
    void Makenul();
};

Stos::Stos()
{
    Top = -1;
}

void Stos::Push(elementtype x)
{
    if (maxlegth - 1 > Top)
    {
        S[Top + 1] = x;
        Top++;
    }
}

void Stos::Pop()
{
    if (Top != -1)
    {
        Top--;
    }
}

bool Stos::Empty()
{
    return (Top == -1) ? true : false;
}

elementtype Stos::TopElem()
{
    if (Top != -1)
    {
        return S[Top];
    }
}

void Stos::Makenul()
{
    Top = -1;
}

int main()
{
    Stos s;

    if (s.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    s.Push(5);
    cout << s.TopElem() << endl;

    if (s.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    s.Pop();

    if (s.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    s.Push(2);
    s.Push(3);
    cout << s.TopElem() << endl;
    s.Push(4);
    s.Push(5);
    cout << s.TopElem() << endl;
    s.Makenul();

    if (s.Empty() == 1)
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}