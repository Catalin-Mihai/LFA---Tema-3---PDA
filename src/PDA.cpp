#include "PDA.h"

PDA::PDA()
= default;

PDA::~PDA()
= default;

int PDA::getStareIndexByLitera(const string& l)
{
    for(unsigned int i = 0; i < stari.size(); i++)
    {
        if(l == stari[i].litera) return stari[i].index;
    }
    return -1;
}

int PDA::getCaracterIndexByLitera(const string& l)
{
    for(unsigned int i = 0; i < caractere.size(); i++)
    {
        if(l == caractere[i].litera) return caractere[i].index;
    }
    return -1;
}

PDA::simbol_intrare PDA::getSimbolIntrareByLitera(const string& l)
{
    for(unsigned int j = 0; j < simboluri_intrare.size(); j++)
    {
        if(simboluri_intrare[j].litera == l)
        {
            return simboluri_intrare[j];
        }
    }
    simbol_intrare s;
    s.index = -1;
    s.litera = "NULL";
    return s;
}

int PDA::getSimbolIntrareIndexByLitera(const string& l)
{
    for(unsigned int j = 0; j < simboluri_intrare.size(); j++)
    {
        if(simboluri_intrare[j].litera == l)
        {
            return simboluri_intrare[j].index;
        }
    }
    return -1;
}

PDA::simbol_iesire PDA::getSimbolIesireByLitera(const string &l) {

    for(unsigned int j = 0; j < simboluri_iesire.size(); j++)
    {
        if(simboluri_iesire[j].litera == l)
        {
            return simboluri_iesire[j];
        }
    }
    simbol_iesire s;
    s.index = -1;
    s.litera = "NULL";
    return s;
}

int PDA::getSimbolIesireIndexByLitera(const string &l) {

    for(unsigned int j = 0; j < simboluri_iesire.size(); j++)
    {
        if(simboluri_iesire[j].litera == l)
        {
            return simboluri_iesire[j].index;
        }
    }
    return -1;
}

PDA::caracter PDA::getCaracterByLitera(const string& l)
{
    for(unsigned int j = 0; j < caractere.size(); j++)
    {
        if(caractere[j].litera == l)
        {
            return caractere[j];
        }
    }
    caracter s;
    s.index = -1;
    s.litera = "NULL";
    return s;
}



int PDA::getStareInitialaIndex() const
{
    return this->stare_initiala.index;
}

bool PDA::isStareFinalaIndex(int index)
{
    for(unsigned int i = 0; i < stari_finale.size(); i++)
    {
        if(stari_finale[i].index == index) return true;
    }
    return false;
}

int PDA::getLambdaSimbolIntrareIndex()
{
    return this->getSimbolIntrareIndexByLitera("L");
}

int PDA::getLambdaSimbolIesireIndex()
{
    return this->getSimbolIesireIndexByLitera("L");
}

int PDA::getLambdaCaracterIndex()
{
    return this->getCaracterIndexByLitera("L");
}

int PDA::getZ0CaracterIndex()
{
    return this->getCaracterIndexByLitera("$");
}

