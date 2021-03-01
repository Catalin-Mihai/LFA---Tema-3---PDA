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

PDA::simbol PDA::getSimbolByLitera(const string& l)
{
    for(unsigned int j = 0; j < simboluri.size(); j++)
    {
        if(simboluri[j].litera == l)
        {
            return simboluri[j];
        }
    }
    simbol s;
    s.index = -1;
    s.litera = "NULL";
    return s;
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

int PDA::getSimbolIndexByLitera(const string& l)
{
    for(unsigned int j = 0; j < simboluri.size(); j++)
    {
        if(simboluri[j].litera == l)
        {
            return simboluri[j].index;
        }
    }
    return -1;
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

int PDA::getLambdaSimbIndex()
{
    return this->getSimbolIndexByLitera("L");
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

    //simboluri
    input>>nr;
    PDA::simbol s2;
    for(unsigned int i = 0; i < nr; i++)
    {
        input>>s2.litera;
        s2.index = i;
        fa.simboluri.push_back(s2);
    }

    //caractere
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
        t.simb = fa.getSimbolByLitera(l);
        input>>l;
        t.caracter_citit = fa.getCaracterByLitera(l);
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
        tabel[i].resize(this->simboluri.size());
    }

    for(unsigned int i = 0; i < this->tranzitii.size(); i++)
    {
        tabel[tranzitii[i].plecare][tranzitii[i].simb.index].push_back(tranzitii[i].destinatie);
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

vector<int> PDA::getValidTranzition(int plecare, int destinatie, int simbol, int caracter_citit)
{
    vector<int> r;
    if(plecare >= 0 && destinatie >= 0)
    {
        for(unsigned int i = 0; i < tranzitii.size(); i++)
        {
            if(tranzitii[i].plecare == plecare && tranzitii[i].destinatie == destinatie && tranzitii[i].simb.index == simbol)
            {
                if(tranzitii[i].caracter_citit.index == caracter_citit)
                {
                    //return i;
                    r.push_back(i);
                }
            }
        }
    }
    return r;
}

bool PDA::check(PDA &lnfa, int stare_index, string word, unsigned int position, stack<int> stiva)
{
    int simbIndex;
    vector<int>::iterator it;
    if(position < word.length())
    {
        string s(1, word[position]);
        simbIndex = lnfa.getSimbolIndexByLitera(s); //indexul simbolului de pe linie/sageata/tranzitie
        if(simbIndex == -1) { cout<<"Simbol invalid, return false"<<endl; return false;}
        if(simbIndex != lnfa.getLambdaCaracterIndex())
        {
            int caracter_index = stiva.top();
            for(it = lnfa.tabel[stare_index][simbIndex].begin(); it != lnfa.tabel[stare_index][simbIndex].end(); it++)
            {
                //ia caracter de pe stivA SI FA CHECK CU EL LA TRANZITIE
                //cout<<endl<<stiva.top()<<endl;
                vector<int> vt = getValidTranzition(stare_index, *it, simbIndex, caracter_index);
                for(unsigned int y = 0; y < vt.size(); y++)
                //if(t != -1)//este tranzitie valida
                {
                    int t = vt[y];
                    stack<int> aux_stiva = stiva;
                    int position2 = position;
                    if(caracter_index != lnfa.getLambdaCaracterIndex())
                    aux_stiva.pop(); //sterge caracterul din top
                    //cout<<endl<<"SIZE: "<<lnfa.tranzitii[t].caractere_scrise.size()-1;
                    for(int c = lnfa.tranzitii[t].caractere_scrise.size()-1; c >= 0; c--)
                    {
                        //cout<<endl<<"c: "<<c;
                        if(lnfa.tranzitii[t].caractere_scrise[c] != lnfa.getLambdaCaracterIndex())
                        {
                            aux_stiva.push(lnfa.tranzitii[t].caractere_scrise[c]);
                        }
                    }
                    if(check(lnfa, *it, word, position2 + 1, aux_stiva))
                    {
                        return true;
                    }
                    //break;
                }
            }
        }
    }
    else if(lnfa.isStareFinalaIndex(stare_index)) return true;

    int lambda_simbIndex = lnfa.getLambdaSimbIndex();
    if(lambda_simbIndex == -1) { return false;}
    //cout<<lambda_simbIndex<<endl;
    int caracter_index = stiva.top();
    //int test = 0;
    for(it = lnfa.tabel[stare_index][lambda_simbIndex].begin(); it != lnfa.tabel[stare_index][lambda_simbIndex].end(); it++)
    {
        //ia caracter de pe stivA SI FA CHECK CU EL LA TRANZITIE
        vector<int> vt = getValidTranzition(stare_index, *it, lambda_simbIndex, caracter_index);
        //if(t != -1)//este tranzitie valida
        for(unsigned int y = 0; y < vt.size(); y++)
        {
            //test = 1;
            stack<int> aux_stiva = stiva;
            int position2 = position;
            int t = vt[y];

            if(caracter_index != lnfa.getLambdaCaracterIndex())
            aux_stiva.pop(); //sterge caracterul din top

            for(int c = lnfa.tranzitii[t].caractere_scrise.size()-1; c >= 0; c--)
                {
                    //cout<<endl<<"c: "<<c;
                    if(lnfa.tranzitii[t].caractere_scrise[c] != lnfa.getLambdaCaracterIndex())
                    {
                        aux_stiva.push(lnfa.tranzitii[t].caractere_scrise[c]);
                    }
                }
            if(check(lnfa, *it, word, position2, aux_stiva))
            {
                //cout<<endl<<"A trimis check din lambda"<<endl;
                return true;
            }
            //break;
        }
    }
    //return false;
    return false;
}

bool PDA::CheckWord(string word)
{
    stack<int>s;
    stiva = s;
    stiva.push(getZ0CaracterIndex());
    return check(*this, this->getStareInitialaIndex(), word, 0, stiva);
}

void PDA::Afiseaza()
{
    cout<<"Nr_stari: "<<this->stari.size()<<endl;
    cout<<"Stari: ";
    for(unsigned int i = 0; i < this->stari.size(); i++)
    {
        cout<<"(i:"<<this->stari[i].index<<",l:"<<this->stari[i].litera<<") ";
    }
    cout<<endl;
    cout<<"Nr simboluri: "<<this->simboluri.size()<<endl;
    cout<<"Simboluri: ";
    for(unsigned int i = 0; i < this->simboluri.size(); i++)
    {
        cout<<"(i:"<<this->simboluri[i].index<<",l:"<<this->simboluri[i].litera<<") ";
    }
    cout<<endl;
    cout<<"Nr caractere: "<<this->caractere.size()<<endl;
    cout<<"Caractere: ";
    for(unsigned int i = 0; i < this->caractere.size(); i++)
    {
        cout<<"(i:"<<this->caractere[i].index<<",l:"<<this->caractere[i].litera<<") ";
    }
    cout<<endl;
    cout<<"Starea initiala: (i:"<<this->stare_initiala.index<<",l:"<<this->stare_initiala.litera<<") ";
    cout<<endl;
    cout<<"Nr stari finale: "<<this->stari_finale.size()<<endl;
    cout<<"Starile finale: ";
    for(unsigned int i = 0; i < this->stari_finale.size(); i++)
    {
        cout<<"(i:"<<this->stari_finale[i].index<<",l:"<<this->stari_finale[i].litera<<") ";
    }
    cout<<endl;
    cout<<"Nr tranzitii: "<<this->tranzitii.size()<<endl;
    for(unsigned int i = 0; i < this->tranzitii.size(); i++)
    {
        cout<<"(plecare_index: "<<this->tranzitii[i].plecare<<", destintatie_index: "<<this->tranzitii[i].destinatie<<" ,litera_simbol: "<<this->tranzitii[i].simb.litera<<" ,simbol_index: "<<this->tranzitii[i].simb.index;
        cout<<", litera_caracter_scos: "<<tranzitii[i].caracter_citit.litera<<", litera_caractere_scrise: ";
        for(unsigned c = 0; c < (this->tranzitii[i].caractere_scrise).size(); c++)
        {
            cout<<tranzitii[i].caractere_scrise[c]<<" ";
        }
        cout<<") "<<endl;
    }
    cout<<endl;
    this->AfiseazaMatrice();
}

/*int PDA::getTranzitieIndexByRule(int plecare, int destinatie, int simbol, int caracter_citit)
{

    for(unsigned int i = 0; i < tranzitii.size(); i++)
    {
        if(tranzitii[i].plecare == plecare && tranzitii[i].destinatie == destinatie && tranzitii[i].simbol == simbol)
        {
            for(unsigned int c = 0; c < tranzitii[i].caractere_scrise.size(); c++)
            {
                if()
            }
        }
    }
}*/

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

stack<int> PDA::getStiva() {
    return this->stiva;
}
