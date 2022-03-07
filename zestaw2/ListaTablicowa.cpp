#include <iostream>

typedef int elementtype, position;
const int maxlength = 30;
const int min = -10000000;
struct List
{
    elementtype elements[maxlength];
    int last;
};

position END(List l)
{
    return l.last + 1;
}

position First(List l)
{
    return 0;
}

position Next(position p, List l)
{
    if (p > l.last || p < 0)
    {
        return -1;
    }
    else
        return p + 1;
}

position Previous(position p, List l)
{
    if (p <= 0 || p > l.last + 1)
    {
        return -1;
    }
    else
        return p - 1;
}

position Locate(elementtype x, List l)
{
    int tmp = 0;
    while (l.elements[tmp] != x && l.last >= tmp)
    {
        tmp++;
    }
    return tmp;
}

elementtype Retrieve(position p, List l)
{
    if (p > l.last || p < 0)
    {
        return min;
    }
    else
        return l.elements[p];
}

bool Insert(int x, position p, List &l)
{
    if (l.last >= maxlength || p < 0 || p > l.last + 1)
    {
        return false;
    }
    else
    {
        for (int i = l.last; i >= p; i--)
        {
            l.elements[i + 1] = l.elements[i];
        }
        l.elements[p] = x;
        l.last++;
        return true;
    }
}

bool Delete(position p, List &l)
{
    if (p < 0 || p > l.last)
    {
        return false;
    }
    else
    {
        for (int i = p; i < l.last; i++)
        {
            l.elements[i] = l.elements[i + 1];
        }
        l.last--;
        return true;
    }
}

void Duplicate(List &l){
    int end = l.last;
    for(int i=0; i<=end; i++){
        Insert(l.elements[i], END(l), l);
    }
}


void DelateDuplicate(List &l){
    for(int i=0; i<=l.last; i++){
        for(int j=0; j<=l.last; j++){
            if((j!=i) && (l.elements[i]==l.elements[j])){
                Delete(j, l);
            }
        }    
    }
}

// Tests
void print(List l)
{
    position i = First(l);
    while (i != END(l))
    {
        printf("  %d,", Retrieve(i, l));
        i = Next(i, l);
    }
    printf("\n");
}

int main()
{
    List l;
    l.last = -1;
    Insert(100, First(l), l);
    print(l);

    for (int i = 0; i < 3; i++)
        Insert(i, First(l), l);
    print(l);

    Insert(20, Previous(END(l), l), l);
    print(l);
    Delete(Locate(20, l), l);
    print(l);

    Duplicate(l);
    print(l);
    Duplicate(l);
    print(l);

    DelateDuplicate(l);
    print(l);
    
    Insert(5, Locate(100, l), l);
    print(l);

}