# **Projekt skarbonki**

<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **1. Wstęp**

Program wykonany jako projekt zaliczeniowy z przedmiotu Algoryty i Struktury Danych II.

----------
<br>

## **2. Opis problemu**

W zadaniu dostajemy `n` skarbonek. Każdą można otworzyć jej kluczem lub rozbić młotkiem. Właściciel skarbonek powrzucał
klucze do pewnych skarbonek (pamięta który do której). Celem zadania jest ustalenie jaka jest najmniejsza liczba
skarbonek które trzeba rozbić aby dostać się do każdej.

----------
<br>

## **3. Wejście**

W pierwszym wierszu standardowego wejścia otrzymujemy jedną liczbę całkowitą `n` odpowiadającą ilości skarbonek które
posiadamy. Skarbonki i klucze są ponumerowane od 1 do `n`. W kolejnych `n` wierszach: w (`i + 1`)-szym wierszu zapisana
jest numer skarbonki w której znajduje się `i`-ty klucz.

----------
<br>

## **4. Interpretacja problemu**

Analizując treść zadania i przykładowe dane zauważamy że możemy przedstawić nasze skarbonki w postaci grafu skierowanego
o wierchołkach od 1 do `n`. Krawędź będzie skierowana w stronę skarbonki `A` jeśli klucz do skarbonki `B` znajduje się w
skarbonce `A`.Otrzymujemy też `n` krawędzi ponieważ z każdego wierzchołka grafu będzie wychodzić jedna krawędź w stronę innej
skarbonki, w której przechowywany jest klucz. Szczególym przypadkiem do zauważenia jest wierzchołek do któego nie
wchodzi żadna krawędź - oznacza to że w skarbonce reprezentowanej przez ten wierzchołek nie znajduje się żaden
klucz.<br>
Rozważając wyżej wymienione wnioski i to że kluczy mamy tyle ile skarbonek można dojść do wniosku że nasz graf 
będzie składał się z kilku składowych zawierających cykl. Problem sprowadza sie więc do określenia ile takich cykli 
musimy rozbić czyli ile mamy składowych w grafie.<br>
Problem zliczania składowych w grafie skierowanym dla tego problemu możemy uprościć do zliczania składowych grafu 
nieskierowanego, ponieważ uzunięcie zwrotów nie połączy nam tych składowych.

----------
<br>

## **5. Opis rozwiązania**

Aplikacja składa się z kilku klas:
* `App` - wczytywanie danych, inicjalizacja zliczania składowych
* `Graph` - zawiera metody umożliwiające tworzenie grafu, operacja na grafach, przeglądanie grafu
* `Edge` - reprezentuje krawędź
* `Vertex` - reprezentuje wierzchołek

### **Wczytywanie danych**

```java
/**
* Pobiera od użytownika wielkość grafu 
* i tworzy graf o podanych zależnościach.
*/
private static Graph getGraph() {
  Scanner scanner = new Scanner(System.in);
  int vaultsNumber = scanner.nextInt();
  Graph graph = new Graph(vaultsNumber, false);
```
Na początku tworzę skaner który wczytuje z wejścia standardowego liczbę skarbonek. Tworzę też graf nieskierowany o 
ilości wierzchołków równej ilości skarbonek.

```java
  for (int i = 0; i < vaultsNumber; i++) {
     graph.addEdge(i, scanner.nextInt() - 1);
  }
  return graph;
}
```
Następnie wczytuję krawędzie według schematu opisanego w **Interpretacja problemu**, z modyfikacją polegającą na 
przesunięciu numerówm skarbonek i kluczy aby były od 0 do `n-1` ponieważ tak reprezentowany jest graf.

### **Zliczanie składowych grafu**

```java
/**
 * Zlicza ilość składowych grafu wykorzystując algorytm dfs.
 */
public int countComponents() {
  int numberOfComponents = 0;
  boolean[] visited = new boolean[numberOfVertices];
```
Na początku tworzę tablicę ustawioną na wartość `false` która będzie służyła do oznaczania które wierzchołki już 
odwiedziłem.

```java
  for (int i = 0; i < numberOfVertices; i++) {
    if (!visited[i]) {
        numberOfComponents++;
        dfs1(selectVertex(i), visited);
    }
  }
  return numberOfComponents;
}
```
Następnie przechodzię po kolei przez tablicę i sprawdzam czy któryś wierzchołek nie został jescze odwiedzony. Jeśli 
taki znajdę uruchamiam na nim funkcję przeszukiwania grafu `dfs1`, jednocześnie zwiększając licznik składowych.

### **Przeszukiwanie grafu w głąd (DFS)**

```java
/**
 * Funkcja realizująca algorytm DFS przeglądania grafu.
 */
private void dfs1(Vertex v, boolean[] visited) {
  int vertex = v.Number();
  visited[vertex] = true;
  Iterator<Edge> iterator = EmanatingEdgesIter(vertex);
```
Na początku oznaczam obecny wierzchołek jako odwiedzony i pobieram iterator który zwraca wierzchołki wychodzące z 
danego wierzchołka.

```java
  while (!iterator.isDone()) {
    Vertex x = iterator.getElement().V1();
    if (!visited[x.Number()]) {
      dfs1(x, visited);
    }
    iterator.next();
  }
}
```
Jeśli któryś z wychodzących wierzchołków nie został wcześniej odwiedzony to uruchamiam na nim ponownie algorytm DFS.

