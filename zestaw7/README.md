# **Algorytmy i struktury danych** <br/> **Zestaw 7**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie nr1**
Zaimplementuj metody klasy BinaryTree

1. `Konstruktor BinaryTree()`
<br>
Tworzy puste drzewo (ustawia `T` na `NULL`)

2. `BuildTree(m)`
<br> 
Wywołuje `BuildTree1(m)` i wynik zapamiętuje w `T`

3. `BuildTree1(m)` 
<br>
Pomcnicza metoda rekurencyjna
    * jeżeli `m=0` to zwróć wartość `NULL`
    * utwórz korzeń
    * zbuduj lewe poddrzewo z *m/2* węzłami
    * zbuduj prawe poddrzewo z *m-(m/2)-1* węzłami
        > Poddrzewa lewe i prawe tworzymy rekurencyjnie – poprzez rekurencyjne wywołanie funkcji `BuildTree1()`.

4. `GetLabel(n)` 
<br>
Zwraca etykietę węzła `n`      

5. `ROOT()` 
<br>
Zwraca węzeł, który jest korzeniem lub `NULL` jeśli drzewo jest puste

6. `LEFT_CHILD(n)` 
<br>
Zwraca lewe dziecko węzła `n`

7. `RIGHT_CHILD(n)` 
<br>
Zwraca prawe dziecko węzła `n`

8. `PARENT(n)` 
<br>
Zwraca rodzica węzła `n` w drzewie `T`
<br>
Jeśli `n` jest korzeniem, to zwraca `NULL`. W przeciwnym wypadku wywołuje funkcję `Parent1(n,T)`

9. `PARENT1(n, T)` 
<br>
Szuka rodzica węzła `n` w poddrzewie `T`. 
<br>
`PARENT1` sprawdza, czy `n` jest lewym lub prawym dzieckiem `T`. Jeśli jest, zwraca `T`, jeśli nie, rekurencyjnie wywołuje `Parent1` dla lewego i prawego poddrzewa i zwraca tą wartość, która jest różna od `NULL`

10. `MAKENULL(n)` 
<br>
Zwalnia pamięć zajętą przez poddrzewo o korzeniu `n`

11. `Destruktor ~BinaryTree()` 
<br>
Wywołuje `MAKENULL(T)`
      
----------
<br>

## **Polecenie nr2**
Napisać funkcje `Preorder()`, `Inorder()` oraz `Postorder()` wypisujące węzły drzewa w określonym porządku.

----------
<br>
