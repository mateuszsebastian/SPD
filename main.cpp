#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>


using namespace std;

int cmax(int **t, int zad, int masz);
void permutacja(int **t, int zad, int masz);
void wypisz(int **t, int zad, int masz);

int main()
{
    ifstream plik;
    int zadanie, maszyna;

    plik.open("ta000.txt");
    if(plik.is_open())
        plik >> zadanie >> maszyna;
    cout <<"Ilosc zadan = " << zadanie << " " <<"Ilosc maszyn = " << maszyna << endl;
    cout << endl;

   // alokacja tablicy dwuwymiarowej

    int **tab = new int *[zadanie];
    for(int i = 0; i < zadanie; i++)
        tab[i] = new int [maszyna];

   // wpisanie wartosci z pliku

    for(int i = 0; i < zadanie; i++)
    {
        for(int j = 0; j < maszyna; j++)
            plik >> tab[i][j];
    }

    permutacja(tab, zadanie - 1, maszyna - 1);

    delete[] tab;

    return 0;
}


 int cmax(int **t, int zad, int masz)
{
    int czas_max;

    if (zad == -1 || masz == -1)
        return czas_max=0;
    else
        return czas_max = max(cmax(t, zad - 1, masz), cmax(t,zad,masz - 1 )) + t[zad][masz];

}


void wypisz(int **t, int zad, int masz)
{
    static int licz = 1;

     for(int i = 0; i < zad; i++)
    {
        for(int j = 0; j < masz; j++)
        {
            cout << setw(4) << t[i][j] << " ";
        }
            cout << endl;
    }


    int c = cmax(t,zad - 1,masz - 1);
    cout << "Czas przegladu zupelnego = " << c << endl;
    cout << licz << endl ;
    licz++;


}

void permutacja(int **t, int zad, int masz)
{
    int z = sizeof(zad);
    int m = sizeof(masz);

    if(zad == - 1)
        {
            wypisz(t,z,m - 1);
            cout << endl;

        }
        else
        {
            permutacja(t, zad - 1 , masz);
            for(int i = 0; i < zad; i++)
                {
                    if(i == masz)
                    swap(t[zad][masz], t[zad - 1][masz]);
                    else
                    {
                        for(int i = 0; i < m ; i++)
                        {
                            swap(t[zad][i], t[zad - 1][i]);
                        }
                    }
                        permutacja(t, zad - 1 , masz);
                }
            }
            return;
}