----------
<br>

## **6. Opis struktur danych**

Graf jest to struktóra składająca się z wierzchołów i krawędzi które łączą wierzchoki. Jeśli jakieś wierzchołki są 
ze sobą połączone krawędzią to są one sąsiadami.
<br><br>
W rozwiązaniu wykorzystałem graf nieskierowany czyli graf którego krawędzie są dwuelementowymi podzbiorami zbioru 
wierzchołków, czyli upraszczając krawędzie nie mają kierunków.
<br><br>
Grafy możemy reprezentować przy użyciu:
* Macierzy sąsiedztwa
* Listy sąsiedztwa
* Macierzy incydencji

W zadaniu graf z któego korzystałem reprezentowany był z użyciem macierzy sąsiedztwa. Jest to macierz kwadratowa `n` na 
`n`, gdzie `n` jest ilością wierzchołków, w której wartość na przeciąciu `i`-tego wiersza i `j`-tej kolumny 
reprezentuje istnitnie krawędzi miedzy wierzchłkiem `i` oraz `j`.
<br><br>
Do poruszania się po grafie wykorzystywałem wzorzec projektowy iterator który pozwala na sekwencyjne odwiedzanie 
elementów jakiejś większej kolekcji bez potrzeby eksponowania jej formy.

----------
<br>

## **7. Złożoność struktur danych**

### **Złożoność pamięciowa**

Do przechowania `n`-wierzchołkowego grafu z użuciem macierzy sąsiedztwa potrzebujemy tablicę `n` na `n`. W programie 
przechowujemy też `n` wierzchołków więc potrzebujemy tablicy `n` elementowej. Liczby te są stałe więc złożoność 
pamięciowa jest równa O(n^2 + n) = O(n^2).

### **Złożoność czasowa**

1. Utworzenie grafu<br>
   Aby utworzyć graf potrzebujemy utworzyć macierz `n` na `n` i wypełnić ją `null`-ami oraz stworzyć `n` wierzchołków. 
   Złożoność czasowa wynosi więc O(n^2 + n) = O(n^2).
2. Dodanie krawędzi<br>
   Utworzenie krawędzi i wstawienie jej do macierzy sąsiedztwa wykonujemy w czasie stałym. Złożoność czasowa wynosi 
   więc O(1). 
3. Pobranie wierzchołka<br>
   Pobranie wierzchołka wykonujemy w czasie stałym. Złożoność czasowa wynosi więc O(1).
4. Pobranie krawędzi<br>
   Pobranie wierzchołka wykonujemy w czasie stałym. Złożoność czasowa wynosi więc O(1).
5. Wyczyszczenie grafu<br>
   Usunięcie zawartości grafu to przejście przez całą macierz sąsiedztwa i ustawienie w każdej komórce `null`-a. 
   Złożoność czasowa wynosi więc O(n^2).
6. Iterator po wierzchołkach<br>
   Przejście przez wszystkie wierzchołki to przejście przez `n` elementową tablicę. Złożoność czasowa wynosi więc O(n).
7. Iterator po krawędziach wchodzących<br>
   Aby przejść przez wszystkie krawędzie wychodzące wierzchołka trzeba przejść przez całą kolumnę macierzy. Złożoność 
   czasowa wynosi więc O(n).
8. Iterator po krawędziach wychodzących<br>
   Aby przejść przez wszystkie krawędzie wychodzące wierzchołka trzeba przejść przez cały wiersz macierzy. Złożoność czasowa wynosi więc O(n).
9. Iterator po wszystkich krawędziach<br>
   Przejście przez wszystkie krawędzie to przejście przez całą macierz sąsiedztwa. Złożoność czasowa wynosi więc O(n^2).

----------
<br>

## **8. Złożoność algorytmów**

### **Złożoność pamięciowa**

Do działania algorytmu DFS potrzebna jest nam tablica zawierająca `n` pól odpowiadajacych informacji czy dany 
wierzchołek został oznaczony. Liczba ta jest stała więc złożoność pamięciowa jest równa O(n).

### **Złożoność czasowa**

Algorytm DFS potrzebuje przejść przez cały wiersz o długości `n` aby odkryć wszystkie krawędzie wychodzące z 
pojedynczego wierzchołka. Mamy `n` wierzchołków. Złożoność czasowa wynosi więc O(n^2).

----------
<br>

## **9. Sposób uruchomienia**
1. Przejść do katalogu `src`
2. Skompilować kod:<br>
`javac App.java Graph.java Edge.java Vertex.java Iterator.java Visitor.java CountingVisitor.java`<br>
3. Uruchomić program:<br>
`java App`<br>

Następnie podajemy ilość skarbonek. A potem kolejno wpisujemy w której skarbonce znajduje się obecny klucz np.:
```text
Podaj liczbę skarbonek
4
Podaj rozmieszczenie kluczy i skarbonek
2
1
2
4
```

----------
<br>

## **10. Literatura**

https://pl.wikipedia.org/wiki/Spójna_składowa_grafu
<br>
https://pl.wikipedia.org/wiki/Przeszukiwanie_w_głąb
<br>
Slajdy z wykładu i ćwiczeń.

----------
<br>

## **11. Wymagania**

**Java** - testowane na wersji **11**<br>