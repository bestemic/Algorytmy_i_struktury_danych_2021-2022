#include <iostream>
#include <vector>
using namespace std;

class Vertex
{
    int number;

public:
    int weight;
    string label;
    Vertex(int n);
    int Number() const;
};

class Edge
{
protected:
    Vertex *v0;
    Vertex *v1;

public:
    int weight;
    string label;
    Edge(Vertex *V0, Vertex *V1);
    Vertex *V0() { return v0; };
    Vertex *V1() { return v1; };
    Vertex *Mate(Vertex *v);
};

template <typename T>
class Iterator
{
public:
    virtual ~Iterator() { ; };
    virtual bool IsDone() = 0;
    virtual T &operator*() = 0;
    virtual void operator++() = 0;
};

template <typename T>
class Visitor
{
public:
    virtual void Visit(T *element) = 0;
    virtual bool IsDone() const { return false; }
};

class CountingVisitor : public Visitor<Vertex>
{
    int sum = 0;

public:
    void Visit(Vertex *element);
    int suma();
};

class GraphAsMatrix
{
    vector<Vertex *> vertices;
    vector<vector<Edge *>> adjacencyMatrix;
    bool isDirected;
    int numberOfVertices;
    int numberOfEdges = 0;

    class AllVerticesIter : public Iterator<Vertex>
    {
        GraphAsMatrix &owner;
        int current;

    public:
        AllVerticesIter(GraphAsMatrix &owner);
        bool IsDone();
        Vertex &operator*();
        void operator++();
    };
    class AllEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;
        bool firstIter;

    public:
        void next();
        AllEdgesIter(GraphAsMatrix &owner);
        bool IsDone();
        Edge &operator*();
        void operator++() { next(); }
    };
    class EmanEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;
        bool firstIter;

    public:
        void next();
        EmanEdgesIter(GraphAsMatrix &owner, int v);
        bool IsDone();
        Edge &operator*();
        void operator++() { next(); }
    };
    class InciEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;
        bool firstIter;

    public:
        void next();
        InciEdgesIter(GraphAsMatrix &owner, int v);
        bool IsDone();
        Edge &operator*();
        void operator++() { next(); }
    };

public:
    GraphAsMatrix(int n, bool b);
    int NumberOfVertices();
    bool IsDirected();
    int NumberOfEdges();
    bool IsEdge(int u, int v);
    void MakeNull();
    void AddEdge(int u, int v);
    Edge *SelectEdge(int u, int v);
    Vertex *SelectVertex(int v);
    void DFS(Vertex *v);
    void DFS1(Vertex *v, vector<bool> &visited);
    void DFS_visitor(CountingVisitor *visitor, Vertex *v, std::vector<bool> &visited);
    bool IsConnected();
    void DFS_Spanning_Tree(Vertex *v);
    void DFS_Spanning_Tree_1(Vertex *v, vector<bool> &visited, vector<int> &parent);

    Iterator<Vertex> &VerticesIter();
    Iterator<Edge> &EdgesIter();
    Iterator<Edge> &EmanatingEdgesIter(int v);
    Iterator<Edge> &IncidentEdgesIter(int v);
};

// Vertex implementation
Vertex::Vertex(int n)
{
    number = n;
}

int Vertex::Number() const
{
    return number;
}

// Edge implementation
Edge::Edge(Vertex *V0, Vertex *V1)
{
    v0 = V0;
    v1 = V1;
}

Vertex *Edge::Mate(Vertex *v)
{
    if (v->Number() == v0->Number())
    {
        return v1;
    }
    else
    {
        return v0;
    }
}

// CountingVisitor implementation
void CountingVisitor::Visit(Vertex *element)
{
    sum++;
}

int CountingVisitor::suma()
{
    int tmp = sum;
    sum = 0;
    return tmp;
}

// GraphAsMatrix implementation
GraphAsMatrix::GraphAsMatrix(int n, bool b)
{
    isDirected = b;
    numberOfVertices = n;
    vertices.resize(n);
    adjacencyMatrix.resize(n);

    for (int i = 0; i < n; i++)
    {
        vertices[i] = new Vertex(i);
    }

    for (int i = 0; i < n; i++)
    {
        adjacencyMatrix[i].resize(n);

        for (int j = 0; j < n; j++)
        {
            adjacencyMatrix[i][j] = NULL;
        }
    }
}

int GraphAsMatrix::NumberOfVertices()
{
    return numberOfVertices;
}

bool GraphAsMatrix::IsDirected()
{
    return isDirected;
}

int GraphAsMatrix::NumberOfEdges()
{
    return numberOfEdges;
}

