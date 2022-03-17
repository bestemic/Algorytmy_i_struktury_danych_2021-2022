# **Algorytmy i struktury danych** <br/> **Zestaw 5**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementować metody klasy Kolejka (reprezentacja cykliczna)

1. `Konstruktor Kolejka()`
<br>
Powinien inicjować zmienne `front` i `rear` tak, aby kolejka była pusta (np.: przyjmujemy `front=0`, `rear=maxlenght-1`).

2. `AddOne()`
<br> 
Zwiększa o jeden zgodnie z relacją modulo

3. `EMPTY()` 
<br>
Zwraca wartość `true`, gdy kolejka jest pusta, zwraca wartość `false`, gdy nie jest pusta

4. `Enqueue(x)` 
<br>
Wstawia element do kolejki (wstawia na koniec !).
    * sprawdź, czy jest miejsce w kolejce (czy kolejka nie jest pełna) Kolejka jest pełna, gdy: (`AddOne(AddOne(Rear)) = Front`)
    * gdy nie jest pełna, to wstaw element `x` do kolejki
        * Zaktualizuj pole `rear` (pole to wskazuje na ostatnio wstawiony element, chcemy, aby wskazywał na pierwszą wolną komórkę)
        * Wstaw elementu `x`

 5. `FrontElem()` 
<br>
Zwraca pierwszy element z kolejki
    * sprawdź, czy kolejka jest pusta
    * jeśli nie jest pusta, to zwróc pierwszy element kolejki (element z komórki o numerze `Front`)

6. `Dequeue()` 
<br>
Usuń elementu z kolejki. Usuwamy element z początku kolejki!
    * sprawdź, czy kolejka jest pusta
    * jeśli nie jest pusta, to zmodyfikuj pole `Front` (zwiększ o 1)
      
----------
<br>
