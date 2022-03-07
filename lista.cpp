typedef int elementtype, position;
const int maxlength = 10, min = -1000000;
struct List
{
    elementtype elements[maxlength];
    int last; //indeks ostatniego elementu listy
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
    if ((p > l.last) || (p < 0))
    {
        return -1;
    }
    else
    {
        return p + 1;
    }
}

position Previous(position p, List l)
{
    if ((p > (l.last + 1)) || (p < 0))
    {
        return -1;
    }
    else
    {
        return p - 1;
    }
}

position Locate(elementtype x, List l)
{ //zwraca pozycje x w l, gdy nie ma x w l zwraca end(l)

    int i = 0;
    while ((i <= l.last) && (l.elements[1] != x))
    {
        i++;
    }
    return i;
}

elementtype Retrieve(position p, List l)
{
    if ((p > l.last) || (p < 0))
    {
        return min;
    }
    else
    {
        return l.elements[p];
    }
}

bool Insert(int x, position p, List &l)
{
    if (l.last >= maxlength)
    {
        return false;
    }
    else if ((p > l.last + 1) || (p < 0))
    {
        return false;
    }
    else
    {
        for (int i = l.last; i >= p; i--)
        {
            l.elements[i + 1] = l.elements[i];
            l.elements[p] = x;
            l.last = l.last + 1;
        }
            return true;
    }
}

bool Delete(position p, List &l)
{
    if ((p > l.last) || (p < 0))
    {
        return false;
    }
    else
    {
        for (int i = p; i < l.last; i++)
        {
            l.elements[i] = l.elements[i + 1];
            l.last--;
        }
            return true;
    }
}
