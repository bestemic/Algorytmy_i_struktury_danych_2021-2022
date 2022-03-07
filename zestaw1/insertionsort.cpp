#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int prostewstawianie(int tab[])
{
    int j, x;
    int licznik = 0;

    cout << "Nieposortowana tablica: ";
    for (int i = 1; i < 11; i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;

    for (int i = 2; i <= 10; i++)
    {
        x = tab[i];
        tab[0] = x;
        j = i - 1;

        while (x < tab[j])
        {
            licznik++;
            tab[j + 1] = tab[j];
            j = j - 1;
        }
        
        licznik++;

        tab[j + 1] = x;
    }

    cout << "Operacji dominujacych jest: " << licznik << endl;
    cout << "Posortowana tablica: ";
    for (int i = 1; i < 11; i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;

    return licznik;
}

int main()
{
    int posortowana[11] = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    prostewstawianie(posortowana);

    cout << "-----------------------------" << endl;

    int odwrotna[11] = {-1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    prostewstawianie(odwrotna);

    int rng[11];
    rng[0] = -1;
    srand(time(NULL));
    int srednia = 0;

    for (int i = 0; i < 10; i++)
    {
        cout << "-----------------------------" << endl;
        for (int j = 1; j < 11; j++)
        {
            rng[j] = ((rand() % 201) - 100);
        }

        srednia += prostewstawianie(rng);
    }

    cout << "\nSrednia ilosc operacji dominujacych dla 10 losowych tablic wynosi: " << double(srednia / 10) << endl;

    return 0;
}
