#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <random>


using namespace std;

int cmax(int **t, int zad, int masz);
void wypisz(int **t, int zad, int masz);
double schladzanie(double Temp);
double ruch(int C,int C_prim,double Temp);
double prawdopodobienstwo();

int main()
{


    ifstream plik;
    int zadanie, maszyna,C,C_s;
    int z_1,z_2;
    double T,p;
    string nazwa_pliku;
    string wybor = "1";

    cout << "Podaj nazwe pliku: \n";
    cin >> nazwa_pliku;

    plik.open(nazwa_pliku);
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

    C = cmax(tab,zadanie - 1,maszyna - 1);

    cout << "Poczatkowy czas przeplywu zupelnego = "<< C << endl;

    cout << "####################################\n#\n#\tPodaj poczatkowa temperature: ";
    cin >> T;
    cout << endl;


        do{

            z_1 = rand() % zadanie;
            z_2 = rand() % zadanie;

            swap(tab[z_1],tab[z_2]);

            C_s = cmax(tab,zadanie - 1, maszyna - 1);
            //Odkomenowac do testu na rozne Cmax
            //if (C_s == C)
             //   swap(tab[z_2],tab[z_1]);
           // else
            //{
            p = ruch(C,C_s,T);
           // aby odrzucic cmax dla p=1 nalezy zakomentowac if w funkcji ruch()
            if(p >= prawdopodobienstwo())
                C = C_s;
                else
                    swap(tab[z_2],tab[z_1]);

            T = schladzanie(T);
        //}
        }while(T > 5);

        wypisz(tab,zadanie,maszyna);
        cout << "\nKoncowy przeplywu zupelnego = "<< C << endl;
        cout << "\nTemperatura koncowa = " << T << endl;

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


     for(int i = 0; i < zad; i++)
    {
        for(int j = 0; j < masz; j++)
        {
            cout << setw(4) << t[i][j] << " ";
        }
            cout << endl;
    }
}

double ruch(int C,int C_prim,double Temp)
{
    double P;

    if (C_prim > C)
        P = exp((C - C_prim)/Temp);
        else
           P = 1;

    return P;
}

double schladzanie(double Temp)
{
    Temp = 0.9 * Temp;
    return Temp;
}

double prawdopodobienstwo()
{
    double P;

    double scale = RAND_MAX + 1.;
    double base = rand() / scale;
    double fine = rand() / scale;

    P = base + fine / scale;

    return P;
}

