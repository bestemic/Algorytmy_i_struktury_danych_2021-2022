#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Visitor
{
public:
    virtual void Visit(T &element) = 0;
    virtual bool IsDone() const { return false; }
};

template <typename T>
class Iterator
{
public:
    virtual ~Iterator() {}
    Iterator() { ; }
    virtual bool IsDone() const = 0;
    virtual const T &operator*() = 0;
    virtual void operator++() = 0;
};

class AddingVisitor : public Visitor<int>
{
    int sum;

public:
    void Visit(int &element);
    int suma();
};

class OddVisitor : public Visitor<int>
{
    bool odd;

public:
    OddVisitor() : odd(false){};
    void Visit(int &element);
    bool IsDone() const;
    void reset();
};

template <typename T>
class Container
{
public:
    Container(){};
    virtual int Count() const = 0;
    virtual bool IsEmpty() const { return Count() == 0; };
    virtual bool IsFull() const = 0;
    virtual void MakeNull() = 0;
    virtual void Accept(Visitor<T> &v) const = 0;
};

template <typename T>
class Set : public virtual Container<T>
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
    class Iter;
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

    void Accept(Visitor<int> &v) const;
    Iter &NewIterator();

    // friend- funkcja uzyska prawo dostepu do prywatnych elementów danej klasy.
    friend SetAsArray operator+(SetAsArray const &, SetAsArray const &);
    friend SetAsArray operator-(SetAsArray const &, SetAsArray const &);
    friend SetAsArray operator*(SetAsArray const &, SetAsArray const &);
    friend bool operator==(SetAsArray const &, SetAsArray const &);
    friend bool operator<=(SetAsArray const &, SetAsArray const &);
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

void SetAsArray::Accept(Visitor<int> &v) const
{
    int i = 0;
    for (i; i < universeSize; i++)
    {
        if (array[i])
        {
            v.Visit(i);
            if (v.IsDone())
            {
                break;
            }
        }
    }
    if (i == universeSize)
    {
        i--;
    }
    cout << "Accept zakończyło na komórce: " << i << endl;
}

void AddingVisitor::Visit(int &element)
{
    sum += element;
}

int AddingVisitor::suma()
{
    int tmp = sum;
    sum = 0;
    return tmp;
}

void OddVisitor::Visit(int &element)
{
    if (element % 2 == 1)
    {
        odd = true;
    }
}

bool OddVisitor::IsDone() const
{
    return odd;
}

void OddVisitor::reset()
{
    odd = false;
}

class SetAsArray::Iter : public Iterator<int>
{
    vector<bool> data;
    int universeSize;
    int index;
    int visited;
    int &elements;

public:
    Iter(vector<bool> array, int us, int &count);
    ~Iter() {}
    const int &operator*() override;
    void operator++() override;
    bool IsDone() const override;
};

SetAsArray::Iter::Iter(vector<bool> array, int us, int &count) : elements(count)
{
    data = array;
    universeSize = us;
    visited = 1;
    for (int i = 0; i < us; i++)
    {
        if (array[i])
        {
            index = i;
            break;
        }
    }
}

const int &SetAsArray::Iter::operator*()
{
    return index;
}

void SetAsArray::Iter::operator++()
{
    for (int i = index + 1; i < universeSize; i++)
    {
        if (data[i])
        {
            index = i;
            break;
        }
    }
    visited++;
}

bool SetAsArray::Iter::IsDone() const
{
    if (visited > elements)
    {
        return true;
    }
    else
    {
        return false;
    }
}

SetAsArray::Iter &SetAsArray::NewIterator()
{
    return *new Iter(array, universeSize, count);
}

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

    A.Insert(1);
    cout << (D == A) << endl;
    cout << (D <= A) << endl;

    cout << "\nNowa czesc" << endl;
    A.Insert(5);

    AddingVisitor v_A;
    A.Accept(v_A);
    cout << v_A.suma() << endl;

    SetAsArray E = SetAsArray(10);
    E = A * B;

    AddingVisitor v_E;
    E.Accept(v_E);
    cout << v_E.suma() << endl;

    E.Withdraw(1);
    E.Accept(v_E);
    cout << v_E.suma() << endl;

    cout << "\nKolejna czesc" << endl;
    OddVisitor o_B;
    B.Accept(o_B);
    cout << o_B.IsDone() << endl;
    OddVisitor o_A;
    A.Accept(o_A);
    cout << o_A.IsDone() << endl;

    A.Withdraw(1);
    A.Withdraw(5);
    o_A.reset();
    A.Accept(o_A);
    cout << o_A.IsDone() << endl;

    Iterator<int> &it = A.NewIterator();
    while (!it.IsDone())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
    delete &it;

    it = B.NewIterator();
    while (!it.IsDone())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
    delete &it;

    return 0;
}