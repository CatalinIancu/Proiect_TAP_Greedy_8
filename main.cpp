#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Solicitare
{
    int ziuaCazarii;
    int durataCazarii;
};

/*
 -> numarCamere reprezinta numarul camerelor libere (sau care vor fi libere in ziua in care o perioada de cazare se sfarseste)
 -> numarSolicitari reprezinta numarul total de solicitari
 -> minimEliberare reprezinta cea mai apropiata zi in care se va sfarsi o cazare
 -> counterSolicitariOnorate imi numara solicitarile onorate
 -> solicitariCazare este un vector care contine toate solicitarile de cazare
 -> camereOcupate este un vector care contine solicitarile in curs de onorare (cele care ocupa camerele)
*/
int numarCamere, numarSolicitari, minimEliberare;
int counterSolicitariOnorate = 0;
vector <Solicitare> solicitariCazare;
vector <Solicitare> camereOcupate;

bool Cmp(Solicitare i, Solicitare j) //Functia standard, cmp pentru std::sort()
{
    return (i.ziuaCazarii + i.durataCazarii < j.ziuaCazarii + j.durataCazarii);
}

/*
 -> Aici are loc citirea din fisier.
 -> Pe primul rand avem numarul de camere pe care le detine hotelul si numarul total de solicitari (despartite prin spatiu)
 -> Urmatoarele randuri contin solicitarile de cazare in format: data cazare , durata cazare (despartite prin spatiu)
*/
void CitireFisier()
{
    ifstream fin("Input.in");
    fin >> numarCamere;
    fin >> numarSolicitari;
    for (int i = 0; i < numarSolicitari; i++)
    {
        Solicitare *SolicitareNoua = new Solicitare;
        fin >> SolicitareNoua->ziuaCazarii;
        fin >> SolicitareNoua->durataCazarii;
        solicitariCazare.push_back(*SolicitareNoua);
    }
}

// Functia std::sort(), adaptata pentru vectorii din program
void SortareSolicitari(vector <Solicitare> vectorDeSortat)
{
    sort(vectorDeSortat.begin(), vectorDeSortat.end(), Cmp);
}

// Functia afiseaza toate elementele din vectorul dat ca parametru
void AfisareVector(vector <Solicitare> vectorDeAfisat)
{
    for (int i = 0; i < vectorDeAfisat.size(); i++)
    {
        cout << vectorDeAfisat[i].ziuaCazarii << " " << vectorDeAfisat[i].durataCazarii << endl;
    }
}
/*
 -> Functia va itera de la 0 pana la numarul camerelor libere (din inainte de intrare in functie)
 -> Functia se va asigura ca voi ocupa toate camerele sau ca voi onora toate cererile in cazul in care nr camere > nr solicitari
 -> Functia va decrementa cu 1 variabila numarCamere de fiecare data cand o solicitare este alocata la o camera
 -> Functia va scrie in minimEliberare cea mai apropiata zi in care se va termina o cazare
 -> Functia va incrementa cu 1 variabila numarCamere de fiecare data cand va gasi o solicitare care se va sfarsi in aceeasi data cu minimEliberare
*/
void InitializareCamere()
{
    int stop = numarCamere;
    minimEliberare = solicitariCazare[0].ziuaCazarii + solicitariCazare[0].durataCazarii;
    for (int i = 0; i < stop; i++)
    {
        if (solicitariCazare.size()>0)
        {
            if ((solicitariCazare[0].ziuaCazarii + solicitariCazare[0].durataCazarii) == minimEliberare)
            {
                numarCamere++;
            }
            camereOcupate.push_back(solicitariCazare[0]);
            solicitariCazare.erase(solicitariCazare.begin());
            numarCamere--;
            counterSolicitariOnorate++;
        }
    }
}

/*
 -> Functia va parcurge anul de 365 de zile, zi cu zi
 -> Cand va gasi o zi care este egala cu minimEliberare, functia fa sterge din solicitariCazare solicitarile care au fost onorate
 -> Functia va inlocui in camereOcupate solicitarile onorate cu solicitari noi luate din vectorul sortat solicitariCazare
 -> Functia se va asigura ca mai are solicitari care pot fi onorate
 -> Functia va scrie in minimEliberare cea mai apropiata zi in care se va termina o cazare
 -> Functia va incrementa cu 1 variabila numarCamere de fiecare data cand va gasi o solicitare care se va sfarsi in aceeasi data cu minimEliberare
*/
void ParcurgereAn()
{
    for (int i = 1; i <= 365; i++)
    {
        if (i == minimEliberare)
        {
            int stop = numarCamere;
            for (int j = 0; j < stop; j++)
            {
                while (solicitariCazare[0].ziuaCazarii < i && solicitariCazare.size() > 0)
                {
                    solicitariCazare.erase(solicitariCazare.begin());
                }
                camereOcupate[j] = solicitariCazare[0];
                if (solicitariCazare.size() > 0)
                {
                    solicitariCazare.erase(solicitariCazare.begin());
                    numarCamere--;
                    counterSolicitariOnorate++;
                } else
                {
                    break;
                }
            }
            SortareSolicitari(camereOcupate);
            minimEliberare = camereOcupate[0].ziuaCazarii + camereOcupate[0].durataCazarii;
            int aux = 0;
            while (camereOcupate[aux].ziuaCazarii + camereOcupate[aux].durataCazarii == minimEliberare)
            {
                aux++;
                numarCamere++;
            }
        }
    }
}

int main()
{
    CitireFisier();
    SortareSolicitari(solicitariCazare);

    cout << "Toate solicitarile ordonate: ";
    cout << endl;
    AfisareVector(solicitariCazare);

    InitializareCamere();
    ParcurgereAn();

    cout << endl;
    cout << "Solicitari onorate: ";
    cout << counterSolicitariOnorate;
    cout << endl;
    return 0;
}