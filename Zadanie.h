#include <iostream>
#include <vector>

using namespace std;

class Zadanie {

public:

    int r, p, q, nr_zad;

    void czytaj(int a, int b, int c, int zad) {r = a; p = b; q = c; nr_zad = zad; };

    vector<Zadanie> Sharge(vector<Zadanie> tab, int rozm);

    int minimum(vector<Zadanie> tab, int rozm);

    int maksimum(vector<Zadanie> tab, int rozm);

    int cmax(vector<Zadanie> tab, int rozm);

    int Schrage_pmtm(vector<Zadanie> tab, int rozm);

   /* std::ostream &operator << (const Zadanie &z1)
    {
        return cout << z1.r << ' ' << z1.p << ' ' << z1.q;
    }*/

};