istream &operator>>(istream &input, PDA &fa)
{
    unsigned int nr;
    //stari
    input>>nr;
    PDA::stare s;
    for(unsigned int i = 0; i < nr; i++)
    {
        input>>s.litera;
        s.index = i;
        fa.stari.push_back(s);
    }

    //simboluri_intrare - alfabetul de intrare
    input>>nr;
    PDA::simbol_intrare s2;
    for(unsigned int i = 0; i < nr; i++)
    {
        input>>s2.litera;
        s2.index = i;
        fa.simboluri_intrare.push_back(s2);
    }

    //simboluri_iesire - alfabetul de iesire
    input>>nr;
    PDA::simbol_iesire s4;
    for(unsigned int i = 0; i < nr; i++)
    {
        input>>s4.litera;
        s4.index = i;
        fa.simboluri_iesire.push_back(s4);
    }

    //caractere - alfabetul stivei
    input>>nr;
    PDA::caracter c;
    for(unsigned int i = 0; i < nr; i++)
    {
        input>>c.litera;
        c.index = i;
        fa.caractere.push_back(c);
    }
    //OBS: Ultimul caracter citit = Z0;

    //stare initiala
    input>>fa.stare_initiala.litera;
    fa.stare_initiala.index = fa.getStareIndexByLitera(fa.stare_initiala.litera);

    //stari finale
    input>>nr;
    PDA::stare s3;
    for(unsigned int i = 0; i < nr; i++)
    {
        input>>s3.litera;
        s3.index = fa.getStareIndexByLitera(s3.litera);
        fa.stari_finale.push_back(s3);
    }

    //tranzitii
    input>>nr;
    string l;
    for(unsigned int i = 0; i < nr; i++)
    {
        PDA::tranzitie t;
        input>>l;
        t.plecare = fa.getStareIndexByLitera(l);
        input>>l;
        t.destinatie = fa.getStareIndexByLitera(l);
        input>>l;
        t.simbol_intrare = fa.getSimbolIntrareByLitera(l);
        input>>l;
        t.caracter_citit = fa.getCaracterByLitera(l);

        //Caracterele care vor fi scrise in stiva
        input>>l;
        for(unsigned int i = 0; i < l.length(); i++)
        {
            string aux;
            aux = l.at(i);
            //cout<<endl<<aux<<endl;
            int index = fa.getCaracterIndexByLitera(aux);
            cout<<endl<<aux<<" ind: "<<index<<endl;
            t.caractere_scrise.push_back(index);
        }

        //Caracterele care vor fi translatate
        input>>l;
        for(unsigned int i = 0; i < l.length(); i++)
        {
            string aux;
            aux = l.at(i);
            int index = fa.getSimbolIesireIndexByLitera(aux);
            cout<<endl<<aux<<" ind simbol iesire: "<<index<<endl;
            PDA::simbol_iesire iesire;
            iesire.index = index;
            iesire.litera = aux;
            t.simboluri_iesire_scrise.push_back(iesire);
        }

        cout<<endl;
        //t.caracter_scris = fa.getCaracterByLitera(l);
        fa.tranzitii.push_back(t);
    }
    fa.CitesteTranzitii();

    return input;
}

void PDA::CitesteTranzitii()
{
//Construire matrice
    //Initializare cu tranzitii
    tabel.resize(this->stari.size());
    for(unsigned int i = 0; i < this->stari.size(); i++)
    {
        tabel[i].resize(this->simboluri_intrare.size());
    }

    for(unsigned int i = 0; i < this->tranzitii.size(); i++)
    {
        tabel[tranzitii[i].plecare][tranzitii[i].simbol_intrare.index].push_back(tranzitii[i].destinatie);
    }

    vector< vector< vector<int> > >::iterator it_stari;
    vector< vector<int> >::iterator it_simb;
    for(it_stari = this->tabel.begin(); it_stari != this->tabel.end(); it_stari++)
    {
        for(it_simb = it_stari->begin(); it_simb != it_stari->end(); it_simb++)
        {
            if(it_simb->begin() == it_simb->end())
            {
                it_simb->push_back(-1);
            }
        }
    }
}

vector<int> PDA::getValidTranzition(int plecare, int destinatie, int simbol_intrare, int caracter_citit)
{
    vector<int> r;
    if(plecare >= 0 && destinatie >= 0)
    {
        for(unsigned int i = 0; i < tranzitii.size(); i++)
        {
            if(tranzitii[i].plecare == plecare && tranzitii[i].destinatie == destinatie && tranzitii[i].simbol_intrare.index == simbol_intrare)
            {
                if(tranzitii[i].caracter_citit.index == caracter_citit)
                {
                    r.push_back(i);
                }
            }
        }
    }
    return r;
}

