#include <iostream>
#include <fstream>

#define size 1000000

using namespace std;

int ileOperacjiLP = 0, 
    ileOperacjiDiZ = 0;

int wyszukiwanieBinarne(int tab[], int l, int p, int x) {
    if (p >= l) {
        //ileOperacjiDiZ += 3;
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
int sieve(int n) { // Sito Eratostenesa
    int k, l;
    int* S = new int[n];
    S[1] = 0; // 1 nie jest liczbą pierwszą
        for (k = 2; k <= n; k++)
            S[k] = 1;

    for (k = 2; k * k <= n; k++) {
        // Jeżeli k jest liczba pierwszą (nie przekreśloną)
            if (S[k] == 1) {
                // Wykreślami wszyskie wielokrotności k
                    for (l = k * k; l <= n; l += k) {
                        S[l] = 0;
                    }
            }
    }
    int ile = 0;
    for (int i = 0; i <= n; i++)
    {
        if (S[i] == 1)ile++;
    }
    cout << "ILE SIEVE: " << ile << endl;

    return ile;
}

bool czyPierwszaI(int x)     // Funkcja iteracyjna
{
    bool t = true;
    for (int d = 2; d * d <= x; d++) {
        //ileOperacjiLP++;
        if (x % d == 0)
        {
            t = false;
            break;
        }
    }
    return t;
}


int main()
{
   fstream plik;
   int ileI = 0,ileR=0;
   int a, b;       // a-początek zakresu, b-koniec zakresu
   plik.open("PL_in_8_Pozniewski.txt", ios::in);
   if (plik.good() == false)
   {
       cout << "Blad otwarcia pliku do odczytu." << endl;
       return 1;
   }
   plik >> a >> b;
   plik.close();
   
   plik.open("PL_out_8_Pozniewski.txt", ios::out);
   if (plik.good() == false)
   {
       cout << "Blad otwarcia pliku do zapisu." << endl;
       return 1;
   }
   
   int* zakres = new int[size];
   for (int i = 0; i < size - 1; i++) //  zakres[0]=2 - zakres[999998] = 10^6
   {
       zakres[i] = i + 2;
   }
   int A, B;
   
   A = wyszukiwanieBinarne(zakres, 0, size - 1, a);
   
   (A == -1) ? cout << "Liczba " << A << " jest spoza zakresu" << endl
       : cout << "Liczba " << A << " miesci sie w zakresie" << endl;
   
   B = wyszukiwanieBinarne(zakres, 0, size - 1, b);
   
   (B == -1) ? cout << "Liczba " << B << " jest spoza zakresu" << endl
       : cout << "Liczba " << B << " miesci sie w zakresie" << endl;
   
   cout << "Zakres liczb " << "(" << A << ":" << B << ")" << endl;

   if (a <= 3)
       ileI = sieve(b) - sieve(a) + 1;
   else ileI = sieve(b) - sieve(a);
   cout << "Ile SIEVE MAIN: " << ileI << endl;

   for (A; A <= B; A++)
   {
       if (czyPierwszaR(A)) {
           ileR++;
       }
   }
   

   //cout << "Ilosc operacji wyszukiwania binarnego : " << ileOperacjiDiZ << endl;
   //cout << "Ilosc operacji funkcji do LP : " << ileOperacjiLP << endl;
   plik << "Ilosc liczb pierwszych: " << ileI <<endl;    // Iteracja
   //plik << "Ilosc liczb pierwszych: " << ileR <<endl;  // Rekurencja
   delete zakres;
   plik.close();
}