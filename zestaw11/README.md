# **Algorytmy i struktury danych** <br/> **Zestaw 11**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementuj podstawowe operacje na grafie.

### Wierzchołek
1. Wierzchołki powinny byc rozróżnialne – nadamy im unikalne numery, będą to kolejne liczby naturalne.

2. Każdy wierzchołek klasy `Vertex` będzie miał pole number, w którym będzie pamiętany unikalny numer tego wierzchołka

3. Można dodać do klasy wierzchołek dodatkowe pola zawierające etykietę wierzchołka (`std::string`)lub jego wagę (`int`)

4. Konstruktor nadaje polu `number` wartość podaną jako argument

5. Metoda `Number()` zwraca wartość pola `number`

### Krawędź
1. Krawędź w grafie skierowanym to para, w nieskierowanym zbiór dwuelementowy.

2. Utworzymy klasę `Edge`, która zawiera wskaźniki do dwóch wierzchołków w polach `v0` i `v1`.
    * Dla grafu skierowanego przyjmujemy, że krawędź wychodzi od `v0` i dochodzi do `v1`.
    * Dla grafu nieskierowanego przyjmujemy, że krawędź `{i,j}` może mieć `v0=i`, `v1=j` lub `v0=j`, `v1=i`

3. Można dodać do klasy krawędź dodatkowe pola zawierające etykietę wierzchołka (`std::string`) lub jego wagę (`int`)

4. Metoda `Mate` zwraca drugi wierzchołek krawędzi (jeśli podamy jako argument `v0` zwróci `v1` i na odwrót)  

### Graf
1. Ponieważ będziemy chcieli implementować grafy skierowane i nieskierowane, stworzymy wspólną klasę bazową z metodą `IsDirected`, która zwraca prawdę dla grafu skierowanego, a fałsz dla nieskierowanego (klasie graf damy pole `bool isDirected`).

2. Przyjmiemy, że wierzchołki są tworzone w konstruktorze klasy graf (podajemy jako argument liczbę wierzchołków). Przyjmujemy, że konstruktorowi grafu podajemy, czy graf będzie skierowany (`true`), czy nieskierowany (`false`).

3. Przyjmujemy, że nie usuwamy wierzchołków z grafu 


4. W naszej implementacji:
    * Macierz sąsiedztwa to pole `adjacencyMatrix`, pamiętamy w nim wskaźniki na krawędzie
    * Oprócz macierzy sąsiedztwa będziemy jeszcze pamiętać wektor wskaźników na wierzchołki (chcemy mieć więcej informacji, niż tylko istnienie wierzchołka czy krawędzi (wagi, etykiety itd.) 

5. `NumberOfEdges`
<br>
Zwraca liczbę krawędzi w grafie.

6. `NumberOfVertices`
<br>
Zwraca liczbę wierzchołków w grafie.

7. `Directed` 
<br>
Zwraca `true` jeśli graf jest skierowany.

8. `SelectVertex`
<br>
Jako argument bierze liczbę (`0 <= i < n`), zwraca wskaźnik `i-tego` wierzchołka grafu.

9. `AddEdge`
<br>
Tworzy nową krawędź od wierzchołka `u` do wierzchołka `v` (można podać ich numery albo wskaźniki), o ile taka wcześniej nie istniała.

10. `IsEdge`
<br>
Zwraca `true` jeśli graf zawiera krawędź łączącą podane wierzchołki.

11. `SelectEdge`
<br>
Zwraca wskaźnik do krawędzi łączącej podane wierzchołki.

12. `EmantingEdges`
<br>
Jako argment bierze bierzchołek grafu. Zwraca iterator przeglądający wszystkie krawędzie wchodzące do podanego wierzchołka.

13. `IncidentEdges`
<br>
Zwraca iterator przeglądający wszystkie krawędzie wchodzące do podanego wierzchołka.

### Uwagi dodatkowe:
1. Konstruktor `GraphAsMatrix(bool b, int n)`:
    * Ustawia pole `isDrected` na `b`
    * Ustawia pole `numberOfVertices` na `n`
    * Tworzy `n` wierzchołków i wstawia wskaźniki na wierzchołki do wektora `vertices`
    * Tworzy macierz `adjacencyMatrix` o rozmiarze `n*n` i wypełnia wartościami `NULL` (bo jeszcze nie mamy żadnych krawędzi)

2. `class AllVerticesIter`:
    * konstruktor tworzy kopię potrzebnych danych, ustawia `current` na `0`
    * `isDone()` zwraca prawdę, gdy przejżymy wszystkie wierzchołki
    * `operator*()` zwraca zawartość bieżącej komórki tablicy wierzchołków
    * `operator++()` zwiększa wartość pola `current`

3. `class AllEdgesIter`:
    * chcemy przejrzeć wszystkie krawędzie w grafie – wszystkie komórki tablicy kwadratowej. Przeglądamy je np. wiersz po wierszu.
    * Pamiętamy w polach klasy `row` i `col` numer wiersza i kolumny (bieżące).
    * Dodatkowa funkcja `next` znajduje następne `row` i `col`, takie, że `adjacencyMatrix[row][col]!=NULL`.
    * Funkcja `next` wykorzystana w `operator++()`
    * Konstruktor klasy inicjalizuje odpowiednio `row` i `col`. Następnie woła funkcję `next`, która znajduje pierwsze `row` i `col` takie, że `adjacencyMatrix[row][col]!=NULL`

----------
<br>
