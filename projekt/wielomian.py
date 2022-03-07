class Wielomian:
    """
    Klasa reprezentujaca wialomian
    """
    def __init__(self, wspolczynniki):
        """
        Inicjalizacja wielomianu o zadanych współczynnikach
        """
        stopien = self.__stopien(wspolczynniki)
        self.wspolczynniki = [None] * stopien

        for i in range(stopien):
            self.wspolczynniki[i] = float(wspolczynniki[i])


    def __add__(self, other):
        """
        Funkcja dodaje do siebie dwa wielomiany
        """
        wspolczynniki = None
        stopien1 = self.__stopien(self.wspolczynniki)
        stopien2 = self.__stopien(other.wspolczynniki)

        if stopien1 > stopien2:
            wspolczynniki = [None] * stopien1
            for i in range(stopien2):
                wspolczynniki[i] = self.wspolczynniki[i] + other.wspolczynniki[i]

            for i in range(stopien2, stopien1):
                wspolczynniki[i] = self.wspolczynniki[i]

        else:
            wspolczynniki = [None] * stopien2
            for i in range(stopien1):
                wspolczynniki[i] = self.wspolczynniki[i] + other.wspolczynniki[i]

            for i in range(stopien1, stopien2):
                wspolczynniki[i] = other.wspolczynniki[i]

        return Wielomian(wspolczynniki)

    def __sub__(self, other):
        """
        Funkcja odejmuje do siebie dwa wielomiany
        """
        wspolczynniki = None
        stopien1 = self.__stopien(self.wspolczynniki)
        stopien2 = self.__stopien(other.wspolczynniki)

        if stopien1 > stopien2:
            wspolczynniki = [None] * stopien1
            for i in range(stopien2):
                wspolczynniki[i] = self.wspolczynniki[i] - other.wspolczynniki[i]

            for i in range(stopien2, stopien1):
                wspolczynniki[i] = self.wspolczynniki[i]

        else:
            wspolczynniki = [None] * stopien2
            for i in range(stopien1):
                wspolczynniki[i] = self.wspolczynniki[i] - other.wspolczynniki[i]

            for i in range(stopien1, stopien2):
                wspolczynniki[i] = -other.wspolczynniki[i]

        return Wielomian(wspolczynniki)

    def __mul__(self, other):
        """
        Funkcja mnożąca ze sobą dwa wielomiany
        """
        stopien1 = self.__stopien(self.wspolczynniki)
        stopien2 = self.__stopien(other.wspolczynniki)
        wspolczynniki = [None] * (stopien1 + stopien2 - 1)

        for i in range(stopien1):
            for j in range(stopien2):
                if wspolczynniki[i+j] == None:
                    wspolczynniki[i+j] = self.wspolczynniki[i] * other.wspolczynniki[j]
                else:
                    wspolczynniki[i+j] += self.wspolczynniki[i] * other.wspolczynniki[j]
                    
        return Wielomian(wspolczynniki)

    def horner(self, x):
        """
        Funkcja obliczająca wartość wielomianu algorytmem Hornera dla danego argumentu
        """
        wynik = 0
        
        for i in range(self.__stopien(self.wspolczynniki)-1, -1, -1):
            wynik = wynik * x + self.wspolczynniki[i]

        return wynik

    def __stopien(self, wspolczynniki):
        """
        Pomocnicza funkcja zwracająca ilość współczynników
        """
        return len(wspolczynniki)

    def stopien(self):
        """
        Funkcja zwracająca stopień wielomianu
        """
        return self.__stopien(self.wspolczynniki) - 1

    def __str__(self):
        """
        Funkcja wypisująca wielomian
        """
        wielomian = ""
        stopien = self.__stopien(self.wspolczynniki)

        for i in range(stopien):
            wartosc = self.wspolczynniki[i]
            if wartosc:
                znak = None
                if wartosc < 0:
                    znak = '-'
                else:
                    znak = '+'

                czynnik = None

                if i == 0:
                    czynnik = str(abs(wartosc))
                elif i == 1:
                    if abs(wartosc) == 1.0:
                        czynnik = 'x'
                    else:
                        czynnik = str(abs(wartosc)) + 'x'
                else:
                    if abs(wartosc) == 1.0:
                        czynnik = 'x^' + str(i)
                    else:
                        czynnik = str(abs(wartosc)) + 'x^' + str(i)

                czynnik = czynnik.replace('.0', '')  
                wielomian += ' ' + znak + ' ' + czynnik
                
        znak = wielomian[1]
        wielomian = wielomian.removeprefix(' ' + znak + ' ')

        if znak == '-':
            wielomian = znak + wielomian

        return wielomian



"""
Przykłady użycia
"""

# w1 = Wielomian([2, 4, 0, 1])
# w2 = Wielomian([2, 4])
# w3 = w1 + w2
# print(w3)

# w3 = w2 - w1
# print(w3)

# w3 = w1 * w2
# print(w3)

# w5 = Wielomian([-9, 0, 0, 4, 5])
# print(w5.horner(1))
# print(w5.stopien())

w1 = Wielomian([0, -1, 7, -1])
print(w1.horner(-3))