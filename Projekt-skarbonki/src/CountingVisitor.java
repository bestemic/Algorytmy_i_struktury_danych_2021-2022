public class CountingVisitor extends Visitor<Vertex> {
    // == private fields ==
    private int counter;

    // == constructor ==
    public CountingVisitor() {
        counter = 0;
    }

    // == public methods ==
    @Override
    public void visit(Vertex element) {
        counter++;
    }

    public int getVisitedElements() {
        int tmp = counter;
        counter = 0;
        return tmp;
    }
}
