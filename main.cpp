#include <iostream>
#include <fstream>
#include "PDA.h"

using namespace std;

ifstream f("test2.txt");

int main()
{
            PDA lnfa;
            f>>lnfa;
            int nr_cuv;
            f>>nr_cuv;
            lnfa.Afiseaza();
            string cuvant;
            for(int i = 0; i < nr_cuv; i++)
            {
                f>>cuvant;
                bool t = lnfa.CheckWord(cuvant);
                if(t == false) cout<<"Nu este bun cuvantul: "<<cuvant<<endl;
                else cout<<"Este bun cuvantul: "<<cuvant<<endl;
            }
            cout<<"LAMBDA: "<<lnfa.getLambdaSimbIndex();
            return 0;
}
