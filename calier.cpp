#include <iostream>
#include <cmath>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <climits>

using namespace std;
bool flaga = false;
vector<int> program;

void wczytaj (vector<vector<int>> &N)
{
    int n=0;
    fstream myfile;
    myfile.open("in50.txt", ios_base::in);
    myfile>>n;
    vector<int> RPG[n];

    int a,b,c;
    a=b=c=0;
    for (int i=0; i<n; ++i)
    {
        myfile>>a>>b>>c;
        RPG[i].push_back(a);
        RPG[i].push_back(b);
        RPG[i].push_back(c);
        N.push_back(RPG[i]);
    }
}


int max_rpg(const vector<vector<int>> &N, int n) // zwraca indeks najmniejszgo R P lub Q
{
    vector<int> R;

    for(int i=0; i<N.size(); ++i)
    {
        R.push_back(N[i][n]); // pierwsze to numer RPG drugie to R P lub Q

    }
    return distance(R.begin(), max_element(R.begin(), R.end()));

}

int min_rpg(const vector<vector<int>> &N, int n) // zwraca indeks najmniejszgo R P lub Q
{
    vector<int> R;
    for(int i=0; i<N.size(); ++i)
    {
        R.push_back(N[i][n]); // pierwsze to numer RPG drugie to R P lub Q

    }
    return distance(begin(R),(min_element(begin(R),end(R))));
}

int min_wartosc(const vector<vector<int>> &N, int n)
{
    return N[min_rpg(N,n)][n];

}

int max_wartosc(const vector<vector<int>> &N, int n)
{
    return N[max_rpg(N,n)][n];
}

int Schrage(vector<vector<int>>N) // Alg Schrage, zwraca Cmax
{
    vector<vector<int>> G;
    vector<int> RPG;
    vector<vector<int>>pi;
    int t=0,k=0,Cmax=0,e=0;
    while (!G.empty() || !N.empty())
    {
        while(!N.empty() && min_wartosc(N,0)<=t)
        {
            e=min_rpg(N,0);
            G.push_back(N[e]);
            N.erase(N.begin()+e);
        }

        if(G.empty())
        {
            t=min_wartosc(N,0);
            continue;
        }

        e=max_rpg(G,2);
        RPG=G[e];

        G.erase(G.begin()+e);

        ++k;
        t=t+RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
        pi.push_back(RPG);
    }
    return Cmax;
}

int Schrage_podzial(vector<vector<int>>N) // Alg Schrage, zwraca Cmax
{
    vector<vector<int>> G;
    vector<int> RPG,akt_zad;
    vector<vector<int>>pi;
    int t=0,k=0,Cmax=0,e=0,q0;
    akt_zad.push_back(0);
    akt_zad.push_back(0);
    akt_zad.push_back(q0);

    while (!G.empty() || !N.empty())
    {
        while(!N.empty() && min_wartosc(N,0)<=t)
        {
            e=min_rpg(N,0);
            RPG=N[e];
            G.push_back(N[e]);
            N.erase(N.begin()+e);

            if(RPG[2]>akt_zad[2])
            {
                akt_zad[1]=t-RPG[0];
                t=RPG[0];
                if(akt_zad[1]>0)
                    G.push_back(akt_zad);
            }
        }

        if(G.empty())
        {
            t=min_wartosc(N,0);
            continue;
        }

        RPG=G[max_rpg(G,2)];

        G.erase(G.begin()+max_rpg(G,2));

        akt_zad=RPG;
        t=t+RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
    }
    return Cmax;
}
vector<vector<int>> schrage_perm(vector<vector<int>>N) // Zwraca permutacje z alg Schrage
{
    vector<vector<int>>pi;
    vector<vector<int>> G;
    vector<int> RPG;
    int t=0,k=0,Cmax=0,e=0;
    while (!G.empty() || !N.empty())
    {
        while(!N.empty() && min_wartosc(N,0)<=t)
        {
            e=min_rpg(N,0);
            G.push_back(N[e]);
            N.erase(N.begin()+e);
        }

        if(G.empty())
        {
            t=min_wartosc(N,0);
            continue;
        }

        e=max_rpg(G,2);
        RPG=G[e];

        G.erase(G.begin()+e);

        ++k;
        t=t+RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
        pi.push_back(RPG);
    }
    return pi;
}

int Cmax_pi(vector<vector<int>>pi) // Funkcja zwraca wartosc Cmax dla danej permutacji
{
    vector<int> RPG;
    int t=pi[0][0];
    int Cmax=0;
    for(int i=0; i<pi.size(); i++)
    {
        RPG=pi[i];
        t=max(t,RPG[0]);
        t+=RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
    }

    return Cmax;

}

