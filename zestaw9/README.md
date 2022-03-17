# **Algorytmy i struktury danych** <br/> **Zestaw 9**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementuj podstawowe operacje na kolejce priorytetowej za pomocą kopca pamiętanego w tablicy.

1. `Konstruktor`
<br>
Ustawia pole `count` na `0`, rozmiar wektora `data` na `n`

2. `Makenull()`
<br> 
Ustawia licznik `count` na `0`. Zakładamy, że kontener NIE jest odpowiedzialny za usunięcie obiektów, które zawiera

3. `FindMin()` 
<br>
Zwraca wartość najmniejszą (jeśli stos nie jest pusty), czyli wartość znajdującą się w komórce `0`

4. `Enqueue(x)` 
<br>
Wstawianie elementu do kopca binarnego:
    * Jeśli nie ma miejsca w wektorze, wykonaj `resize`
    * Wstaw nowy element do kolejki priorytetowej
<br>
Podczas operacji wstawiania elementu do kopca binarnego spełnione muszą zostać następujące wymagania:
    * Wynikowe drzewo musi mieć odpowiedni kształt
    * Warunek stogu musi być spełniony

 5. `DequeueMin()` 
<br>
Usuwanie elementu najmniejszego

----------
<br>
