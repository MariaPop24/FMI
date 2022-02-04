#include<iostream>
#include<cstring>

using namespace std;

class Vector
{
    ///date private
    int nr_elemente;
    int *p;

    ///metode
public:

    Vector(int val, int nr); ///constructor pentru initializarea cu un numar dat pe toate componentele
    Vector();               ///constructor pentru initializare
    Vector(Vector& v);      ///constructor de copiere
    ~Vector();              ///destructor

    ///supraincarcarea operatorului de atribuire
    Vector operator=(Vector&);

    ///reactualizarea numarului de componente si initializarea componentelor cu un numar dat
    void reactualizare(int val, int nr);

    ///suma tuturor elementelor vectorului
    long suma();

    ///gasirea maximului si a pozitiei lui
    void maxim();

    ///sortarea crescatoare a vectorului
    void sortare();

    ///setters
    void set_nr_elemente(int t) {nr_elemente = t;}
    void set_p(int z) {for(int i = 0; i < nr_elemente; i++) p[i] = z;}

    ///getters
    int get_nr_elemente() {return nr_elemente;}
    int * get_vector() {return p;}

    ///metoda prin care se face citirea/afisarea a n obiecte
    void citire();

    friend istream& operator>> (istream& in, Vector& s);
    friend ostream& operator<<(ostream& out, Vector& s);
};

///constructor pentru initializarea cu un numar dat pe toate componentele
Vector::Vector(int val, int nr)
{
    p = new int[nr];
    this->nr_elemente = nr;

    for(int i = 0; i < this->nr_elemente; i++)
        (this->p)[i] = val;
}

///constructor pentru initializare
Vector::Vector()
{
    this->nr_elemente = 1;
    p = new int[1];
    p[0] = 1;
}

///constructor de copiere
Vector::Vector(Vector& v)
{
    this->nr_elemente = v.nr_elemente;
    p = new int[this->nr_elemente];

    for(int i = 0; i < this->nr_elemente; i++)
        (this->p)[i] = (v.p)[i];
    cout << "Obiectul a fost copiat" << endl;
}

///destructor
Vector::~Vector()
{
    delete[] p;
    p = nullptr;

}

///supraincarcarea operatorului de atribuire
Vector Vector::operator= (Vector& v)
{
    if(this != &v)
    {
        this->nr_elemente = v.nr_elemente;
        for(int i = 0; i < this->nr_elemente; i++)
            (this->p)[i] = (v.p)[i];
    }
    return *this;
}

///reactualizarea numarului de componente si initializarea componentelor cu un numar dat
void Vector::reactualizare(int val, int nr)
{
    this->nr_elemente = nr;
    p = new int[this->nr_elemente];
    for(int i = 0; i < this->nr_elemente; i++)
        (this->p)[i] = val;
}

///suma tuturor elementelor vectorului
long Vector::suma()
{
    long s = 0;
    for(int i = 0; i < this->nr_elemente; i++)
        s += (this->p)[i];
    return s;
}

///gasirea maximului si a pozitiei lui
void Vector::maxim()
{
    int poz = 0;
    int maxp = p[0];

    for(int i = 1; i < this->nr_elemente; i++)
        if(maxp < p[i])
    {
        maxp = p[i];
        poz = i;
    }
    cout << "Cel mai mare numar din vector este " << maxp << " si apare pe pozitia " << poz << endl;
}

///sortarea crescatoare a vectorului
void Vector::sortare()
{
    int aux;

    for(int i = 0; i < this->nr_elemente - 1; i++)
        for(int j = i; j < this->nr_elemente; j++)
            if(p[i] > p[j])
    {
        aux = (this->p)[i];
        (this->p)[i] = (this->p)[j];
        (this->p)[j] = aux;
    }
}

///supraincarcarea operatorului >>
istream& operator>> (istream& in, Vector& s)
{
    cout << "Numarul de elemente din vector este: ";
    in >> s.nr_elemente;
    for(int i = 0; i < s.nr_elemente; i++)
    {
        cout << "Elementul " << i << " al vectorului este: ";
        in >> s.p[i];
    }
    cout << endl;
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, Vector& s)
{
    out << s.nr_elemente << endl;
    for(int i = 0; i < s.nr_elemente; i++)
        out << s.p[i] << " ";
    return out;
}

///metoda prin care se face citirea/afisarea a n obiecte
void Vector::citire()
{
    int n;
    cout << "Scrieti numarul de obiecte pe care vreti sa le generati: ";
    cin >> n;
    cout << endl;

    Vector ob[n];

    for(int i = 0; i < n; i++)
      {
         cout << "Scrieti numarul de elemente asociat obiectului " << i <<": ";
         cin >> ob[i].nr_elemente;
         ob[i].p = new int[ob[i].nr_elemente];
         cout << endl;
         for(int j= 0; j < ob[i].nr_elemente; j++)
         {
             cout << "Elementul " << j << " al obiectului " << i << " este: ";
             cin >> ob[i].p[j];
         }
        cout << endl;

      }
    cout << "Citirea a fost realizata cu succes!\n\n";
    cout << "Urmeaza afisarea celor " << n << " obiecte create!" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "Primul obiect are " << ob[i].nr_elemente << " elemente, iar valorile sale sunt: ";
        for(int j = 0; j < ob[i].nr_elemente; j++)
            cout << ob[i].p[j] << " ";
        cout << endl;
    }
        cout << endl;
}

int main()
{
    int interactiv = 1, x, y;
    char optiune[100];

    cout << "Comenzile acceptate in cadrul acestui program sunt: ";
    cout << "\n - reactualizare;";
    cout << "\n - suma;";
    cout << "\n - maxim;";
    cout << "\n - sortare;\n\n";

    Vector a;
    a.citire();

    cout << "Acum se va efectua citirea datelor pentru obiectul asupra carora se vor putea executa comenzile de mai sus\n\n";
    Vector b;
    cin >> b;

    while(interactiv)
    {
        cout << "Scrieti o instructiune: ";
        cin >> optiune;
        if(strcmp(optiune, "reactualizare") == 0)
        {
            cout << "Scrieti numarul de componente pe care doriti sa-l aiba vectorul: ";
            cin >> x;
            cout << "Scrieti cu ce valoare doriti sa inlocuiti elementele vectorului: ";
            cin >> y;
            b.reactualizare(y, x);
            cout << "Vectorul reactualizat este: ";
            for(int i = 0; i<b.get_nr_elemente(); i++)
                cout << *(b.get_vector() + i) << " ";
            cout << endl << endl;
        }
        else if(strcmp(optiune, "suma") == 0)
           {
               cout << "Suma elementelor vectorului este: " << b.suma() << endl << endl;
           }
        else if(strcmp(optiune, "maxim") == 0)
           {
                b.maxim();
                cout << endl;
           }
        else if(strcmp(optiune, "sortare") == 0)
            {
                b.sortare();
                cout << "Vectorul de dupa sortare este: ";
                for(int i = 0; i<b.get_nr_elemente(); i++)
                cout << *(b.get_vector() + i) << " ";
                cout << endl << endl;
            }
        else if(strcmp(optiune, "final") == 0)
            {
                interactiv = 0;
                cout << "Programul a ajuns la final!";
            }
        else
            cout << "Instructiune incorecta!" << endl << endl;;
    }

    return 0;
}
