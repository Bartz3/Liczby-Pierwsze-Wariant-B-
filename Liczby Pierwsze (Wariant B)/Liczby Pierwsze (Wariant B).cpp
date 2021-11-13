#include <iostream>
#include <fstream>

#define size 1000000

using namespace std;

int wyszukiwanieBinarne(int tab[], int l, int p, int x) {
    if (p >= l) {
        int sr = l + (p - l) / 2;

        if (tab[sr] == x)
            return tab[sr];

        if (tab[sr] > x)
            return wyszukiwanieBinarne(tab, l, sr - 1, x);

        if (tab[sr] < x)
            return wyszukiwanieBinarne(tab, sr + 1, p, x);
    }


    return -1; // Jeœli brak elementu x funckja zwraca -1
}
bool czyPierwszaI(int x)     // Funkcja iteracyjna
{
    bool t = true;
    for (int d = 2; d * d <= x; d++)
        if (x % d == 0)
        {
            t = false;
            break;
        }
    return t;
}

bool czyPierwszaR(int n, int i = 2) //Funkcja rekurencyjna: sprawdzenie liczb od 2 do sqrt(n), je¿eli 2 if jest prawdziwy, liczba nie jest pierwsza
{
    if (n <= 2)
        return (n == 2) ? true : false;   
    if (n % i == 0)
        return false;
    if (i * i > n)
        return true;

    return czyPierwszaR(n, i + 1);
}

int main()
{
    fstream plik;
    int ile = 0, ileOperacjiLP = 0, ileOperacjiDiZ = 0;
    int a, b;
    plik.open("PL_in_8_Pozniewski.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "B³¹d otwarcia pliku do odczytu." << endl;
        return 1;
    }
    plik >> a >> b;
    plik.close();

    plik.open("PL_out_8_Pozniewski.txt", ios::out);
    if (plik.good() == false)
    {
        cout << "B³¹d otwarcia pliku do zapisu." << endl;
        return 1;
    }

    int* zakres = new int[size];
    for (int i = 0; i < size-1; i++) //  zakres[0]=2 - zakres[999998] = 10^6
    {
        zakres[i] = i + 2;
    }
    int A, B;

    A=wyszukiwanieBinarne(zakres,0,size-1,a);

    (A == -1) ? cout << "Liczba " << A << " jest spoza zakresu" << endl
        : cout << "Liczba " << A << " miesci sie w zakresie" << endl;


    B=wyszukiwanieBinarne(zakres,0,size-1,b);

    (B == -1) ? cout << "Liczba " << B << " jest spoza zakresu" << endl
        : cout << "Liczba " << B << " miesci sie w zakresie" << endl;

    cout << "Zakres liczb " << "(" << A << ":" << B << ")" << endl;
   
   for (A; A <= B; A++)
   {
       if (czyPierwszaI(A)) {  
           ile++;
       }
   }

   cout << "Ilosc liczb pierwszych: " << ile << endl;
   plik << "Ilosc liczb pierwszych: " << ile;

   delete zakres;
   plik.close();

}
