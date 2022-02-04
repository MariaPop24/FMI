#include <iostream>

using namespace std;

class Avocat
{
    ///date de tip protected
protected:

    int cod;
    string nume;
    int nr_procese;
    int *vector_procese;

    ///metode
public:

    Avocat();   ///constructor de initializare
    Avocat(int cod2, string nume2, int nr_procese2);   ///constructor de initializare parametrizat
    Avocat(Avocat &a);  ///constructor de copiere
    ~Avocat();          ///destructor

    ///supraincarcarea operatorului de atribuire
    Avocat& operator= (Avocat&);

    ///supraincarcarea operatorului >> pentru clasa de baza
    friend istream& operator>>(istream&, Avocat&);

    ///supraincarcarea operatorului << pentru clasa de baza
    friend ostream& operator<<(ostream&, Avocat&);

    ///supraincarcarea operatorului >
    friend bool operator>(Avocat &, Avocat &);

};

class Avocat_Oficiu:public Avocat
{
    ///date de tip protected
protected:

    string nume_client;
    int durata;

public:

    ///constructor parametrizat cu transmiterea parametrilor catre constructorul din clasa de baza
    Avocat_Oficiu(int cod3, string nume3, int nr_procese3, string nume_client2, int durata2) : Avocat(cod3, nume3, nr_procese3)
    {
        nume_client = nume_client2;
        durata = durata2;
    }

    ///constructor de initializare cu trimitere explicita catre constructorul de initializare din clasa de baza
    Avocat_Oficiu() : Avocat() {nume_client = "necunoscut"; durata = 0;}

    ///constructor de copiere cu trimitere explicita catre constructorul de copiere din clasa de baza
    Avocat_Oficiu(Avocat_Oficiu &a) : Avocat(a)
    {
        nume_client = a.nume_client;
        durata = a.durata;
    }

    ///supraincarcarea operatorului de atribuire
    Avocat_Oficiu& operator=(Avocat_Oficiu&);

    ///supraincarcarea operatorului >> pentru clasa derivata
    friend istream& operator>>(istream&, Avocat_Oficiu&);

    ///supraincarcarea operatorului << pentru clasa derivata
    friend ostream& operator<<(ostream&, Avocat_Oficiu&);

    ///metoda ceruta
    int gasire(Avocat_Oficiu ob[], int m);

};

///metoda ceruta
int Avocat_Oficiu::gasire(Avocat_Oficiu ob[], int m)
{
    int maxim = ob[0].durata, poz = 0;

    for(int i = 1; i < m; i++)
    {
        if(ob[i].durata > maxim)
        {
            maxim = ob[i].durata;
            poz = i;
        }
    }

    return poz;
}

///constructor de initializare
Avocat::Avocat()
{
    cod = 0;
    nume = "necunoscut";
    nr_procese = 0;
    vector_procese = new int[1];
    vector_procese[0] = 0;
}

///constructor de initializare parametrizat
Avocat::Avocat(int cod2, string nume2, int nr_procese2)
{
    cod = cod2;
    nume = nume2;
    nr_procese = nr_procese2;
    vector_procese = new int[nr_procese];

}

///constructor de copiere
Avocat::Avocat(Avocat &a)
{
    cod = a.cod;
    nume = a.nume;
    nr_procese = a.nr_procese;
    vector_procese = new int[a.nr_procese];

    for(int i = 0; i < nr_procese; i++)
    {
        vector_procese[i] = (a.vector_procese)[i];
    }
}

///destructor
Avocat::~Avocat()
{
    cod = 0;
    nume = "necunoscut";
    nr_procese = 0;
    delete[] vector_procese;
    vector_procese = nullptr;
}

///supraincarcarea operatorului de atribuire pentru clasa de baza
Avocat& Avocat::operator= (Avocat& ob)
{
    if(this != &ob)
    {
        cod = ob.cod;
        nume = ob.nume;
        nr_procese = ob.nr_procese;
        vector_procese = new int[ob.nr_procese];

    for(int i = 0; i < nr_procese; i++)
    {
        vector_procese[i] = (ob.vector_procese)[i];
    }
    }

    return *this;
}

///supraincarcarea operatorului de atribuire pentru clasa derivata
Avocat_Oficiu& Avocat_Oficiu::operator=(Avocat_Oficiu& ob)
{
    if(this != &ob)
    {
        Avocat::operator=(ob);
        nume_client = ob.nume_client;
        durata = ob.durata;
    }

    return *this;
}

