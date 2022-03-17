# **Algorytmy i struktury danych** <br/> **Zestaw 3**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementuj operacje na liście (lista wskaźnikowa z głową)

1. `First()` 
Pozycja elementu pierwszego - wskaźnik do głowy listy

2. `END()`
<br> 
Zwraca pozycję za ostatnim elementem (czyli wskażnik do ostatniego elementu)

3. `Next(p)` 
<br>
zwraca wskaźnik do nastepnego elementu po `p` (czyli `p->next`)

4. `Previous(p)` 
<br>
Zwraca pozycję poprzedniego elementu w stosunku do `p` (przegląda całą listę, aby znależć takie `tmp`, że `tmp->next==p`)


5. `Insert(x,p)`
<br>
Wstawia `x` na pozycję `p`-czyli wstawiamy nową komórkę za komórką wskazywaną przez `p`

6. `Delete(p)` 
<br>
Usuwa z pozycji `p`, czyli usuwa komórkę wskazywaną przez `p->next`

7. `Locate(x)`
<br>
Zwraca pozycję elementu `x` w liście, czyli taką pozycję `p`, że `p->next->element==x` (pętla po wszystkich elementach listy, aż znajdziemy `p` takie, że `p->next->element==x`)

8. `Retrieve(p)`
<br>
Zwraca elementu znajdujący się w liście na pozycji `p` (w komórce `p->next`), jeśli `p->next!=NULL`

----------
<br>
