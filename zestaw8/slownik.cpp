#include <iostream>
using namespace std;

const int B = 65;
typedef char *elementtype;
struct celltype
{
    elementtype element;
    celltype *next;
};
typedef celltype *position;

class dictionary
{
protected:
    position D[B];

public:
    dictionary();
    ~dictionary();
    void Makenul();
    bool Member(elementtype x);
    void Insert(elementtype x);
    void Delete(elementtype x);
    int H(elementtype x);
};

dictionary::dictionary()
{
    for (int i = 0; i <= B; i++)
    {
        D[i] = NULL;
    }
}

dictionary::~dictionary()
{
    position tmp;
    for (int i = 0; i <= B; i++)
    {
        while (D[i] != NULL)
        {
            tmp = D[i];
            D[i] = D[i]->next;
            delete tmp;
        }
    }
}

void dictionary::Makenul()
{
    position tmp;
    for (int i = 0; i <= B; i++)
    {
        while (D[i] != NULL)
        {
            tmp = D[i];
            D[i] = D[i]->next;
            delete tmp;
        }
    }
}

bool dictionary::Member(elementtype x)
{
    position tmp = D[H(x)];
    while (tmp != NULL)
    {
        if (tmp->element == x)
            return true;
        else
            tmp = tmp->next;
    }
    return false;
}

void dictionary::Insert(elementtype x)
{
    if (Member(x) == false)
    {
        int where = H(x);
        position tmp = D[where];
        position nowa = new celltype;
        nowa->element = x;
        nowa->next = tmp;
        D[where] = nowa;
    }
}

void dictionary::Delete(elementtype x)
{
    int bucket = H(x);
    if (D[bucket] != NULL)
    {
        if (D[bucket]->element == x)
        {
            position tmp = D[bucket];
            D[bucket] = D[bucket]->next;
            delete tmp;
        }
        else
        {
            position tmp = D[bucket];
            while (tmp->next != NULL)
            {
                if (tmp->next->element == x)
                {
                    position tmp2 = tmp->next;
                    tmp->next = tmp->next->next;
                    delete tmp2;
                    return;
                }
                else
                {
                    tmp = tmp->next;
                }
            }
        }
    }
}

int dictionary::H(elementtype x)
{
    return (int(x[0]) % B);
}

int main()
{
    dictionary d;
    d.Insert("Ala");
    cout << d.Member("Ala") << endl;
    cout << d.H("Ala") << endl;

    d.Insert("As");
    cout << d.Member("As") << endl;
    cout << d.H("As") << endl;

    cout << d.Member("Ala") << endl;
    cout << d.H("Ala") << endl;

    d.Insert("Pawlik");
    cout << d.H("Pawlik") << endl;
    cout << d.Member("Pawlik") << endl;

    d.Delete("Ala");
    cout << d.Member("As") << endl;
    cout << d.Member("Ala") << endl;

    d.Makenul();
    cout << d.Member("As") << endl;
    cout << d.Member("Pawlik") << endl;

    return 0;
}