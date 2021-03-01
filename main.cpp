#include <iostream>
#include <fstream>
#include "PDA.h"

using namespace std;


int main()
{
    ifstream f("test4.txt");
    if(f.is_open())
        cout<<"Fisierul a fost gasit!\n";
    else cout<<"Fisierul nu a fost gasit!\n";

    PDA pda;
    f>>pda;
    int nr_cuv;
    f>>nr_cuv;
    pda.Afiseaza();
    string cuvant;
    for(int i = 0; i < nr_cuv; i++)
    {
        f>>cuvant;
        vector<PDA::simbol_iesire> iesire = pda.CheckWord(cuvant);
        if(iesire.empty())
            cout<<"Inputul nu este corect!";
        else
        {
            cout<<"Outputul este: ";
            for(auto &c: iesire)
            {
                cout<<c.litera;
            }
            cout<<endl;
        }
    }
//    cout<<"LAMBDA: "<< pda.getLambdaSimbolIntrareIndex();
    return 0;
}