bool GraphAsMatrix::IsEdge(int u, int v)
{
    if (u < numberOfVertices && v < numberOfVertices)
    {
        if (adjacencyMatrix[u][v] != NULL)
        {
            return true;
        }
    }
    return false;
}

void GraphAsMatrix::MakeNull()
{
    numberOfEdges = 0;
    for (int i = 0; i < numberOfVertices; i++)
    {
        for (int j = 0; j < numberOfVertices; j++)
        {
            adjacencyMatrix[i][j] = NULL;
        }
    }
}

void GraphAsMatrix::AddEdge(int u, int v)
{
    if (u < numberOfVertices && v < numberOfVertices)
    {
        if (adjacencyMatrix[u][v] == NULL)
        {
            Edge *edge = new Edge(vertices[u], vertices[v]);
            numberOfEdges++;
            adjacencyMatrix[u][v] = edge;

            edge = new Edge(vertices[v], vertices[u]);
            if (!isDirected)
            {
                adjacencyMatrix[v][u] = edge;
            }
        }
    }
}

Edge *GraphAsMatrix::SelectEdge(int u, int v)
{
    if (u < numberOfVertices && v < numberOfVertices)
    {
        return adjacencyMatrix[u][v];
    }
}

Vertex *GraphAsMatrix::SelectVertex(int v)
{
    if (v >= 0 && v < numberOfVertices)
    {
        return vertices[v];
    }
}

void GraphAsMatrix::DFS(Vertex *v)
{
    vector<bool> visited(numberOfVertices, false);
    DFS1(v, visited);

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (visited[i] == false)
        {
            DFS1(SelectVertex(i), visited);
        }
    }
}

void GraphAsMatrix::DFS1(Vertex *v, vector<bool> &visited)
{
    int vertex = v->Number();
    visited[vertex] = true;
    cout << "Odwiedzam wierzchołek: " << vertex << endl;

    Iterator<Edge> &iterator = EmanatingEdgesIter(vertex);
    while (!iterator.IsDone())
    {
        Vertex *x = (*iterator).V1();
        if (visited[x->Number()] == false)
        {
            DFS1(x, visited);
        }
        ++iterator;
    }
    delete &iterator;
}

void GraphAsMatrix::DFS_Spanning_Tree(Vertex *v)
{
    if (!IsConnected())
    {
        cout << "Nie jest spójny";
        abort();
    }

    vector<bool> visited(numberOfVertices, false);
    vector<int> parent(numberOfVertices, -1);
    DFS_Spanning_Tree_1(v, visited, parent);
}

void GraphAsMatrix::DFS_Spanning_Tree_1(Vertex *v, vector<bool> &visited, vector<int> &parent)
{
    int vertex = v->Number();
    visited[vertex] = true;

    Iterator<Edge> &iterator = EmanatingEdgesIter(vertex);
    while (!iterator.IsDone())
    {
        Vertex *u = (*iterator).V1();
        if (visited[u->Number()] == false)
        {
            parent[u->Number()] = vertex;
            cout << "Rodzicem " << u->Number() << " jest " << vertex << endl;
            DFS_Spanning_Tree_1(u, visited, parent);
        }
        ++iterator;
    }
    delete &iterator;
}

void GraphAsMatrix::DFS_visitor(CountingVisitor *visitor, Vertex *v, std::vector<bool> &visited)
{
    int vertex = v->Number();
    visited[vertex] = true;
    visitor->Visit(v);

    Iterator<Edge> &iterator = EmanatingEdgesIter(vertex);
    while (!iterator.IsDone())
    {
        Vertex *x = (*iterator).V1();
        if (visited[x->Number()] == false)
        {
            DFS_visitor(visitor, x, visited);
        }
        ++iterator;
    }
    delete &iterator;
}