int algorytm_carlier(vector<vector<int>>N, int UB)
{
    /*n – liczba zada
    ri – termin dostępnoci zadania i
    pi – czas wykonania zadania i
    qi – czas dostarczenia zadania i
    UB – górne oszacowanie wartoci funkcji celu ( warto funkcji celu dla najlepszego dotychczas najlepszego rozwiązania)


    π - permutacja wykonania zadana maszynie,
    U – warto funkcji celu,
    LB – dolne oszacowanie wartoci funkcji c
    */



    vector<vector<int>> opt_pi,pi;
    vector<int> RPG;

    pi=schrage_perm(N); //wyznaczenie permutacji wykonywania zadañ algorytmem SHRAGE

    // **********PKT nr 2************
    //uaktualniane jest najlepsze do tej pory znalezione rozwiazanie
    int U=Schrage(N);
    if (U<UB)
    {
        UB=U;
        opt_pi=pi;
    }

    // **********PKT nr 3************
    //tu wyznaczany jest blok (a,b) oraz pozycja zadania interferencyjnego
    int a;
    int b=-1;
    int c=-1;
    int t=pi[0][0];

    // Wyznaczenie b
    for(int i=0; i<pi.size(); i++)
    {

        int Cmax_PI=Cmax_pi(pi); // przypisanie Cmax dla danego pi
        RPG=pi[i];
        t=max(t,RPG[0]);
        t+=RPG[1];
        if(t+RPG[2]==Cmax_PI)
        {
            if(i>b)     // wybieramy tylko najwieksze b, pierwszy zawsze spelniony bo wyzej b=-1
                b=i;
        }
        // wyznaczenie sumy do a
    }

    for(int i=0; i<pi.size(); i++)
    {
        int suma=0;
        int Cmax_PI=Cmax_pi(pi); // przypisanie Cmax dla danego pi
        RPG=pi[i];
        t=max(t,RPG[0]);
        t+=RPG[1];
        for(int s=i; s<=b; s++)
        {
            suma+=pi[s][1];

        }
        suma+=pi[b][2];
        if((RPG[0]+suma)==Cmax_PI)
        {
            if(i<a)
                a=i;  // wybieramy tylko najmniejsze a, pierwszy zawsze spelniony, bo wyzej a
        }
    }

    // wyznaczenie c
    for(int i=a; i<=b; i++)
    {
        if(pi[i][2]<pi[b][2])
        {
            if(i>c)
                c=i;
        }
    }

    if(c==-1)
    {
        flaga = true;
    }

    //****** PKT nr 4*******
    if(flaga==true)
    {
        program.push_back(UB);

        return UB;
    }

    // ******PKT nr 5*********
    /*wyznaczany jest najmniejszy z terminów dostępnosci oraz największy z termidostarczenia zadan stojacych na
    pozycjach od c+1 do b, dodatkowo wyznaczana jest suma czasów wykonania zadan*/
    int r_prim,g_prim,p_prim=0;
    for(int i=c+1; i<=b; i++)
    {
        if(pi[i][0]<r_prim)
            r_prim=pi[i][0];

        if(pi[i][2]<g_prim)
            g_prim=pi[i][2];

        p_prim+=pi[i][1];
    }

    // ********PKT 6-10***********
    int r_pom=pi[c][0];
    pi[c][0]=max(pi[c][0],r_prim+p_prim);   /*modyfikowany jest termin dostepno ci zadania referencyjnego
                                             (wymuszane jest aby zadanie referencyjne wykonywane było za wszystkimi zadaniami na tych pozycjach)*/
    int LB=Schrage_podzial(pi); //wyznaczane jest dolne ograniczenie dla wszystkich permutacji spełniajacych to wymaganie
    if(LB<UB)   //jeśli dolne oszacowanie wartosci celu jest mneijsze od gornego oszacowania funkcji celu
        algorytm_carlier(pi,UB);
    pi[c][0]=r_pom; //odtwarzany jest termin dostepnoci rozwiazania referencyjnego

    // *********PKT 11-15*************
    int q_pom=pi[c][2];
    pi[c][2]=max(pi[c][2],g_prim+p_prim);
    LB=Schrage_podzial(pi);
    if(LB<UB)
        algorytm_carlier(pi,UB);
    pi[c][2]=q_pom; /*modyfikowany jest termin dostarczenia zadania referencyjnego
                    (wymuszane jest aby zadanie referencyjne wykonywane było przed wszystkimi zadaniami na pozycjach od c+1 do b).*/
    return UB;
}

int main()
{
    vector<vector<int>>N;
    vector<int> rpg1;
    wczytaj(N);
    algorytm_carlier(N,INT_MAX);
    cout<<"Cmax to: "<<program.at(0)<<endl;

    return 0;
}
