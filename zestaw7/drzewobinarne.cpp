#include <iostream>
using namespace std;

typedef int Telement;
struct Node
{
    Telement info;
    Node *left;
    Node *right;
};
typedef Node *PNode;

class BinaryTree
{
protected:
    PNode T;

public:
    BinaryTree();
    ~BinaryTree();
    PNode PARENT(PNode n);
    PNode PARENT1(PNode n, PNode T);
    PNode LEFT_CHILD(PNode n);
    PNode RIGHT_CHILD(PNode n);
    Telement GetLabel(PNode n);
    PNode BuildTree1(int m);
    void BuildTree(int m);
    PNode& ROOT();
    void MAKENULL(PNode &p);
    void PreOrder(PNode t);
    void InOrder(PNode t);
    void PostOrder(PNode t);
};

BinaryTree::BinaryTree()
{
    T = NULL;
}

BinaryTree::~BinaryTree()
{
    MAKENULL(T);
}

void BinaryTree::MAKENULL(PNode &p)
{
    if (p != NULL)
    {
        if (p->left != NULL)
            MAKENULL(p->left);
        if (p->right != NULL)
            MAKENULL(p->right);
        delete p;
        p = NULL;
    }
}

void BinaryTree::BuildTree(int m)
{
    T = BuildTree1(m);
}

PNode BinaryTree::BuildTree1(int m)
{
    if (m == 0)
    {
        return NULL;
    }
    PNode p = new Node;
    Telement t;

    int m1 = m / 2;
    int m2 = m - m1 - 1;

    cout << "Podaj wartość: ";
    cin >> t;
    p->info = t;
    p->left = BuildTree1(m1);
    p->right = BuildTree1(m2);
    return p;
}

PNode& BinaryTree::ROOT()
{
    
    return T;
}

Telement BinaryTree::GetLabel(PNode n)
{
    if (n != NULL)
        return n->info;
}

PNode BinaryTree::LEFT_CHILD(PNode n)
{
    if (n != NULL)
    {
        return n->left;
    }
}
PNode BinaryTree::RIGHT_CHILD(PNode n)
{
    if (n != NULL)
    {
        return n->right;
    }
}

void BinaryTree::PreOrder(PNode t)
{
    if (t != NULL)
    {
        cout << t->info;
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

void BinaryTree::InOrder(PNode t)
{
    if(t!=NULL){
        InOrder(t->left);
        cout << t->info;
        InOrder(t->right);
    }
}

void BinaryTree::PostOrder(PNode t)
{
    if (t != NULL)
    {
        PostOrder(t->left);
        PostOrder(t->right);
        cout << t->info;
    }
}

PNode BinaryTree::PARENT(PNode n)
{
    if (n == T)
    {
        return NULL;
    }
    return PARENT1(n, T);
}
PNode BinaryTree::PARENT1(PNode n, PNode T)
{
    if (T->left == n || T->right == n)
    {
        return T;
    }
    if (T->left != NULL)
    {
        PNode left = PARENT1(n, T->left);
        if (left != NULL)
        {
            return left;
        }
    }

    if (T->right != NULL)
    {
        PNode right = PARENT1(n, T->right);
        if (right != NULL)
        {
            return right;
        }
    }
}

int main()
{
    BinaryTree *b = new BinaryTree();
    b->BuildTree(9);
    cout << b->GetLabel(b->ROOT());
    cout << b->GetLabel(b->LEFT_CHILD(b->ROOT()));
    cout << b->GetLabel(b->RIGHT_CHILD(b->ROOT())) << endl;

    cout<< b->GetLabel(b->PARENT(b->RIGHT_CHILD(b->ROOT())))<<endl;
    cout<< b->GetLabel(b->PARENT(b->RIGHT_CHILD(b->LEFT_CHILD(b->ROOT()))))<<endl;

    b->PreOrder(b->ROOT());
    cout<<endl;

    b->InOrder(b->ROOT());
    cout<<endl;

    b->PostOrder(b->ROOT());
    cout<<endl;

    b->MAKENULL(b->ROOT());
    b->InOrder(b->ROOT());
    cout<<endl;

    return 0;
}