import java.util.ArrayList;
import java.util.List;

public class Graph {
    // == fields ==
    private final List<Vertex> vertices;
    private final List<List<Edge>> adjacencyMatrix;
    private final boolean isDirected;
    private final int numberOfVertices;
    private int numberOfEdges = 0;

    // == constructor ==

    /**
     * Tworzy wierzchołki i inicjalizuje macierz sąsiedztwa.
     */
    public Graph(int n, boolean b) {
        isDirected = b;
        numberOfVertices = n;
        vertices = new ArrayList<>(n);
        adjacencyMatrix = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            vertices.add(new Vertex(i));
        }

        for (int i = 0; i < n; i++) {
            adjacencyMatrix.add(new ArrayList<>(n));

            for (int j = 0; j < n; j++) {
                adjacencyMatrix.get(i).add(null);
            }
        }
    }

    // == public methods ==

    /**
     * Zwraca liczbę wierzchołków.
     */
    public int numberOfVertices() {
        return numberOfVertices;
    }

    /**
     * Zwraca informacje czy graf jest skierowany.
     */
    public boolean isDirected() {
        return isDirected;
    }

    /**
     * Zwraca liczbę krawędzi.
     */
    public int numberOfEdges() {
        return numberOfEdges;
    }

    /**
     * Zwraca informacje czy krawędź istnieje
     */
    public boolean isEdge(int u, int v) {
        if (u < numberOfVertices && v < numberOfVertices) {
            return adjacencyMatrix.get(u).get(v) != null;
        }
        return false;
    }

    /**
     * Czyści graf.
     */
    public void makeNull() {
        numberOfEdges = 0;

        for (int i = 0; i < numberOfVertices; i++) {
            for (int j = 0; j < numberOfVertices; j++) {
                adjacencyMatrix.get(i).set(j, null);
            }
        }
    }

    /**
     * Dodaje krawędź do grafu.
     */
    public void addEdge(int u, int v) {
        if (u < numberOfVertices && v < numberOfVertices) {
            if (adjacencyMatrix.get(u).get(v) == null) {
                Edge edge = new Edge(vertices.get(u), vertices.get(v));
                numberOfEdges++;
                adjacencyMatrix.get(u).set(v, edge);

                edge = new Edge(vertices.get(v), vertices.get(u));
                if (!isDirected) {
                    adjacencyMatrix.get(v).set(u, edge);
                }
            }
        }
    }

    /**
     * Zwraca krawędź.
     */
    public Edge selectEdge(int u, int v) {
        if (u < numberOfVertices && v < numberOfVertices) {
            return adjacencyMatrix.get(u).get(v);
        }
        return null;
    }

    /**
     * Zwraca wierzchołek.
     */
    public Vertex selectVertex(int v) {
        if (v >= 0 && v < numberOfVertices) {
            return vertices.get(v);
        }
        return null;
    }

    /**
     * Zlicza ilość składowych grafu wykorzystując algorytm dfs.
     */
    public int countComponents() {
        int numberOfComponents = 0;
        boolean[] visited = new boolean[numberOfVertices];

        for (int i = 0; i < numberOfVertices; i++) {
            if (!visited[i]) {
                numberOfComponents++;
                dfs1(selectVertex(i), visited);
            }
        }
        return numberOfComponents;
    }

    /**
     * Przeszukiwanie w głąb przez wszystkie wierzchołki.
     */
    public void dfs(Vertex v) {
        boolean[] visited = new boolean[numberOfVertices];
        dfs1(v, visited);

        for (int i = 0; i < numberOfVertices; i++) {
            if (!visited[i]) {
                dfs1(selectVertex(i), visited);
            }
        }
    }

    /**
     * Uruchamia na grafie DFS i sprawdza czy graf jest spójny.
     */
    public boolean isConnected() {
        CountingVisitor visitor = new CountingVisitor();
        if (isDirected()) {
            for (int i = 0; i < numberOfVertices(); i++) {
                boolean[] visited = new boolean[numberOfVertices];
                dfsVisitor(visitor, selectVertex(i), visited);

                if (visitor.getVisitedElements() != numberOfVertices()) {
                    return false;
                }
            }
            return true;
        } else {
            boolean[] visited = new boolean[numberOfVertices];
            dfsVisitor(visitor, selectVertex(0), visited);

            return visitor.getVisitedElements() == numberOfVertices();
        }
    }

    /**
     * Zwraca iterator po wierzchołkach.
     */
    public Iterator<Vertex> VerticesIter() {
        return new AllVerticesIter(this);
    }

    /**
     * Zwraca iterator po krawędziach.
     */
    public Iterator<Edge> EdgesIter() {
        return new AllEdgesIter(this);
    }

    /**
     * Zwraca iterator po krawędziach wychodzących.
     */
    public Iterator<Edge> EmanatingEdgesIter(int v) {
        return new EmanEdgesIter(this, v);
    }

    /**
     * Zwraca iterator po krawędziach wchodzących.
     */
    public Iterator<Edge> IncidentEdgesIter(int v) {
        return new InciEdgesIter(this, v);
    }

    // == private method ==

    /**
     * Funkcja realizująca algorytm DFS przeglądania grafu.
     */
    private void dfs1(Vertex v, boolean[] visited) {
        int vertex = v.Number();
        visited[vertex] = true;

        Iterator<Edge> iterator = EmanatingEdgesIter(vertex);
        while (!iterator.isDone()) {
            Vertex x = iterator.getElement().V1();
            if (!visited[x.Number()]) {
                dfs1(x, visited);
            }
            iterator.next();
        }
    }

    /**
     * Funkcja realizująca algorytm DFS przeglądania grafu z wywoływaniem wizytatora.
     */
    private void dfsVisitor(CountingVisitor visitor, Vertex v, boolean[] visited) {
        int vertex = v.Number();
        visited[vertex] = true;
        visitor.visit(v);

        Iterator<Edge> iterator = EmanatingEdgesIter(vertex);
        while (!iterator.isDone()) {
            Vertex x = iterator.getElement().V1();
            if (!visited[x.Number()]) {
                dfsVisitor(visitor, x, visited);
            }
            iterator.next();
        }
    }

    // == inner classes ==

    /**
     * Klasa iteratora po wierzchołkach.
     */
    private class AllVerticesIter extends Iterator<Vertex> {
        // == fields ==
        private final Graph owner;
        private int current;

        // == constructor ==
        public AllVerticesIter(Graph owner) {
            this.owner = owner;
            current = 0;
        }

        // == public methods ==
        @Override
        public boolean isDone() {
            return !(current < owner.numberOfVertices());
        }

        @Override
        public Vertex getElement() {
            return owner.vertices.get(current);
        }

        @Override
        public void next() {
            current++;
        }
    }

    /**
     * Klasa iteratora po krawędziach.
     */
    private class AllEdgesIter extends Iterator<Edge> {
        // == fields ==
        private final Graph owner;
        private int row;
        private int col;
        private boolean valueOnFirstElement;

        // == constructor ==
        public AllEdgesIter(Graph owner) {
            this.owner = owner;
            row = 0;
            col = 0;
            valueOnFirstElement = true;
            next();
        }

        // == public methods ==
        @Override
        public boolean isDone() {
            return row >= owner.numberOfVertices() || col >= owner.numberOfVertices();
        }

        @Override
        public Edge getElement() {
            return owner.adjacencyMatrix.get(row).get(col);
        }

        @Override
        public void next() {
            while (true) {
                if (row == 0 && col == 0 && valueOnFirstElement) {
                    if (owner.adjacencyMatrix.get(row).get(col) != null) {
                        valueOnFirstElement = false;
                        break;
                    }
                }
                if (row == owner.numberOfVertices() - 1 && col == owner.numberOfVertices() - 1) {
                    row = owner.numberOfVertices();
                    break;
                }

                if (col == owner.numberOfVertices() - 1) {
                    if (row == owner.numberOfVertices() - 1) {
                        break;
                    } else {
                        col = 0;
                        row++;
                    }
                } else {
                    col++;
                }

                if (owner.adjacencyMatrix.get(row).get(col) != null) {
                    break;
                }
            }
        }
    }

    /**
     * Klasa iteratora po krawędziach wychodzących.
     */
    private class EmanEdgesIter extends Iterator<Edge> {
        // == fields ==
        private final Graph owner;
        private int row;
        private int col;
        private boolean valueOnFirstElement;

        // == constructor ==
        public EmanEdgesIter(Graph owner, int v) {
            this.owner = owner;
            row = v;
            col = 0;
            valueOnFirstElement = true;
            next();
        }

        // == public methods ==
        @Override
        public boolean isDone() {
            return col >= owner.numberOfVertices();
        }

        @Override
        public Edge getElement() {
            return owner.adjacencyMatrix.get(row).get(col);
        }

        @Override
        public void next() {
            while (true) {
                if (col == 0 && valueOnFirstElement) {
                    if (owner.adjacencyMatrix.get(row).get(col) != null) {
                        valueOnFirstElement = false;
                        break;
                    }
                }
                if (col == owner.numberOfVertices() - 1) {
                    col = owner.numberOfVertices();
                    break;
                }

                col++;

                if (owner.adjacencyMatrix.get(row).get(col) != null) {
                    break;
                }
            }
        }
    }

    /**
     * Klasa iteratora po krawędziach wchodzących.
     */
    private class InciEdgesIter extends Iterator<Edge> {
        // == fields ==
        private final Graph owner;
        private int row;
        private int col;
        private boolean valueOnFirstElement;

        // == constructor ==
        public InciEdgesIter(Graph owner, int v) {
            this.owner = owner;
            row = 0;
            col = v;
            valueOnFirstElement = true;
            next();
        }

        // == public methods ==
        @Override
        public boolean isDone() {
            return row >= owner.numberOfVertices();
        }

        @Override
        public Edge getElement() {
            return owner.adjacencyMatrix.get(row).get(col);
        }

        @Override
        public void next() {
            while (true) {
                if (row == 0 && valueOnFirstElement) {
                    if (owner.adjacencyMatrix.get(row).get(col) != null) {
                        valueOnFirstElement = false;
                        break;
                    }
                }
                if (row == owner.numberOfVertices() - 1) {
                    row = owner.numberOfVertices();
                    break;
                }

                row++;

                if (owner.adjacencyMatrix.get(row).get(col) != null) {
                    break;
                }
            }
        }
    }
}
