public class Edge {
    // == fields ==
    protected Vertex v0;
    protected Vertex v1;
    public int weight;
    public String label;

    // == constructor ==
    public Edge(Vertex v0, Vertex v1) {
        this.v0 = v0;
        this.v1 = v1;
    }

    // == public methods ==
    public Vertex V0() {
        return v0;
    }

    public Vertex V1() {
        return v1;
    }

    public Vertex Mate(Vertex v) {
        if (v.Number() == v0.Number()) {
            return v1;
        } else {
            return v0;
        }
    }
}
