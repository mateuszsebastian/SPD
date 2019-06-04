#include "Zadanie.h"
#include <iostream>
#include <vector>


int Zadanie::minimum(vector<Zadanie> tab, int rozm)
{
    int adres = 0;
    int pom = tab[0].r;

    for (int i = 0; i < rozm; i++)
    {
        if(pom > tab[i].r){
            adres = i;
            pom = tab[i].r;
    }
    }
        return adres;

}

int Zadanie::maksimum(vector<Zadanie> tab, int rozm)
{
    int pom = tab[0].q;
    int adres = 0;

    for(int i = 0; i < rozm; i++)
    {
        if(pom < tab[i].q)
            {
                adres = i;
                pom = tab[i].q;
            }
    }
    return adres;
}

vector<Zadanie> Zadanie::Sharge(vector<Zadanie> tab, int rozm)
{
   // int i = 1;
    int t = tab[0].r;
    int adres;

    vector<Zadanie> pom;
    vector<Zadanie> sigma;

    Zadanie j;

    while(!tab.empty() || !pom.empty())
    {
        while(!tab.empty() && tab[0].r <= t)
        {
            adres = j.minimum(tab,tab.size());
            j.czytaj(tab[adres].r , tab[adres].p , tab[adres].q, tab[adres].nr_zad);
           // j.nr_zad = tab[adres].nr_zad;
            pom.push_back(j);
            tab.erase(tab.begin() + adres);
        }

        if(pom.empty() == true)
            t = tab[0].r;
        else
        {
            adres = j.maksimum(pom,pom.size());
            j.czytaj(pom[adres].r , pom[adres].p , pom[adres].q, pom[adres].nr_zad);
           // j.nr_zad = pom[adres].nr_zad;
            pom.erase(pom.begin() + adres);
            sigma.push_back(j);
           // i++;
            t = t + j.p;
        }
    }



   // for(unsigned int j = 0; j < sigma.size(); j++)
       // cout << sigma[j].r << " " << sigma[j].p << " " << sigma[j].q << endl;

    return sigma;
}

int Zadanie::Schrage_pmtm(vector<Zadanie> tab, int rozm)
{
    int Cmax = 0;
    int t = 0;
    //int l = 0;
    int adres;

    vector<Zadanie> pom;

    Zadanie j,l;
    l.czytaj(0,0,0,0);

    while (!pom.empty() || !tab.empty())
    {
        while(!tab.empty() && tab[0].r <= t)
        {
            adres = j.minimum(tab,tab.size());
            j.czytaj(tab[adres].r, tab[adres].p, tab[adres].q, tab[adres].nr_zad);
            pom.push_back(j);
            tab.erase(tab.begin() + adres);
            if(j.q > l.q)
            {
                l.p = t - j.r;
                t = j.r;
                if(l.p > 0)
                    pom.push_back(l);
            }
        }
        if(pom.empty())
            t = tab[0].r;
        else
            {
                adres = j.maksimum(pom,pom.size());
                j.czytaj(pom[adres].r, pom[adres].p, pom[adres].q, pom[adres].nr_zad);
                pom.erase(pom.begin() + adres);
                l = j;
                t = t + j.p;
                Cmax = max(Cmax, t + j.q);
            }
    }
    return Cmax;
}
int Zadanie::cmax(vector<Zadanie> tab, int rozm)
{
    int j = 0;
    vector<int> S;
    vector<int> Cmax;

    for(; j < rozm; j++)
    {
        if (j == 0)
            S.push_back(tab[j].r);
        else
            S.push_back(max(tab[j].r, S[j - 1] + tab[j - 1].p));
        Cmax.push_back(S[j] + tab[j].p);
    }

    int MaxWart = 0;

    for (unsigned int i = 0; i < Cmax.size(); i++)
    {
        if(Cmax[i] + tab[i].q > MaxWart)
            MaxWart = Cmax[i] + tab[i].q;
    }


    return MaxWart;
}
