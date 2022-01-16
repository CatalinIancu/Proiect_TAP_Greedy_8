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

int numarCamere, numarSolicitari, minimEliberare;
int counterSolicitariOnorate = 0;
vector <Solicitare> solicitariCazare;
vector <Solicitare> camereOcupate;

bool Cmp(Solicitare i, Solicitare j)
{
    return (i.ziuaCazarii + i.durataCazarii < j.ziuaCazarii + j.durataCazarii);
}

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

void SortareSolicitari(vector <Solicitare> vectorDeSortat)
{
    sort(vectorDeSortat.begin(), vectorDeSortat.end(), Cmp);
}

void AfisareVector(vector <Solicitare> vectorDeAfisat)
{
    for (int i = 0; i < vectorDeAfisat.size(); i++)
    {
        cout << vectorDeAfisat[i].ziuaCazarii << " " << vectorDeAfisat[i].durataCazarii << endl;
    }
}

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