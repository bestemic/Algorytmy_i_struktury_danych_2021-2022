public abstract class Visitor<T> {
    // == public methods ==
    public abstract void visit(T element);
    public boolean isDone (){return false;}
}