bool PDA::check(PDA &lnfa, int stare_index, string word, unsigned int position, stack<int> stiva, vector<simbol_iesire> &sir_iesire)
{
    int simbolIntrareIndex;
    vector<int>::iterator it;

    //Tranzitii non-lambda
    if(position < word.length())
    {
        string s(1, word[position]);
        simbolIntrareIndex = lnfa.getSimbolIntrareIndexByLitera(s); //indexul simbolului de pe linie/sageata/tranzitie
        if(simbolIntrareIndex == -1) { cout << "Simbol invalid, return false" << endl; return false;}
        if(simbolIntrareIndex != lnfa.getLambdaCaracterIndex())
        {
            int caracter_index = stiva.top();
            for(it = lnfa.tabel[stare_index][simbolIntrareIndex].begin(); it != lnfa.tabel[stare_index][simbolIntrareIndex].end(); it++)
            {
                //Ia caracterul de pe stiva si vezi ce tranzitii exista cu caracterul citit
                vector<int> vt = getValidTranzition(stare_index, *it, simbolIntrareIndex, caracter_index);
                for(unsigned int y = 0; y < vt.size(); y++)
                {
                    int t = vt[y];

                    //Copie a stivei in acest moment.
                    //Nu folosim stiva originala deoarece continutul ei este modificat de alte tranzitii paralele.
                    stack<int> aux_stiva = stiva;
                    int position2 = position;
                    if(caracter_index != lnfa.getLambdaCaracterIndex())
                        aux_stiva.pop(); //sterge caracterul din top

                    //Push pe stiva
                    for(int c = lnfa.tranzitii[t].caractere_scrise.size()-1; c >= 0; c--)
                    {
                        //cout<<endl<<"c: "<<c;
                        if(lnfa.tranzitii[t].caractere_scrise[c] != lnfa.getLambdaCaracterIndex())
                        {
                            aux_stiva.push(lnfa.tranzitii[t].caractere_scrise[c]);
                        }
                    }

                    //Facem append simbolurilor de iesire
                    for(int c = lnfa.tranzitii[t].simboluri_iesire_scrise.size()-1; c >= 0; c--)
                    {
                        //cout<<endl<<"c: "<<c;
                        if(lnfa.tranzitii[t].simboluri_iesire_scrise[c].index != lnfa.getLambdaSimbolIesireIndex())
                        {
                            sir_iesire.push_back(lnfa.tranzitii[t].simboluri_iesire_scrise[c]);
                        }
                    }

                    if(check(lnfa, *it, word, position2 + 1, aux_stiva, sir_iesire))
                    {
                        return true;
                    }
                }
            }
        }
    }
    else if(lnfa.isStareFinalaIndex(stare_index))
    {
        outputs.push_back(convertSimboluriIesireToString(sir_iesire));
        return true;
    }


    // Tranzitii lambda
    // Aceiasi pasi ca mai sus.
    // Se executa doar tranzitiile lambda. Aici nu se mai verifica daca s-a ajuns la finalul cuvantului
    // si nu se mai avanseaza in cuvantul citit

    int lambda_simbIndex = lnfa.getLambdaSimbolIntrareIndex();
    if(lambda_simbIndex == -1) { return false;}
    int caracter_index = stiva.top();
    for(it = lnfa.tabel[stare_index][lambda_simbIndex].begin(); it != lnfa.tabel[stare_index][lambda_simbIndex].end(); it++)
    {
        vector<int> vt = getValidTranzition(stare_index, *it, lambda_simbIndex, caracter_index);
        for(unsigned int y = 0; y < vt.size(); y++)
        {
            stack<int> aux_stiva = stiva;
            int position2 = position;
            int t = vt[y];

            if(caracter_index != lnfa.getLambdaCaracterIndex())
                aux_stiva.pop(); //sterge caracterul din top

            for(int c = lnfa.tranzitii[t].caractere_scrise.size()-1; c >= 0; c--)
            {
                if(lnfa.tranzitii[t].caractere_scrise[c] != lnfa.getLambdaCaracterIndex())
                {
                    aux_stiva.push(lnfa.tranzitii[t].caractere_scrise[c]);
                }
            }

            //Facem append simbolurilor de iesire
            for(int c = lnfa.tranzitii[t].simboluri_iesire_scrise.size()-1; c >= 0; c--)
            {
                if(lnfa.tranzitii[t].simboluri_iesire_scrise[c].index != lnfa.getLambdaSimbolIesireIndex())
                {
                    sir_iesire.push_back(lnfa.tranzitii[t].simboluri_iesire_scrise[c]);
                }
            }

            if(check(lnfa, *it, word, position2, aux_stiva, sir_iesire))
            {
                return true;
            }
        }
    }
    return false;
}

