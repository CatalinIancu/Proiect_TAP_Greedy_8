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

bool Cmp(Solicitare i, Solicitare j)
{
    return (i.ziuaCazarii + i.durataCazarii < j.ziuaCazarii + j.durataCazarii);
}

void CitireFisier(int &numarCamere, int &numarSolicitari, vector <Solicitare> &solicitariCazare)
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

void SortareSolicitari(vector <Solicitare> &solicitariCazare)
{
    sort(solicitariCazare.begin(), solicitariCazare.end(), Cmp);
}

void AfisareVector(vector <Solicitare> solicitariCazare)
{
    cout << "Test: " << endl;
    for (int i = 0; i < solicitariCazare.size(); i++)
    {
        cout << "Solicitare " << i << ": " << endl;
        cout << solicitariCazare[i].ziuaCazarii << " " << solicitariCazare[i].durataCazarii << endl;
    }
}

void InitializareCamere(int &minimEliberare, int &numarCamere, int &counterSolicitariOnorate,
                        vector <Solicitare> &camereOcupate,
                        vector <Solicitare> &solicitariCazare)
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

void ParcurgereAn(int &minimEliberare, int &numarCamere, int &counterSolicitariOnorate,
                  vector <Solicitare> &camereOcupate,
                  vector <Solicitare> &solicitariCazare)
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
    int numarCamere, numarSolicitari, minimEliberare;
    int counterSolicitariOnorate = 0;
    vector <Solicitare> solicitariCazare;
    vector <Solicitare> camereOcupate;
    camereOcupate.resize(numarCamere);
    CitireFisier(numarCamere, numarSolicitari, solicitariCazare);
    SortareSolicitari(solicitariCazare);
    AfisareVector(solicitariCazare);
    InitializareCamere(minimEliberare, numarCamere, counterSolicitariOnorate, camereOcupate, solicitariCazare);
    ParcurgereAn(minimEliberare, numarCamere, counterSolicitariOnorate, camereOcupate, solicitariCazare);
    cout << "numarSolicitariOnorate: " << counterSolicitariOnorate << endl;
    return 0;
}