# **Algorytmy i struktury danych** <br/> **Zestaw 8**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementuj metody klasy dictionary

1. `Konstruktor`
<br>
Wypełnia tablice wartościami `NULL`

2. `Destruktor`
<br> 
Dla każdej komórki tablicy w pętli usuń elementy odpowiedniej listy

3. `Makenull() ` 
<br>
Dla każdej komórki tablicy:
    * w pętli usuń elementy odpowiedniej listy
    * wstaw wartośc `NULL` do tablicy

4. `Member(x)` 
<br>
Oblicz, w której liście może znajdować się element `x` wywołując funkcję `H(x)` przegladaj odpowiednią listę w poszukiwaniu elementu `x`

 5. `Insert(x)` 
<br>
Sprawdź, czy element `x` jest w słowniku (wywołując `Member(x)`). Jeśli nie ma elementu `x` w słowniku, to:
    * oblicz, do której listy należy wstawic element `x` (wywołując funkcję `H(x)`)
    * wstaw element `x` na poczatek odpowiedniej listy 

6. `Delete(x)` 
<br>
Oblicz, w której liście może znajdować się element `x` wywołując funkcję `H(x)` (`int bucket=H(x)`). Jeśli ta lista nie jest pusta to:
* jesli `x` jest pierwszym elementem tej listy,usuń element z początku listy aktualizując `D[bucket]`
* jesli `x` nie jest pierwszym elementem tej listy, przeglądaj listę aby znaleźć element i usuń go
      
7. `H(x)` 
<br>
Pobierz kod ASCII pierwszego znaku słowa `x`: `(int (x[0])) modulo rozmiar tablicy`

----------
<br>