bool PDA::CheckWord(string word)
{
    stack<int>s;
    stiva = s;

    //Stiva are intial caracterul Z0
    stiva.push(getZ0CaracterIndex());

    vector<simbol_iesire> sir_iesire;
    return check(*this, this->getStareInitialaIndex(), word, 0, stiva, sir_iesire);
}

void PDA::Afiseaza() {
    cout << "Nr_stari: " << this->stari.size() << endl;
    cout << "Stari: ";
    for (unsigned int i = 0; i < this->stari.size(); i++) {
        cout << "(i:" << this->stari[i].index << ",l:" << this->stari[i].litera << ") ";
    }
    cout << endl;
    cout << "Nr simboluri_intrare: " << this->simboluri_intrare.size() << endl;
    cout << "Simboluri: ";
    for (unsigned int i = 0; i < this->simboluri_intrare.size(); i++) {
        cout << "(i:" << this->simboluri_intrare[i].index << ",l:" << this->simboluri_intrare[i].litera << ") ";
    }
    cout << endl;
    cout << "Nr caractere: " << this->caractere.size() << endl;
    cout << "Caractere: ";
    for (unsigned int i = 0; i < this->caractere.size(); i++) {
        cout << "(i:" << this->caractere[i].index << ",l:" << this->caractere[i].litera << ") ";
    }
    cout << endl;
    cout << "Starea initiala: (i:" << this->stare_initiala.index << ",l:" << this->stare_initiala.litera << ") ";
    cout << endl;
    cout << "Nr stari finale: " << this->stari_finale.size() << endl;
    cout << "Starile finale: ";
    for (unsigned int i = 0; i < this->stari_finale.size(); i++) {
        cout << "(i:" << this->stari_finale[i].index << ",l:" << this->stari_finale[i].litera << ") ";
    }
    cout << endl;
    cout << "Nr tranzitii: " << this->tranzitii.size() << endl;
    for (unsigned int i = 0; i < this->tranzitii.size(); i++) {
        cout << "(plecare_index: " << this->tranzitii[i].plecare << ", destintatie_index: "
             << this->tranzitii[i].destinatie << " ,litera_simbol: " << this->tranzitii[i].simbol_intrare.litera
             << " ,simbol_index: " << this->tranzitii[i].simbol_intrare.index;
        cout << ", litera_caracter_scos: " << tranzitii[i].caracter_citit.litera << ", litera_caractere_scrise: ";
        for (unsigned c = 0; c < (this->tranzitii[i].caractere_scrise).size(); c++) {
            cout << tranzitii[i].caractere_scrise[c] << " ";
        }
        cout << ") " << endl;
    }
    cout << endl;
    this->AfiseazaMatrice();
}

void PDA::AfiseazaMatrice()
{
    vector< vector< vector<int> > >::iterator it_stari;
    vector< vector<int> >::iterator it_simb;
    vector<int>::iterator it_elem;
    for(it_stari = this->tabel.begin(); it_stari != this->tabel.end(); it_stari++)
    {
        for(it_simb = it_stari->begin(); it_simb != it_stari->end(); it_simb++)
        {
            for(it_elem = it_simb->begin(); it_elem != it_simb->end(); it_elem++)
            {
                cout<<*it_elem<<" ";
            }
            cout<<"; ";
        }
        cout<<endl;
    }
}

string PDA::convertSimboluriIesireToString(vector<simbol_iesire> simboluriIesire) {
    string s;
    for(auto c: simboluriIesire)
    {
        s.append(c.litera);
    }
    return s;
}

vector<string> PDA::getOutputs()
{
    return outputs;
}

void PDA::clearOutputs()
{
    outputs.clear();
}