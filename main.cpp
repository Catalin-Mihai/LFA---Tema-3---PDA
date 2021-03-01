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
        bool t = pda.CheckWord(cuvant);
        if(!t) cout << "Nu este bun cuvantul: " << cuvant << endl;
        else cout<<"Este bun cuvantul: "<<cuvant<<endl;
        cout<<pda.getStiva().size()<<endl;
    }
    cout<<"LAMBDA: "<<pda.getLambdaSimbIndex();
    return 0;
}
