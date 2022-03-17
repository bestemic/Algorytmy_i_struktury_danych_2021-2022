# **Algorytmy i struktury danych** <br/> **Zestaw 1**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **1.**
Proszę dopisać instrukcje umożliwiające zliczenie wykonanej liczby porównań 

----------
<br>

## **2.**
Proszę zrobić testy i zliczyć liczbę operacji dominujących dla:
<br>
* tablicy posortowanej rosnąco
* tablicy posortowanej malejąco
* tablic z losowymi wartościami

----------
<br>

### **Sortowanie przez proste wstawianie - wskazówki**
* Algorytm wykorzystuje komórkę `a[0]` jako wartownika. Proszę przyjąć `n=10`. Proszę zrobić testy dla tablicy 11 elementowej – wypełnić komórki od 1 do 10, a komórkę 0 zostawić.

* Licznik ma zliczyć, ile razy wykona się porównanie (`x<a[j]`). Czyli instrukcja `licznik++` będzie w pętli `while` zliczać, ile razy się `while` wykona. A porównanie wykona się więcej razy – trzeba jeszcze za `while` wstawić `licznik++`.