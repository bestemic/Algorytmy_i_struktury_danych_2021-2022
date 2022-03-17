# **Algorytmy i struktury danych** <br/> **Zestaw 2**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementuj podstawowe operacje na liście w reprezentacji tablicowej (plik `ListaTablicowa.cpp`)

1. `First()` 
Zwraca pozycję elementu pierwszego - (indeks 0).

2. `END()`
<br> 
Zwraca pozycję za ostatnim elementem (czyli `last+1`)

3. `Next(p)` 
<br>
zwraca indeks następnego elementu po `p` (czyli `p+1`):
    * jeśli istnieje element następny, to zwróć jego indeks
    * jeśli nie istnieje element następny, to zwróć `-1`

4. `Previous(p)` 
<br>
Zwraca indeks poprzedniego elementu w stosunku do `p` (czyli `p-1`)
    * jeśli istnieje element poprzedni, to zwróć jego indeks
    * jeśli nie istnieje element poprzedni, to zwróć `-1`

5. `Insert(x,p)`
<br>
Wstawia `x` do komórki o numerze `p` ( o ile się da):
    * sprawdź, czy jest miejsce w tablicy
    * sprawdź, czy pozycja `p` jest poprawna
    * przesuń elementy w tablicy, aby komórka `p` była pusta
    * wstaw `x` do komórki `p`
    * zwiększ `last`
    * zwróć `true` gdy operacja wstawiania się powiedzie `false` wpp

6. `Delete(p)` 
<br>
Usuwa element z komórki o numerze `p`:
    * sprawdź, czy pozycja `p` jest poprawna
    * przesuń elementy w "górę" tablicy
    * zmniejsz `last`
    * zwróć `true` gdy operacja usuwania się powiedzie, `false` wpp

7. `Locate(x)`
<br>
Zwraca pozycję elementu `x` w liście (indeks komórki), jeśli `x` występuje w tablicy.
    * zwraca `END()` (pozycję za ostatnim elementem) gdy `x` nie występuje w tablicy

8. `Retrieve(p)`
<br>
Zwraca elementu znajdujący się w liście na pozycji `p` (w komórce `p`), jeśli pozycja p jest poprawna
    * zwraca `MIN` wpp, gdzie `MIN` to wartość która na pewno nie wystąpi w naszej liście. Gdy przechowujemy w liście liczby integer `np. MIN=-10000000`

----------
<br>
