#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

void wypisz(int **t, int zad, int masz);
int **czas_zad(int **t, int zad, int masz);
int **sortuj(int **t_s, int zad);
int cmax(int **t, int zad, int masz);
int **neh(int **t,int **t_s, int zad, int masz);

int main()
{
    char wybor = '1';
    int **s;


    while(wybor != '0')
    {
        ifstream plik;
        int zadanie, maszyna;
        string nazwa_pliku;

      //  cout << "Podaj nazwe pliku do wczytania: " << endl;
      //  cin >> nazwa_pliku;

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

            wypisz(tab,zadanie,maszyna);
            s = czas_zad(tab,zadanie,maszyna);

            cout << endl;

            sortuj(s,zadanie);
            neh(tab,s,zadanie,maszyna);

            delete[] tab;

            cout << endl;
            cout << "Jesli chcesz zakonczyc program wcisnij 0" << endl;
            cin >> wybor;
            cout << endl;



        }

    return 0;

}

void wypisz(int **t, int zad, int masz)
{
     for(int i = 0; i < zad; i++)
    {
        for(int j = 0; j < masz; j++)
        {
            cout << setw(4) << t[i][j] << " ";
        }
            cout << endl;
    }
}

int **czas_zad(int **t, int zad, int masz)
{
    int suma_tmp;
    int *suma = new int[zad];
    int **suma2 = new int *[2];
            for(int i = 0; i < 2; i++)
                suma2[i] = new int [zad];

    for(int i = 0; i < zad; i++)
        {
            suma_tmp = 0;

            for(int j = 0; j < masz; j++)
            suma_tmp += t[i][j];
            suma[i] = suma_tmp;



            for(int i = 0; i < 2; i++)
            {
                if (i == 0)
                {
                    for(int j = 0; j < zad; j++)
                        suma2[i][j] = suma[j];
                }
                else
                    {
                        for(int k = 0; k < zad; k++)
                            suma2[i][k] = k + 1;
                    }
            }
        }

    return suma2;

}

int **sortuj(int **t_s, int zad)
{
    int tmp = zad;

    do
    {
        for(int i = 0; i < zad - 1; i++)
            {
                if(t_s[0][i] < t_s[0][i + 1])
                {
                    swap(t_s[0][i], t_s[0][i + 1]);
                     swap(t_s[1][i], t_s[1][i + 1]);

                }
            }

            tmp --;
    }
    while(tmp > 1);

    cout << "Czas zadan posortowany nierosnaco" << endl;

    for(int j = 0; j < zad; j++)
        cout << t_s[0][j] << " ";
    cout << endl <<endl;

    cout << "Kolejnosc wykonywania posortowanych zadan" << endl;

    for(int j = 0; j < zad; j++)
        cout << t_s[1][j] << " ";
    cout << endl << endl;
return t_s;

}

int cmax(int **t, int zad, int masz)
{
    int czas_max;

    if (zad == -1 || masz == -1)
        return czas_max=0;
    else
        return czas_max = max(cmax(t, zad - 1, masz), cmax(t,zad,masz - 1 )) + t[zad][masz];

}



int **neh(int **t,int **t_s, int zad, int masz)
{
    int kolejne_zad;
    int C, C1, C_tmp = 0;
    int **tab_tmp = new int *[zad];
    for(int i = 0; i < zad; i++)
        tab_tmp[i] = new int [masz];

    if(zad == 1)
        {
            cout << "Jest tylko jedno zadanie do wykonanaia." << endl
                << "Czas preplywu zupelnego tego zadania to: " <<  t_s[0][0] << endl;
        }

        else
            {
                //petla, ktora dodaje kolejne zadania

                for(int i = 0; i < zad; i++)
                {
                    kolejne_zad = t_s[1][i] - 1;


                    // kopiowanie odpowiednich tablicy glownej do tablicy tymczasowej

                        for(int k = 0; k < masz; k++)
                            tab_tmp[i][k] = t[kolejne_zad][k];

                        if(i > 0)
                            {
                                C1 = cmax(tab_tmp,i,masz - 1);

                                    for(int z = 1; z <= i; z++)
                                    {
                                        swap(tab_tmp[i],tab_tmp[i - z]);
                                        C = cmax(tab_tmp,i,masz - 1);
                                        if(C1 > C)
                                            {
                                                C1 = C;
                                                swap(tab_tmp[i - z],tab_tmp[i]);
                                            }

                                    }
                                    C = cmax(tab_tmp,i,masz - 1);
                                    C_tmp = cmax(tab_tmp,i, masz - 1);
                                    if(C > C_tmp)
                                        C = C_tmp;
                                    else
                                       {
                                           for(int z = 0; z < i + 1; z++)
                                            swap(tab_tmp[i - z],tab_tmp[i]);
                                       }
                            }
                            else
                                {
                                    C = cmax(tab_tmp,i,masz - 1);
                                }
                }
                if(C1 > C)
                    cout << "Czas wykonania zadan wg algorytmu NEH to: " << C << endl;
                else
                    cout << "Czas wykonania zadan wg algorytmu NEH to: " << C1 << endl;
                }

    delete[] tab_tmp;

      return t_s;
}