///supraincarcarea operatorului >> pentru clasa de baza
istream& operator>>(istream& in, Avocat& ob)
{
    cout << "\nScrieti codul avocatului: ";
    in >> ob.cod;
    cout << "Scrieti numele avocatului: ";
    in >> ob.nume;
    cout << "Scrieti numarul de procese ale avocatului: ";
    in >> ob.nr_procese;
    for(int i = 0; i < ob.nr_procese; i++)
    {
        cout << "Suma primita pentru procesul " << i + 1 << " este: ";
        in >> ob.vector_procese[i];
    }
    return in;
}

///supraincarcarea operatorului >> pentru clasa derivata
istream& operator>>(istream& in, Avocat_Oficiu& ob)
{
    in >> (Avocat&)ob;
    cout << "Scrieti numele clientului: ";
    in >> ob.nume_client;
    cout << "Scrieti durata: ";
    in >> ob.durata;
    return in;
}

///supraincarcarea operatorului << pentru clasa de baza
ostream& operator<<(ostream& out, Avocat& ob)
{
    cout << "\nCodul avocatului este: ";
    out << ob.cod;
    cout << "\nNumele avocatului este: ";
    out << ob.nume;
    cout << "\nNumarul de procese ale avocatului este: ";
    out << ob.nr_procese;
    cout << "\nSumele obtinute de avocat in urma proceselor sunt: ";
    for(int i = 0; i < ob.nr_procese; i++)
    {
        out << ob.vector_procese[i] << " ";
    }
    cout << '\n';
    return out;
}

///supraincarcarea operatorului << pentru clasa derivata
ostream& operator<<(ostream& out, Avocat_Oficiu& ob)
{
    out << (Avocat&)ob;
    cout << "Numele clientului este: ";
    out << ob.nume_client;
    cout << "\nDurata: ";
    out << ob.durata;
    cout << '\n';
    return out;
}

bool operator>(Avocat &a, Avocat &b)
{
    return a.nr_procese > b.nr_procese;
}

int main()
{
    int a;
    int interactiv = 1;
    int n;
    cout << "    ---   Tema aleasa este tema 9   ---\n\n";
    cout << "Comenzile disponibile din cadrul acestui program sunt:";
    cout << "\n1 - Sortarea listei de avocati dupa numarul de procese";
    cout << "\n2 - Aflarea avocatului care a petrecut timpul maxim cu un client";
    cout << "\n3 - Finalul programului\n";
    cout << "\n*campul pentru nume nu accepta spatii\n";

    while(interactiv)
    {
        cout << "\nScrieti o cifra corespunzatoare unei instructiuni: ";
        cin >> a;

        if(a == 1)
        {
            cout << "\nUrmeaza crearea de n elemente!\n\n";
            cout << "Numarul de obiecte create este: ";
            cin >> n;

            Avocat v[n];
            for(int i = 0; i < n; i++)
            {
                cout << "\nCrearea obiectului " << i + 1 << " din lista!\n";
                cin >>v[i];
            }
            for(int i = 0; i < n - 1; i++)
            {
                for(int j = i; j < n; j++)
                {
                    if(v[i] > v[j])
                    {

                        Avocat ax = v[i];
                        v[i] = v[j];
                        v[j] = ax;




                    }
                }

                cout << "\nOrdinea avocatilor dupa numarul de procese este urmatoarea:\n";

                for(int i = 0; i < n; i++)
                    cout << v[i];
            }
        }
        else if(a == 2)
        {
            cout << "\nUrmeaza crearea de n elemente!\n\n";
            cout << "Numarul de obiecte create este: ";
            cin >> n;   cout << '\n';

            Avocat_Oficiu v[n], c;
            for(int i = 0; i < n; i++)
            {
                cout << "Crearea obiectului " << i + 1 << " din lista!\n";
                cin >>v[i];
            }

            int p;
            p = c.gasire(v, n);

            cout << "\nAvocatul care a petrecut timpul maxim cu un client este urmatorul:\n";
            cout << v[p];

            }

        else if(a == 3)
        {
            cout << "\nProgramul a ajuns la final!\n";
            interactiv = 0;
        }
        else cout << "\nInstructiune gresita!\n";
    }

    return 0;
}
