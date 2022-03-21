# **Algorytmy i struktury danych** <br/> **Zestaw 10**
<br>
<div style="text-align: right"><b>Przemysław Pawlik</b></div>

## **Polecenie**
Zaimplementuj podstawowe operacje na zbiorze.

1. `SetAsArray (unsigned int N);` 
<br>
Konstruktor pobiera jeden argument `N` oznaczający rozmiar zbioru uniwersalnego *(czyli również rozmiar tablicy*
boolowskiej). 
<br>
Konstruktor tworzy pusty zbiór inicjalizując tablicę wartościami `false`. 
<br>
<br>
Złożoność czasowa konstruktora O(N). 

2. `void Insert (int element);` 
<br>
Metoda Insert wstawia element do zbioru. Odpowiedni element tablicy jest ustawiany na `true`, aby zaznaczyć, że podany obiekt został wstawiony do zbioru. 
<br>
Dodatkowo zwiększany jest licznik `count`.
<br>
<br>
**Uwaga 1**: Jeśli element już należy do zbioru, nie wstawiamy go ponownie (nie zwiększamy licznika). 
<br>
<br>
Złożoność czasowa operacji wstawiania O(1).

3. `void Withdraw(int element);`
<br> 
Analogicznie do `Insert`. Jeśli element należy do zbioru,
to w odpowiedniej komórce tablicy wstawiamy watrtość `false` i zmniejszamy licznik `count`. 

4. `SetAsArray operator + (SetAsArray const& s, SetAsArray const& t)`
<br>
Operator sumy pobiera dwie referencje do instancji klasy `SetAsArray: s` oraz `t`.
<br>
Wynik jest typu `SetAsArray`. 
<br>
Implementacja wymaga, aby obydwa zbiory `s` oraz `t` miały taki sam rozmiar zbioru uniwersalnego. Wynik również będzie zbiorem o tym samym rozmiarze zbioru uniwersalnego. 
<br>
Operator ten tworzy nową tablicę wynikową i oblicza wymagane wartości tablicy. i-ty element tablicy będzie przyjmował wartość `true`, gdy i-ty element `s` przyjmuje wartość `true` lub i-ty element `t` przyjmuje wartość `true`.
<br>
<br>
Złożoność czasowa – O(N)

5. `SetAsArray operator * (SetAsArray const& s, SetAsArray const& t)`
<br>
Analogicznie do „`+`”, definiuje iloczyn mnogościowy (przecięcie) zbiorów.

6. `SetAsArray operator - (SetAsArray const& s, SetAsArray const& t)`
<br>
Analogicznie do „+”, definiuje różnicę mnogościową zbiorów.

7. `Operator ==` 
<br>
Równość zbiorów. Zwraca prawdę, gdy zbiory są równe.

8. `Operator <=`
<br>
Zawieranie zbiorów, zwraca prawdę, gdy pierwszy zbiór zawiera się w drugim. 

----------
<br>

## **Polecenie v2**
Stworzyć klasę `AddingVisitor` – wizytatora, który oblicza sumę elementów zbioru.
* Tworzymy klasę `AddingVisitor` dziedziczącą z klasy `Visitor`. W klasie mamy pole(np. `sum`) w którym pamiętamy policzona sumę. Metoda `AddingVisitor.visit(i)` zwieksza wartość tego pola `sum` o `i`. 
* Implementujemy metodę `Accept` dla klasy `SetAsArray` (przegląda wszystkie elementy zbioru wywołując `v.visit()`.(„skacze” po komórkach tablicy w których jest wartość `true`) 

