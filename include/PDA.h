#ifndef PDA_H
#define PDA_H

#include <string>
#include <istream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class PDA
{
public:
    struct simbol //citit de la tastatura
    {
        string litera;
        int index;
    };

    struct caracter //citit din stiva
    {
        string litera;
        int index;
    };

    struct tranzitie
    {
        simbol simb;
        caracter caracter_citit;
        vector<int> caractere_scrise;
        int plecare;
        int destinatie;
    };

    struct stare
    {
        string litera;
        int index;
    };

private:
    stare stare_initiala;
    vector<simbol> simboluri;
    vector<caracter> caractere;
    vector<stare> stari;
    vector<stare> stari_finale;
    vector<tranzitie> tranzitii;
    stack<int> stiva;
    string caracter_nul;
    string simbol_nul;
    //int **matrice;
    vector< vector< vector<int> > > tabel;
    void AfiseazaMatrice();
    bool check(PDA &nfa, int stare_index, string word, unsigned int position, stack<int> stiva);

public:
    PDA();
    virtual ~PDA();
    bool CheckWord(string word);
    friend istream &operator>>(istream &input, PDA &pda);
    void CitesteTranzitii();
    void Afiseaza();
    int getLambdaSimbIndex();
    int getStivaCaracter();
    int getZ0CaracterIndex();
    int getLambdaCaracterIndex();
    //int getTranzitieIndexByRule(int plecare, int destinatie, int simbol, int caracter_citit);
    vector<int> getValidTranzition(int plecare, int destinatie, int simbol, int caracter_citit);
    int getStareIndexByLitera(string l);
    int getCaracterIndexByLitera(string l);
    caracter getCaracterByLitera(string l);
    simbol getSimbolByLitera(string l);
    int getSimbolIndexByLitera(string l);
    int getStareInitialaIndex();
    bool isStareFinalaIndex(int index);
};

#endif // PDA_H