bool GraphAsMatrix::IsConnected()
{
    CountingVisitor *visitor = new CountingVisitor;
    if (IsDirected())
    {
        for (int i = 0; i < NumberOfVertices(); i++)
        {
            vector<bool> visited(numberOfVertices, false);
            DFS_visitor(visitor, SelectVertex(i), visited);
            if (visitor->suma() != NumberOfVertices())
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        vector<bool> visited(numberOfVertices, false);
        DFS_visitor(visitor, SelectVertex(0), visited);
        if (visitor->suma() == NumberOfVertices())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

Iterator<Vertex> &GraphAsMatrix::VerticesIter()
{
    return *new AllVerticesIter(*this);
}

Iterator<Edge> &GraphAsMatrix::EdgesIter()
{
    return *new AllEdgesIter(*this);
}

Iterator<Edge> &GraphAsMatrix::EmanatingEdgesIter(int v)
{
    return *new EmanEdgesIter(*this, v);
}

Iterator<Edge> &GraphAsMatrix::IncidentEdgesIter(int v)
{
    return *new InciEdgesIter(*this, v);
}

// AllVerticesIter implementation
GraphAsMatrix::AllVerticesIter::AllVerticesIter(GraphAsMatrix &owner) : owner(owner)
{
    current = 0;
}

Vertex &GraphAsMatrix::AllVerticesIter::operator*()
{
    return *owner.vertices[current];
}

bool GraphAsMatrix::AllVerticesIter::IsDone()
{
    return !(current < owner.NumberOfVertices());
}

void GraphAsMatrix::AllVerticesIter::operator++()
{
    current++;
}

// AllEdgesIter implementation
GraphAsMatrix::AllEdgesIter::AllEdgesIter(GraphAsMatrix &owner) : owner(owner)
{
    row = 0;
    col = 0;
    firstIter = true;
    next();
}

Edge &GraphAsMatrix::AllEdgesIter::operator*()
{
    return *owner.adjacencyMatrix[row][col];
}

bool GraphAsMatrix::AllEdgesIter::IsDone()
{

    if (row < owner.NumberOfVertices() && col < owner.NumberOfVertices())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GraphAsMatrix::AllEdgesIter::next()
{
    while (true)
    {

        if (row == 0 && col == 0 && firstIter)
        {
            if (owner.adjacencyMatrix[row][col] != NULL)
            {
                firstIter = false;
                break;
            }
        }
        if (row == owner.NumberOfVertices() - 1 && col == owner.NumberOfVertices() - 1)
        {
            row = owner.NumberOfVertices();
            break;
        }

        if (col == owner.NumberOfVertices() - 1)
        {
            if (row == owner.NumberOfVertices() - 1)
            {
                break;
            }
            else
            {
                col = 0;
                row++;
            }
        }
        else
        {
            col++;
        }

        if (owner.adjacencyMatrix[row][col] != NULL)
        {
            break;
        }
    }
}

// EmanEdgesIter implementation
GraphAsMatrix::EmanEdgesIter::EmanEdgesIter(GraphAsMatrix &owner, int v) : owner(owner)
{
    row = v;
    col = 0;
    firstIter = true;
    next();
}

Edge &GraphAsMatrix::EmanEdgesIter::operator*()
{
    return *owner.adjacencyMatrix[row][col];
}

bool GraphAsMatrix::EmanEdgesIter::IsDone()
{
    if (col < owner.NumberOfVertices())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GraphAsMatrix::EmanEdgesIter::next()
{
    while (true)
    {
        if (col == 0 && firstIter)
        {
            if (owner.adjacencyMatrix[row][col] != NULL)
            {
                firstIter = false;
                break;
            }
        }

        if (col == owner.NumberOfVertices() - 1)
        {
            col = owner.NumberOfVertices();
            break;
        }

        col++;

        if (owner.adjacencyMatrix[row][col] != NULL)
        {
            break;
        }
    }
}

// InciEdgesIter implementation
GraphAsMatrix::InciEdgesIter::InciEdgesIter(GraphAsMatrix &owner, int v) : owner(owner)
{
    row = 0;
    col = v;
    firstIter = true;
    next();
}

Edge &GraphAsMatrix::InciEdgesIter::operator*()
{
    return *owner.adjacencyMatrix[row][col];
}

bool GraphAsMatrix::InciEdgesIter::IsDone()
{
    if (row < owner.NumberOfVertices())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GraphAsMatrix::InciEdgesIter::next()
{
    while (true)
    {
        if (row == 0 && firstIter)
        {
            if (owner.adjacencyMatrix[row][col] != NULL)
            {
                firstIter = false;
                break;
            }
        }
        if (row == owner.NumberOfVertices() - 1)
        {
            row = owner.NumberOfVertices();
            break;
        }

        row++;

        if (owner.adjacencyMatrix[row][col] != NULL)
        {
            break;
        }
    }
}

int main()
{
    // Graf skierowany
    cout << "Graf skierowany" << endl;
    GraphAsMatrix graf1 = GraphAsMatrix(10, true);

    cout << "Liczba wierzcholkow : " << graf1.NumberOfVertices() << endl;
    cout << "Liczba krawedzi : " << graf1.NumberOfEdges() << endl;

    Vertex *v1 = graf1.SelectVertex(2);
    cout << "Numer wierzcholka : " << v1->Number() << endl;
    v1->weight = v1->Number() * v1->Number();
    cout << "Waga wierzcholka : " << v1->weight << endl;

    graf1.AddEdge(1, 2);
    graf1.AddEdge(1, 2);
    graf1.AddEdge(2, 3);
    graf1.AddEdge(3, 4);
    graf1.AddEdge(9, 9);

    cout << "Liczba wierzcholkow : " << graf1.NumberOfVertices() << endl;
    cout << "Liczba krawedzi : " << graf1.NumberOfEdges() << endl;
    cout << "Czy istnieje 1, 1 " << graf1.IsEdge(1, 1) << endl;
    cout << "Czy istnieje 1, 2 " << graf1.IsEdge(1, 2) << endl;
    cout << "Czy istnieje 2, 1 " << graf1.IsEdge(2, 1) << endl;

    for (int i = 1; i < 9; i++)
    {
        Edge *e = graf1.SelectEdge(i, i + 1);
        if (e == NULL)
            cout << "Krawedz nie istnieje" << endl;
        else
        {
            cout << "V0: " << e->V0()->Number() << endl;
            cout << "V1: " << e->V1()->Number() << endl;
            cout << "Mate0 : " << e->Mate(e->V0())->Number() << endl;
            cout << "Mate1 : " << e->Mate(e->V1())->Number() << endl;
            e->weight = e->V0()->Number() + e->V1()->Number();
            cout << "Waga krawedzi : " << e->weight << endl;
        }
        cout << "----------------------" << endl;
    }

    cout << endl;

    // Graf nieskierowany
    cout << "Graf nieskierowany" << endl;
    GraphAsMatrix graf2 = GraphAsMatrix(10, false);

    cout << "Liczba wierzcholkow : " << graf2.NumberOfVertices() << endl;
    cout << "Liczba krawedzi : " << graf2.NumberOfEdges() << endl;

    Vertex *v2 = graf2.SelectVertex(2);
    cout << "Numer wierzcholka : " << v2->Number() << endl;
    v2->weight = v2->Number() * v2->Number();
    cout << "Waga wierzcholka : " << v2->weight << endl;

    graf2.AddEdge(1, 2);
    graf2.AddEdge(1, 2);
    graf2.AddEdge(2, 3);
    graf2.AddEdge(3, 4);
    graf2.AddEdge(9, 9);

    cout << "Liczba wierzcholkow : " << graf2.NumberOfVertices() << endl;
    cout << "Liczba krawedzi : " << graf2.NumberOfEdges() << endl;
    cout << "Czy istnieje 1, 1 " << graf2.IsEdge(1, 1) << endl;
    cout << "Czy istnieje 1, 2 " << graf2.IsEdge(1, 2) << endl;
    cout << "Czy istnieje 2, 1 " << graf2.IsEdge(2, 1) << endl;

    for (int i = 1; i < 9; i++)
    {
        Edge *e = graf2.SelectEdge(i, i + 1);
        if (e == NULL)
            cout << "Krawedz nie istnieje" << endl;
        else
        {
            cout << "V0: " << e->V0()->Number() << endl;
            cout << "V1: " << e->V1()->Number() << endl;
            cout << "Mate0 : " << e->Mate(e->V0())->Number() << endl;
            cout << "Mate1 : " << e->Mate(e->V1())->Number() << endl;
            e->weight = e->V0()->Number() + e->V1()->Number();
            cout << "Waga krawedzi : " << e->weight << endl;
        }
        cout << "----------------------" << endl;
    }

    cout << endl;
    cout << "Iterator po wieżchołkach graf 1" << endl;

    Iterator<Vertex> &v_it = graf1.VerticesIter();
    while (!v_it.IsDone())
    {
        cout << "Numer: " << (*v_it).Number() << " Waga: " << (*v_it).weight << endl;
        ++v_it;
    }
    delete &v_it;

    cout << endl;
    cout << "Iterator po wieżchołkach graf 2" << endl;

    v_it = graf1.VerticesIter();
    while (!v_it.IsDone())
    {
        cout << "Numer: " << (*v_it).Number() << " Waga: " << (*v_it).weight << endl;
        ++v_it;
    }
    delete &v_it;

    graf1.AddEdge(3, 5);
    graf1.AddEdge(8, 3);
    graf1.AddEdge(5, 2);
    graf2.AddEdge(3, 5);
    graf2.AddEdge(8, 3);
    graf2.AddEdge(5, 2);

    cout << endl;
    cout << endl;
    cout << "Iterator po krawędziach graf 1" << endl;
    Iterator<Edge> &e_it = graf1.EdgesIter();
    while (!e_it.IsDone())
    {
        cout << "Krawedz: " << (*e_it).V0()->Number() << " ------ " << (*e_it).V1()->Number() << endl;
        ++e_it;
    }
    delete &e_it;

    cout << endl;
    cout << "Iterator po krawędziach graf 2" << endl;

    e_it = graf2.EdgesIter();
    while (!e_it.IsDone())
    {
        cout << "Krawedz: " << (*e_it).V0()->Number() << " ------ " << (*e_it).V1()->Number() << endl;
        ++e_it;
    }
    delete &e_it;

    cout << endl;
    cout << endl;
    cout << "Iterator po krawędziach wychodzących graf 1" << endl;
    e_it = graf1.EmanatingEdgesIter(3);
    while (!e_it.IsDone())
    {
        cout << "Krawedz: " << (*e_it).V0()->Number() << " ------ " << (*e_it).V1()->Number() << endl;
        ++e_it;
    }
    delete &e_it;

    cout << endl;
    cout << "Iterator po krawędziach wychodzących graf 2" << endl;

    e_it = graf2.EmanatingEdgesIter(3);
    while (!e_it.IsDone())
    {
        cout << "Krawedz: " << (*e_it).V0()->Number() << " ------ " << (*e_it).V1()->Number() << endl;
        ++e_it;
    }
    delete &e_it;

    cout << endl;
    cout << endl;
    cout << "Iterator po krawędziach wchodzących graf 1" << endl;
    e_it = graf1.IncidentEdgesIter(2);
    while (!e_it.IsDone())
    {
        cout << "Krawedz: " << (*e_it).V0()->Number() << " ------ " << (*e_it).V1()->Number() << endl;
        ++e_it;
    }
    delete &e_it;

    cout << endl;
    cout << "Iterator po krawędziach wchodzących graf 2" << endl;

    e_it = graf2.IncidentEdgesIter(2);
    while (!e_it.IsDone())
    {
        cout << "Krawedz: " << (*e_it).V0()->Number() << " ------ " << (*e_it).V1()->Number() << endl;
        ++e_it;
    }
    delete &e_it;

    // DFS

    cout << endl;

    GraphAsMatrix *graph = new GraphAsMatrix(10, false);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(3, 7);
    graph->AddEdge(4, 5);
    graph->AddEdge(5, 9);
    graph->AddEdge(9, 9);
    graph->AddEdge(6, 8);
    graph->AddEdge(8, 6);
    graph->AddEdge(0, 8);
    graph->DFS(graph->SelectVertex(0));
    delete graph;

    cout << endl;

    graph = new GraphAsMatrix(10, true);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(3, 7);
    graph->AddEdge(4, 5);
    graph->AddEdge(5, 9);
    graph->AddEdge(9, 9);
    graph->AddEdge(6, 8);
    graph->AddEdge(8, 6);
    graph->AddEdge(0, 8);
    graph->DFS(graph->SelectVertex(0));
    delete graph;

    cout << endl;

    graph = new GraphAsMatrix(10, false);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(3, 7);
    graph->AddEdge(4, 5);
    graph->AddEdge(5, 9);
    graph->AddEdge(9, 9);
    graph->AddEdge(6, 8);
    graph->AddEdge(8, 6);
    graph->AddEdge(0, 8);
    cout << "graf jest spojny=" << graph->IsConnected() << endl;
    graph->AddEdge(0, 8);
    cout << "graf jest spojny=" << graph->IsConnected() << endl;
    delete graph;

    cout << endl;

    graph = new GraphAsMatrix(10, true);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(3, 7);
    graph->AddEdge(4, 5);
    graph->AddEdge(5, 9);
    graph->AddEdge(9, 9);
    graph->AddEdge(6, 8);
    graph->AddEdge(8, 6);
    graph->AddEdge(0, 8);
    graph->AddEdge(6, 0);
    graph->AddEdge(9, 0);
    cout << "graf jest spojny=" << graph->IsConnected() << endl;
    graph->AddEdge(7, 0);
    cout << "graf jest spojny=" << graph->IsConnected() << endl;

    cout << endl;
    cout << "DRZEWO ROZPINAJĄCE" << endl;

    graph = new GraphAsMatrix(10, false);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(3, 7);
    graph->AddEdge(4, 5);
    graph->AddEdge(5, 9);
    graph->AddEdge(9, 9);
    graph->AddEdge(6, 8);
    graph->AddEdge(8, 6);
    graph->AddEdge(0, 8);

    graph->DFS_Spanning_Tree(graph->SelectVertex(0));
    cout << endl;

    graph->AddEdge(3, 9);
    graph->AddEdge(5, 7);
    graph->AddEdge(9, 8);
    graph->DFS_Spanning_Tree(graph->SelectVertex(0));

    return 0;
}