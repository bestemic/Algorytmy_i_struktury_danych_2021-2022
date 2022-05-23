import java.util.Scanner;

public class App {

    /**
     * Pobiera od użytownika wielkość grafu
     * i tworzy graf o podanych zależnościach.
     */
    private static Graph getGraph() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Podaj liczbę skarbonek");
        int vaultsNumber = scanner.nextInt();

        Graph graph = new Graph(vaultsNumber, false);

        System.out.println("Podaj rozmieszczenie kluczy i skarbonek");
        for (int i = 0; i < vaultsNumber; i++) {
            graph.addEdge(i, scanner.nextInt() - 1);
        }
        scanner.close();
        return graph;
    }

    public static void main(String[] args) {
        Graph graph = getGraph();
        System.out.println("Liczba skarbonek do rozbicia: " + graph.countComponents());
    }
}
