#include "Zadanie.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
   string nazwa_pliku;
   ifstream plik;
   int zadania, a, b, c, Cmax, zad;

   vector <Zadanie> tab;
   vector <Zadanie> pi;
   Zadanie test,test2;

   cout << "Podaj nazwe pliku" << endl;
   cin >> nazwa_pliku;

    plik.open(nazwa_pliku);
    if(plik.is_open())
    plik >> zadania;
    cout <<"Ilosc zadan = " << zadania << endl;
    cout << endl;


    for (int i = 0; i < zadania; i++)
    {
            plik >> a >> b >> c;
            zad = i + 1;
            test.czytaj(a,b,c,zad);
           // test.nr_zad = i + 1;
            tab.push_back(test);

    }


   // for (int i = 0; i < zadania; i++)
   //     cout << tab[i].r << " " << tab[i].p << " " << tab[i].q << " " << tab[i].nr_zad << endl;


     /*  pi = test.Sharge(tab,tab.size());

       for (unsigned int i = 0; i < pi.size(); i++)
        cout << pi[i].nr_zad << " ";


       Cmax = test.cmax(pi, pi.size());
       cout << "\n" << Cmax << endl;

*/

        Cmax = test.Schrage_pmtm(tab,tab.size());
        cout << "#################################\n\tCMAX z przerwaniami\n\t" << Cmax << endl;


        /*Cmax = test.maksimum(tab,tab.size());
        cout << Cmax << endl;

        test2.czytaj(tab[Cmax].r, tab[Cmax].p, tab[Cmax].q, tab[Cmax].nr_zad);

        cout << test2.r << " " << test2.p << " " << test2.q << endl;



        tab.erase(tab.begin() + Cmax);

         for (int i = 0; i < tab.size(); i++)
             cout << tab[i].r << " " << tab[i].p << " " << tab[i].q << " " << tab[i].nr_zad << endl;

*/








return 0;
}
