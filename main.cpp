#include <iostream>
#include <fstream>
#include "PDA.h"

using namespace std;


int main()
{
    ifstream f("input3.txt");
    if(f.is_open())
        cout<<"Fisierul a fost gasit!\n";
    else cout<<"Fisierul nu a fost gasit!\n";

    PDA pda;
    f>>pda;
    int nr_cuv;
    f>>nr_cuv;
    pda.Afiseaza();
    string cuvant;
    cout<<"Introduceti sirul: "<<endl;
    while(cin>>cuvant)
    {
        pda.clearOutputs();
        pda.CheckWord(cuvant);
        auto outputs = pda.getOutputs();
        if(outputs.empty())
        {
            cout << "Nu exista output pentru inputul introdus!\n";
        }
        else
        {
            cout<<"Output-uri:"<<endl;
            for(const auto& output: pda.getOutputs())
            {
                cout<<output<<endl;
            }
        }

        cout<<"Introduceti sirul: "<<endl;
    }
    return 0;
}
