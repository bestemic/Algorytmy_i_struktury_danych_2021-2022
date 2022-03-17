#include <iostream>
#include <vector>
using namespace std;

// template <typename T>
// class Visitor
// {
// public:
//     virtual void Visit(T &element) = 0;
//     virtual bool IsDone() const { return false; }
// };

// class AddingVisitor : public Visitor<int>
// {
// public:
//     int sum;
//     void Visit(int &element);
// };

// template <typename T>
class Container
{
public:
    Container(){};
    virtual int Count() const = 0;
    virtual bool IsEmpty() const { return Count() == 0; };
    virtual bool IsFull() const = 0;
    virtual void MakeNull() = 0;
    // virtual void Accept(Visitor<T> &v) = 0;
};

template <typename T>
class Set : public virtual Container
{
protected:
    int count;
    int universeSize;

public:
    Set();
    Set(int n) : universeSize(n) {}
    int UniverseSize() const { return universeSize; }
    int Count() const { return count; };
    virtual void Insert(T element) = 0;
    virtual bool IsMember(T element) const = 0;
    virtual void Withdraw(T element) = 0;
};

class SetAsArray : public Set<int>
{
    std::vector<bool> array;

public:
    SetAsArray(unsigned int n);
    void MakeNull()
    {
        count = 0;
        universeSize = 0;
    }
    bool IsFull() const { return (Count() == UniverseSize()); };
    void Insert(int element);
    bool IsMember(int element) const;
    void Withdraw(int element);
    void Wypisz();

    // friend- funkcja uzyska prawo dostepu do prywatnych elementów danej klasy.
    friend SetAsArray operator+(SetAsArray const &, SetAsArray const &);
    friend SetAsArray operator-(SetAsArray const &, SetAsArray const &);
    friend SetAsArray operator*(SetAsArray const &, SetAsArray const &);
    friend bool operator==(SetAsArray const &, SetAsArray const &);
    friend bool operator<=(SetAsArray const &, SetAsArray const &);

    // void Accept(Visitor &) const;
};

SetAsArray::SetAsArray(unsigned int n) : Set(n)
{
    for (int i = 0; i < n; i++)
    {
        array.push_back(false);
    }
}

void SetAsArray::Insert(int element)
{
    if (!array[element])
    {
        array[element] = true;
        count++;
    }
}

void SetAsArray::Withdraw(int element)
{
    if (array[element])
    {
        array[element] = false;
        count--;
    }
}

bool SetAsArray::IsMember(int element) const
{
    if (element >= this->universeSize || element < 0)
        return false;
    return this->array[element];
}

void SetAsArray::Wypisz()
{
    for (int i = 0; i < universeSize; i++)
    {
        if (array[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

SetAsArray operator+(SetAsArray const &s1, SetAsArray const &s2)
{
    if (s1.universeSize == s2.universeSize)
    {
        SetAsArray wynik = SetAsArray(s1.universeSize);
        for (int i = 0; i < s1.universeSize; i++)
        {
            if (s1.array[i] || s2.array[i])
            {
                wynik.array[i] = true;
                wynik.count++;
            }
        }
        return wynik;
    }
    else
    {
        abort();
    }
}

SetAsArray operator*(SetAsArray const &s1, SetAsArray const &s2)
{
    if (s1.universeSize == s2.universeSize)
    {
        SetAsArray wynik = SetAsArray(s1.universeSize);
        for (int i = 0; i < s1.universeSize; i++)
        {
            if (s1.array[i] && s2.array[i])
            {
                wynik.array[i] = true;
                wynik.count++;
            }
        }
        return wynik;
    }
    else
    {
        abort();
    }
}

SetAsArray operator-(SetAsArray const &s1, SetAsArray const &s2)
{
    if (s1.universeSize == s2.universeSize)
    {
        SetAsArray wynik = SetAsArray(s1.universeSize);
        for (int i = 0; i < s1.universeSize; i++)
        {
            if (s1.array[i] == true && s2.array[i] == false)
            {
                wynik.array[i] = true;
                wynik.count++;
            }
        }
        return wynik;
    }
    else
    {
        abort();
    }
}

bool operator==(SetAsArray const &s1, SetAsArray const &s2)
{
    if (s1.universeSize == s2.universeSize)
    {
        for (int i = 0; i < s1.universeSize; i++)
        {
            if (s1.array[i] != s2.array[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<=(SetAsArray const &s1, SetAsArray const &s2)
{

    for (int i = 0; i < s1.universeSize; i++)
    {
        if (s1.array[i] != s2.array[i] && !s2.array[i])
        {
            return false;
        }
    }
    return true;
}

// void SetAsArray::Accept(Visitor &v) const
// {
//     for (int i = 0; i < universeSize; i++)
//     {
//         if (array[i])
//         {
//             v.Visit(i);
//         }
//     }
// }

// void AddingVisitor::Visit(int &element)
// {
//     sum += element;
// }

int main()
{
    SetAsArray A = SetAsArray(10);
    SetAsArray B = SetAsArray(10);
    SetAsArray C = SetAsArray(10);
    SetAsArray D = SetAsArray(10);

    for (int i = 0; i < 10; i++)
    {
        if (i % 2)
        {
            B.Insert(i);
        }
        else
        {
            A.Insert(i);
        }
    }

    C = A + B;
    D = C - B;

    A.Wypisz();
    B.Wypisz();
    C.Wypisz();
    D.Wypisz();

    cout << (D == A) << endl;
    cout << (D <= A) << endl;
    cout << (C == B) << endl;
    cout << (B <= C) << endl;

    cout << endl;

    A.Insert(1);
    cout << (D == A) << endl;
    cout << (D <= A) << endl;

    // A.Insert(5);
    // AddingVisitor v_A;
    // A.Accept(v_A);
    // cout << v_A.sum << endl;

    return 0;
}