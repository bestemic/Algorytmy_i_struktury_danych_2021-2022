#include <iostream>
using namespace std;

typedef int elementtype;

struct celltype {
    elementtype element;
    celltype * next;
};

typedef celltype * position;

class Lista
{
protected :
    position l; // wskaźnik do głowy listy
public:
    Lista(); //konstruktor
    ~Lista(); //destruktor
    void Insert(elementtype x, position p);
    void Delete(position p);
    elementtype Retrieve(position p);
    position Locate(elementtype x);
    position First();
    position Next(position p);
    position Previous(position p);
    position END();
};

Lista::Lista(){
    l=new celltype;
    l->next = nullptr;
}

Lista::~Lista(){    
    while (l->next!=nullptr)
    {
        Delete(l);
    }
}

void Lista::Insert(elementtype x, position p){
    position tmp =p->next;
    p->next = new celltype;
    p->next->element = x;
    p->next->next = tmp;
}

void Lista::Delete(position p){
    position tmp = p->next;
    p->next=p->next->next;
    delete tmp;
}

elementtype Lista::Retrieve(position p){
    return p->next->element;
}

position Lista::Locate(elementtype x){
    position tmp = l;
    while (tmp->next!=nullptr)
    {
        if(tmp->next->element==x){
            return tmp;
        }
        else{
            tmp=tmp->next;
        }
    }

    return tmp;
}

position Lista::First(){
    return l;
}

position Lista::Next(position p){
    return p->next;
}

position Lista::Previous(position p){
    position tmp = l;
    while (tmp->next!=p)
    {
        tmp=tmp->next;
    }
    return tmp;
}

position Lista::END(){
    position tmp = l;
    while(tmp->next!=nullptr){
        tmp= tmp->next;
    }
    return tmp;
}


int main()
{
    Lista l;
    l.Insert(5, l.First());
    cout<<l.Retrieve(l.First())<<endl;
    cout<<endl;

    l.Insert(2, l.First());
    cout<<l.Retrieve(l.First())<<endl;
    cout<<l.Retrieve(l.Next(l.First()))<<endl;
    cout<<endl;

    l.Insert(1, l.Next(l.First()));
    cout<<l.Retrieve(l.First())<<endl;
    cout<<l.Retrieve(l.Next(l.First()))<<endl;
    cout<<l.Retrieve(l.Next(l.Next(l.First())))<<endl;

return 0;
}