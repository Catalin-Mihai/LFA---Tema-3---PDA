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
    struct simbol_intrare //citit de la tastatura
    {
        string litera;
        int index;
    };

    struct simbol_iesire //citit de la tastatura
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
        simbol_intrare simbol_intrare;
        caracter caracter_citit;
        vector<int> caractere_scrise;
        vector<simbol_iesire> simboluri_iesire_scrise;
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
    vector<simbol_intrare> simboluri_intrare;
    vector<simbol_iesire> simboluri_iesire;
    vector<caracter> caractere;
    vector<stare> stari;
    vector<stare> stari_finale;
    vector<tranzitie> tranzitii;
    stack<int> stiva;
    vector<string> outputs;
    string caracter_nul;
    string simbol_nul;
    //int **matrice;
    vector< vector< vector<int> > > tabel;
    void AfiseazaMatrice();
    bool check(PDA &nfa, int stare_index, string word, unsigned int position, stack<int> stiva, vector<simbol_iesire> &sir_iesire);

public:
    PDA();
    virtual ~PDA();
    bool CheckWord(string word);
    friend istream &operator>>(istream &input, PDA &pda);
    void CitesteTranzitii();
    void Afiseaza();
    stack<int> getStiva();
    int getLambdaSimbolIntrareIndex();
    int getZ0CaracterIndex();
    int getLambdaCaracterIndex();
    //int getTranzitieIndexByRule(int plecare, int destinatie, int simbol_intrare, int caracter_citit);
    vector<int> getValidTranzition(int plecare, int destinatie, int simbol_intrare, int caracter_citit);
    int getStareIndexByLitera(const string& l);
    int getCaracterIndexByLitera(const string& l);
    caracter getCaracterByLitera(const string& l);

    simbol_intrare getSimbolIntrareByLitera(const string& l);
    int getSimbolIntrareIndexByLitera(const string& l);

    simbol_iesire getSimbolIesireByLitera(const string& l);
    int getSimbolIesireIndexByLitera(const string& l);

    int getStareInitialaIndex() const;
    bool isStareFinalaIndex(int index);

    int getLambdaSimbolIesireIndex();

    static string convertSimboluriIesireToString(vector<simbol_iesire> simboluriIesire);

    vector<string> getOutputs();

    void clearOutputs();
};

#endif // PDA_H
