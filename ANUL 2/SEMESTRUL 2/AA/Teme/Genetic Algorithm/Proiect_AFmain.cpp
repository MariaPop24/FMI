#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#define INF 0x3f3f3f3f

using namespace std;

ifstream fin("proiect.in");
ofstream fout("proiect.out");

class Graf
{
    int numar_noduri, numar_muchii;
    vector <vector <int>> lista_adiacenta;

public:

    /// functii de citire pentru grafuri orientate si grafuri neorientate
    void citire_graf_orientat(int, int);
    void citire_graf_neorientat(int, int);

    /// functia folosita pentru problema BFS
    // Complexitate: O(n + m), unde n = numar de noduri si m = numar de muchii
    void bfs_initializare();
    void bfs(int);

    /// functiile folosite pentru problema DFS
    // Complexitate: O(n + m), unde n = numar de noduri si m = numar de muchii
    void dfs_initializare();
    int numar_componente_conexe();
    void dfs(vector <int> &, int nod);

    /// functiile folosite pentru problema CTC (Kosaraju)
    // Complexitate: O(n + m), unde n = numar de noduri si m = numar de muchii
    void ctc_initializare();
    void parcurgere(vector <vector <int>> &);
    void dfs1(int, unordered_map <int, bool>&, vector <int> &);
    void dfs2(int, unordered_map <int, bool>&, vector <int> &, int, vector <vector <int>> &, vector <vector <int>> &);

    /// functia folosita pentru Havel-Hakimi
    // Complexitate: O(n^2)
    void havel_hakimi();

    /// functiile folosite pentru problema sortaret
    // Complexitate: O(n + m), unde n = numar de noduri si m = numar de muchii
    void sortare_topologica_initializare();
    void sortare_topologica();
    void functie(int nod, int vizitarest[], stack <int> &stiva);

    /// functiile folosite pentru problema biconex
    void biconex_initializare();
    void dfs_biconex1();
    void dfs_biconex2(int, int, int &, stack <int> &, vector <vector <int>>&, vector <int> &, vector <int> &, vector<int> &);

    /// functiile folosite pentru problema "Critical Connections"
    void critical_connections_initializare();
    void functie1(vector<int> adiacenta[], vector<vector<int>>& connections)
    {
        for(int i = 0; i < connections.size(); i++)
        {
            adiacenta[connections[i][0]].push_back(connections[i][1]);
            adiacenta[connections[i][1]].push_back(connections[i][0]);
        }
    }

    void dfs_leetcode(vector <int> adiacenta[], int v1[], int v2[], bool vizitare[], int s, int nod, int &numar1, vector <vector <int>> &x)
    {
        vizitare[s] = true; // marcam nodul ca fiind vizitat
        v1[s] = v2[s] = ++numar1;

        for(int &i: adiacenta[s])   // vizitam toti vecinii nodului s
        {
            if(!vizitare[i])    // daca nu este vizitat
            {
                dfs_leetcode(adiacenta, v1, v2, vizitare, i, s, numar1, x);
                v2[s] = min(v2[s], v2[i]);  // verificam daca arborele de radacina s are vreo muchie incidenta cu unul din predecesorii lui i

                if(v2[i] > v1[s])   // daca nodul gasit a putut urca mai sus de nodul initial
                    x.push_back({s, i});    // adaugam muchia critica [s, i]
            }
            else if(i != nod)       //daca nodul se afla mai sus de nodul curent, am gasit o muchie de intoarcere si actualizam v2[s]
                v2[s] = min(v2[s], v1[i]); //cu nivelul nodului gasit
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections, vector <vector <int>> &x)
    {

        vector <int> adiacenta[n];
        functie1(adiacenta, connections);

        int v1[n];  // momentul vizitarii unui nod
        fill(v1, v1 + n, 0);    // initializam v1 cu 0

        int v2[n];  // cat de sus poate merge un nod pe o muchie de intoarcere
        fill(v2, v2 + n, 0);    // initializam v2 cu 0

        bool vizitare[n];
        fill(vizitare, vizitare + n, false);    // vector vizitare

        int numar1 = 0;
        dfs_leetcode(adiacenta, v1, v2, vizitare, 0, -1, numar1, x);
        return x;
    }

    /// functiile folosite pentru problema APM (Arbore partial de cost minim) (Kruskal)
    // Complexitate: O(m * log m), m = numar de muchii
    void apm_initializare();
    void apm(vector <vector <int>>&);
    int gasire(int, int[]);
    void unire(int, int, int[], int[]);

    /// functiile folosite pentru problema "Paduri de multimi disjuncte" (Disjoint)
    void disjoint();
    int gasire_multime(int, int[]);
    void operatie_tip_1(int, int, int[], int[]);

    /// functiile folosite pentru problema "Algoritmul lui Dijkstra"
    // Complexitate: O(m * log n)
    void dijkstra1();
    vector <int> dijkstra2(const int a, vector <vector <pair<int, int>>> &lista_adiacenta2)
    {
        int b;
        vector <int> lungime_drum(numar_noduri + 1, INF);   // aici retinem lungimea drumurilor cautate pe care le initializam cu infinit
        vector <bool> pq(numar_noduri + 1, 0);  // pentru a marca nodurile vizitate
        // priority queue folosit pentru a retine nodul cel mai apropiat
        priority_queue <pair <int, int>, vector <pair <int, int>>, greater<pair<int, int>>> coada;

        // lungimea drumul de la nodul de incepere la el insusi este 0 si il adaugam in coada
        lungime_drum[a] = 0;
        coada.push(make_pair(0, a));

        // parcurgem elementele priority queue-ului
        while(!coada.empty())
        {
            b = coada.top().second; // cel mai mic nod
            coada.pop();

            // daca nu a fost vizitat
            if(pq[b] == 0)
            {
                pq[b] = 1;  // il marcam ca fiind vizitat
                // ii verificam vecinii
                for(int i = 1; i < lista_adiacenta2[b].size(); i++)
                    // daca distanta pana la nod e mai mare decat lungimea calculata pana la momentul acesta, o modificam
                    if(lungime_drum[lista_adiacenta2[b][i].first] > lungime_drum[b] + lista_adiacenta2[b][i].second)
                {
                    lungime_drum[lista_adiacenta2[b][i].first] = lungime_drum[b] + lista_adiacenta2[b][i].second;
                    coada.push(make_pair(lungime_drum[lista_adiacenta2[b][i].first], lista_adiacenta2[b][i].first));
                }
            }
        }

        return lungime_drum;

    }

    /// functiile folosite pentru problema "Algoritmul Bellman-Ford"
    // Complexitate: O(n * m)
    void bellman_ford1();
    vector <int> bellman_ford2(const int a, vector <vector <pair<int, int>>> &lista_adiacenta2)
    {
            int ok = 1, b;
            queue <int> coada;      // coada in care stocam nodurile
            vector <bool> m(numar_noduri + 1, false);   // vector cu ajutorul caruia verificam daca un nod a fost vizitat sau nu
            vector <int> v(numar_noduri + 1, 0);          // vector cu ajutorul caruia contorizam de cate ori a fost relaxat un nod
            vector <int> distanta(numar_noduri + 1, INF);       // vector in care tinem minte distanele de la nodul de inceput la toate celelalte (il initializam cu infinit)

            // marcam nodul de la care incepem
            m[a] = 1;           // marcam nodul de inceput ca fiind vizitat
            distanta[a] = 0;    // distanta de la primul nod la el insusi este 0
            coada.push(a);      // coada in care tinem minte nodurile

            while(ok && !coada.empty())     // luam la rand nodurile din coada cat timp se afla acolo
            {
                b = coada.front();  // stocam nodul din capul cozii in b
                m[b] = 0;
                coada.pop();

                // parcurgem lista de adiacenta a nodului curent
                for(int i = 1; i < lista_adiacenta2[b].size(); i++)
                    // daca avem un cost mai mare decat costul pe care l-am forma cu muchia actuala, il modificam
                    if(distanta[b] + lista_adiacenta2[b][i].second < distanta[lista_adiacenta2[b][i].first])
                {
                    v[lista_adiacenta2[b][i].first]++;
                    distanta[lista_adiacenta2[b][i].first] = distanta[b] + lista_adiacenta2[b][i].second;

                    // daca al doilea nod nu este in queue, il adaugam
                    if(m[lista_adiacenta2[b][i].first] == 0)
                    {
                        coada.push(lista_adiacenta2[b][i].first);
                        m[lista_adiacenta2[b][i].first] = 1;
                    }

                    // daca un nod a fost relaxat de un numar mai mare de ori decat numarul de noduri, inseamna ca exista un ciclu
                    if(v[lista_adiacenta2[b][i].first] >= numar_noduri)
                        ok = 0;

                }
            }

    if(ok == 0)
        distanta.clear();

    return distanta;
    }

    /// functiile folosite pentru problema "Diametrul unui arbore"
    // Complexitate: O(n)
    void darb_initializare();
    void bfs_darb(int, int &, int &);

    /// functiile folosite pentru problema "Floyd-Washall/Roy-Floyd"
    // Complexitate: O(n ^ 3)
    void roy_floyd_initializare();
    vector <vector <int>> roy_floyd(vector <vector <int>>matrice_ponderi, int cost)
    {
        vector <vector <int>> distante = matrice_ponderi;

        for(int i = 1; i <= numar_noduri; i++)
            for(int j = 1; j <= numar_noduri; j++)
                if(i != j && !matrice_ponderi[i][j])
                    distante[i][j] = cost;      // adaugam in matricea drumurilor minime costurile muchiilor pentru nodurile adiacente

        for(int i = 1; i <= numar_noduri; i++)
            for(int j = 1; j <= numar_noduri; j++)      // incercam sa gasim pentru orice 2 noduri j si k, un nod i pe care daca-l parcurgem, obtinem o distanta mai mica
                for(int k = 1; k <= numar_noduri; k++)  // intre nodurile j si k
                    if(j != k && distante[j][k] > distante[j][i] + distante[i][k])  // verificam daca se indeplineste conditia si daca j si k sunt acelasi nod
                        distante[j][k] = distante[j][i] + distante[i][k];

        return distante;
    }

    /// functiile folosite pentru problema "Flux maxim" (Edmonds-Karp)
    // Complexitate: O(max_flow * m), unde m = numar de muchii, max_flow = flux maxim
    void flux_maxim_initializare();
    int max_flow(vector <vector <pair <int, int>>>, int, int, int);
    int bfs_maxflow(int, int, vector <vector <int>>&, vector<int>&, vector <vector <int>>&, vector <int>&, vector <vector<int>>&);

    /// functiile folosite pentru problema "Ciclu hamiltonian de cost minim"
    // Complexitate: O(m * 2^n)
    void hamilton_initializare();
    int hamilton(vector <vector <pair <int, int>>>);

    /// functiile folosite pentru problema "Cuplaj maxim in graf bipartit"
    void cuplaj_maxim_initializare();
    int dfs_cuplaj_maxim(int, vector <int> &, int[], int[]);

    /// functia folosita pentru problema "Ciclu Eulerian" (Hierholzer)
    void ciclu_eulerian();
};

/// functia de citire pentru grafuri orientate
void Graf :: citire_graf_orientat(int numar_noduri, int numar_muchii)
{
    int capat_stang, capat_drept;
    lista_adiacenta.resize(numar_noduri + 1);

    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> capat_stang >> capat_drept;
        lista_adiacenta[capat_stang].push_back(capat_drept);
    }
}

/// functia de citire pentru grafuri neorientate
void Graf :: citire_graf_neorientat(int numar_noduri, int numar_muchii)
{
    int capat_stang, capat_drept;
    lista_adiacenta.resize(numar_noduri + 1);

    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> capat_stang >> capat_drept;
        lista_adiacenta[capat_stang].push_back(capat_drept);
        lista_adiacenta[capat_drept].push_back(capat_stang);
    }
}

/// functii pentru problema "BFS"
void Graf :: bfs_initializare()
{
    int nod_start;

    fin >> numar_noduri >> numar_muchii >> nod_start;

    citire_graf_orientat(numar_noduri, numar_muchii);

    bfs(nod_start);

    lista_adiacenta.clear();
}

/// algoritmul bfs - parcurgerea in latime a unui graf
void Graf :: bfs(int nod_start)
{
    int nod_curent;
    queue <int> coada;
    int vizitare[numar_noduri + 1] = {};

    coada.push(nod_start);  // adaugam in coada nodul de la care se incepe parcurgerea
    vizitare[nod_start] = 1;    // marcam nodul de start ca fiind vizitat

    int cost_nod[numar_noduri + 1] = {};   // pentru retinerea numarului minim de arce ce trebuie parcurse
    cost_nod[nod_start] = 0;    // numarul de arce de la nodul de start la el insusi este 0

    while(coada.size() > 0)
    {
        nod_curent = coada.front();

        // se iau la rand nodurile adiacente cu nodul curent
        for(int i = 0; i < lista_adiacenta[nod_curent].size(); i++)
            if(!vizitare[lista_adiacenta[nod_curent][i]])   // daca un nod adiacent cu nodul curent nu este vizitat se executa codul de mai jos
        {
            coada.push(lista_adiacenta[nod_curent][i]); // adaugam in queue nodurile nevizitate
            cost_nod[lista_adiacenta[nod_curent][i]] = cost_nod[nod_curent] + 1;    // actualizam numarul de arce ce trebuie parcurse
            vizitare[lista_adiacenta[nod_curent][i]] = 1;   // le marcam ca fiind vizitate
        }
        coada.pop();    // scoatem din coada nodul curent
    }

    for(int i = 1; i <= numar_noduri; i++)
        if(vizitare[i])     // daca un nod a fost vizitat, inseamna ca este accesibil din nodul de start
            fout << cost_nod[i] << " "; // afisam numarul minim de arce ce trebuie parcurse de la nodul de start la nodul i
        else
            fout << "-1 ";  // afisam -1 pentru nodurile la care nu se poate ajunge din nodul de start

}

/// functii folosite pentru problema "DFS"
void Graf :: dfs_initializare()
{
    fin >> numar_noduri >> numar_muchii;

    citire_graf_neorientat(numar_noduri, numar_muchii);

    fout << numar_componente_conexe();

    lista_adiacenta.clear();
}

/// functia pentru numararea componentelor conexe
int Graf :: numar_componente_conexe()
{
    int numar_componente = 0;
    vector <int> vizitare;

    for(int i = 1; i <= numar_noduri + 1; i++)
        vizitare.push_back(0);      // vector folosit pentru a sti daca un nod a fost sau nu vizitat

    for(int i = 1; i <= numar_noduri; i++)
        if(!vizitare[i])    // daca nodul a fost vizitat, inseamna ca apartine unei componente conexe numarate deja
    {
        dfs(vizitare, i);   // numarul de componente conexe este egal cu numarul de apeluri ale functiei dfs din interiorul functiei numar_componente_conexe
        numar_componente++;
    }
    return numar_componente;
}

/// algoritmul dfs - parcurgerea in adancime a grafului
void Graf :: dfs(vector <int> &vizitare, int nod)
{
    // nu avem nevoie nevoie sa adaugam nodurile intr-o coada, ci doar sa tinem minte daca un nod a fost vizitat sau nu
    vizitare[nod] = 1;  // marcam nodul curent ca fiind vizitat

    for(int i = 0; i < lista_adiacenta[nod].size(); i++)    // verificam nodurile adiacente cu nodul curent
        if(!vizitare[lista_adiacenta[nod][i]])          // daca nu a fost vizitat, continuam parcurgerea in adancime a grafului
            dfs(vizitare, lista_adiacenta[nod][i]);    // apelam in mod recursiv functia dfs pentru a parcurge toate nodurile dintr-o componenta conexa

}

/// functii folosite pentru problema "CTC"
void Graf :: ctc_initializare()
{
    int capat_stang, capat_drept;
    vector <vector <int>> lista_adiacenta1;

    fin >> numar_noduri >> numar_muchii;

    lista_adiacenta.resize(numar_noduri + 1);
    lista_adiacenta1.resize(numar_noduri + 1);

    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> capat_stang >> capat_drept;
        lista_adiacenta[capat_stang].push_back(capat_drept);    // listele de adiacenta pentru graful dat
        lista_adiacenta1[capat_drept].push_back(capat_stang);   // listele de adiacenta pentru graful transpus
    }

    parcurgere(lista_adiacenta1);

    lista_adiacenta.clear();
    lista_adiacenta1.clear();
}

/// functie pentru problema "CTC" pentru rezolvarea careia s-a folosit algoritmul lui Kosaraju
void Graf :: parcurgere(vector <vector <int>> &lista_adiacenta1)
{
    int numar_componente = 0;
    vector <int> st;    // vectorul in care vom stoca nodurile
    vector < vector <int>> componenta;
    unordered_map <int, bool> vizitare1, vizitare2;

    for(int i = 1; i <= numar_noduri; i++)
        if(!vizitare1[i])
            dfs1(i, vizitare1, st);     // realizam o parcurgere in adancime a grafului dat

    for(int i = st.size() - 1; i >= 0; i--)
        if(!vizitare2[st[i]])   // pornind de la ultimul nod adaugat in vector, realizam parcurgerea in adancime a grafului transpus
    {
        dfs2(st[i], vizitare2, st, numar_componente, componenta, lista_adiacenta1);
        numar_componente++;     // numarul de componente conexe tare este egal cu numarul de apeluri ale functiei de parcurgere in adancime a grafului transpus
    }

    // afisarea rezultatului
    fout << numar_componente << '\n';

    for(int i = 0; i < numar_componente; i++)   // pentru fiecare componenta
    {
        for(int j = 0; j < componenta[i].size(); j++)   // afisam elementele sale
            fout << componenta[i][j] << " ";

        fout << '\n';
    }
}

/// primul algoritm DFS pentru problema "CTC"
void Graf :: dfs1(int nod, unordered_map <int, bool> &vizitare1, vector <int> &st)
{
    vizitare1[nod] = true;  // marcam nodul curent ca fiind vizitat

    for(int i = 0; i < lista_adiacenta[nod].size(); i++)    // pentru fiecare nod adiacent cu nodul curent
        if(!vizitare1[lista_adiacenta[nod][i]])             // verificam daca a fost vizitat
            dfs1(lista_adiacenta[nod][i], vizitare1, st);   // apelam in mod recursiv primul algoritm DFS pentru graful dat

    st.push_back(nod);      // introducem in vector nodurile in ordinea inversa fata de cea in care au fost vizitate
}

/// al doilea algoritm DFS pentru problema "CTC"
void Graf :: dfs2(int nod, unordered_map <int, bool> &vizitare2, vector <int> &st, int numar_componente, vector <vector <int>> &componenta, vector <vector <int>> &lista_adiacenta1)
{
    vizitare2[nod] = true;      // marcam nodul curent ca fiind vizitat
    componenta.resize(numar_componente + 1);        // daca se va descoperi inca o componenta tare conexa, se va adauga spatiu pentru stocarea elementelor sale
    componenta[numar_componente].push_back(nod);    // adaugam in fiecare componenta tare conexa nodurile corespunzatoare

    for(int i = 0; i < lista_adiacenta1[nod].size(); i++)   // pentru fiecare nod adiacent cu nodul curent
        if(!vizitare2[lista_adiacenta1[nod][i]])    // verificam daca a fost vizitat
            dfs2(lista_adiacenta1[nod][i], vizitare2, st, numar_componente, componenta, lista_adiacenta1);    // apelam in mod recursiv al doilea algoritm DFS pentru graful transpus
}

/// Havel-Hakimi
void Graf :: havel_hakimi()
{
    int ok = 1, nod, numar_havel;
    vector <int> grade;

    fin >> numar_havel;

    // citim lista de numere pe care le introducem intr-un vector
    while(numar_havel)
    {
        fin >> nod;
        grade.push_back(nod);
        numar_havel--;
    }

    // structura repetitiva cu ajutorul careia aflam raspunsul
    while(true)
    {
        sort(grade.begin(), grade.end(), greater<>());  // sortam lista de grade pentru ca gradul cel mai mare sa fie primul

        // daca cel mai mare grad din lista este 0, atunci putem construi un graf
        if(!grade[0])
            break;

        int x = grade[0];           // retinem primul element din vector pentru a putea realiza verificari
        grade.erase(grade.begin()); // conform algoritmului Havel-Hakimi, eliminam primul element din lista

        // daca cel mai mare grad al unui nod este mai mare decat numarul de elemente ramase in lista, adica de noduri, inseamna ca nu putem construi un graf
        // pentru ca nodul cu gradul cel mai mare nu ar avea un numar suficient de noduri cu care sa se conecteze, astfel ca ii dam lui ok valoarea 0
        // pentru a putea iesi din structura repetitiva
        if(grade.size() < x)
        {
            ok = 0;
            break;
        }

        for(int i = 0; i < x; i++)
        {
            grade[i]--;     // conform algoritmului, "eliminam" muchiile incidente cu nodul eliminat scazand cu 1 din gradele urmatoarelor x noduri

            if(grade[i] < 0)    // daca intalnim un nod cu un grad negativ, nu putem construi un graf
            {
                ok = 0;
                break;
            }
        }

        if(ok == 0)     // conditie pusa pentru iesirea din while pentru cazul in care ok ar fi devenit 0 in cadrul structurii repetitive for
            break;
    }

    if(ok)      // daca ok nu a devenit 0 in timpul structurii repetitive while, atunci inseamna ca putem construi un graf
        fout << "Da";
    else
        fout << "Nu";

}

/// functii folosite pentru problema "sortaret"
void Graf :: sortare_topologica_initializare()
{
    fin >> numar_noduri >> numar_muchii;

    citire_graf_orientat(numar_noduri, numar_muchii);

    sortare_topologica();

    lista_adiacenta.clear();
}


/// pentru sortarea topologica
void Graf :: sortare_topologica()
{
    stack <int> stiva;  // stiva in care stocam nodurile sortate invers topologic
    int vizitare[numar_noduri + 1] = {};

    for(int i = 1; i <= numar_noduri; i++)
        if(!vizitare[i])
            functie(i, vizitare, stiva);    // folosim algoritmul DFS pentru fiecare componenta conexa a grafului

    // afisam nodurile sortate topologic
    while(!stiva.empty())
    {
        fout << stiva.top() << " ";
        stiva.pop();
    }
}

/// apartine problemei "sortaret" - algoritm DFS
void Graf :: functie(int nod, int vizitare[], stack <int> &stiva)
{
    vizitare[nod] = 1;  // marcam nodul curent ca fiind vizitat

    for(int i = 0; i < lista_adiacenta[nod].size(); i++)         // verificam nodurile adiacente cu nodul curent
        if(!vizitare[lista_adiacenta[nod][i]])                  // daca nu a fost vizitat, continuam parcurgerea in adancime a grafului
            functie(lista_adiacenta[nod][i], vizitare, stiva);  // apelam in mod recursiv functia pentru a parcurge toate nodurile nevizitate
                                                                // dintr-o componenta conexa
    stiva.push(nod);    // dupa ce am vizitat toate nodurile care depind de nodul curent, adaugam nodul curent in stiva
}

/// functii folosite pentru problema "Biconex"
void Graf :: biconex_initializare()
{
    fin >> numar_noduri >> numar_muchii;

    citire_graf_neorientat(numar_noduri, numar_muchii);

    dfs_biconex1();

    lista_adiacenta.clear();
}

/// pentru problema biconex
void Graf :: dfs_biconex1()
{
    int numar = 0;      // numarul de componente biconexe
    stack <int> st;
    vector <int> nivel1(numar_noduri + 1);
    vector <int> nivel2(numar_noduri + 1);
    vector <int> nivel3(numar_noduri + 1);
    vector <vector <int>> componente_biconexe(numar_noduri + 1);

    dfs_biconex2(1, 0, numar, st, componente_biconexe, nivel1, nivel2, nivel3); // facem o parcurgere in adancime incepand cu primul nod

    // afisarea rezultatului
    fout << numar << '\n';

    for(int i = 0; i < numar; i++)
    {
        for(int j = 0; j < componente_biconexe[i].size(); j++)
            fout << componente_biconexe[i][j] << " ";
        fout << '\n';
    }
}

void Graf :: dfs_biconex2(int x, int parinte, int &numar, stack <int> &st, vector <vector <int>>& componente_biconexe, vector <int> &nivel1, vector <int> &nivel2, vector <int> &nivel3)
{
        st.push(x);
        nivel2[x] = nivel2[parinte] + 1;
        nivel1[x] = nivel2[x];
        nivel3[x] = 1;

        for(int i = 0; i < lista_adiacenta[x].size(); i++)
        {
            int y = lista_adiacenta[x][i];

            if(parinte != y)
                if(nivel3[y] == 1)
            {
                if(nivel1[x] > nivel2[y])
                    nivel1[x] = nivel1[y];
            }
            else
            {
                dfs_biconex2(lista_adiacenta[x][i], x, numar, st, componente_biconexe, nivel1, nivel2, nivel3);
                if(nivel1[x] > nivel1[y])
                    nivel1[x] = nivel1[lista_adiacenta[x][i]];
                if(nivel2[x] <= nivel1[y])
                {
                    while(st.top() != y)
                    {
                        componente_biconexe[numar].push_back(st.top());
                        st.pop();
                    }

                    componente_biconexe[numar].push_back(y);
                    componente_biconexe[numar].push_back(x);
                    st.pop();
                    numar++;
                }
            }
        }
}

/// functia de citire pentru problema "critical connections"
void Graf :: critical_connections_initializare()
{
    int n, capat_stang, capat_drept;
    vector <vector <int>> connections;
    vector<vector<int>> x;

    fin >> n;

    for(int i = 0; i < n; i++)
    {
        fin >> capat_stang >> capat_drept;
        connections.push_back({capat_stang, capat_drept});
    }

    // stocam in vectorul rezultat muchiile critice
    vector <vector <int>> rezultat = criticalConnections(n, connections, x);

    for(int i = 0; i < rezultat.size(); i++)
    {
        for(int j = 0; j < rezultat[i].size(); j++)
            fout << rezultat[i][j] << " ";
        fout << '\n';
    }
}

/// functiile folosite pentru functia "Arbore partial de cost minim"
void Graf :: apm_initializare()
{
    int capat_stang, capat_drept, cost;
    vector <vector <int>> muchii;

    fin >> numar_noduri >> numar_muchii;

    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> capat_stang >> capat_drept >> cost;
        muchii.push_back({capat_stang, capat_drept, cost});
    }

    apm(muchii);
}

void Graf :: apm(vector <vector <int>> &muchii)
{
    // adaugam muchii fara a obtine un ciclu, retinand parintele fiecarui nod in noduri1
    int numar_muchii_selectate = 0;
    int cost_minim = 0;
    int noduri1[numar_noduri + 1], noduri2[numar_noduri + 1];

    for(int i = 1; i <= numar_noduri; i++)
        noduri1[i] = i;         // setam initial ca tatal fiecarui nod sa fie el insusi pentru a sti cand nu are parinte

    // sortam muchiile in functie de cost
    sort(muchii.begin(), muchii.end(), [](vector <int> a, vector <int> b) {return a[2] < b[2];});

    vector <pair <int, int>> rezultat;

    for(int i = 0; i < muchii.size(); i++)
    {
        if(numar_muchii_selectate == numar_noduri - 1)
            break;

        if(gasire(muchii[i][0], noduri1) == gasire(muchii[i][1], noduri1))  // verificam cazul in care capetele unei muchii apartin unor arbori cu acee
            continue;                                                       // pentru ca vrem sa evitam formarea unui ciclu
        // daca 2 noduri au aceeasi radacina, nu mai executam codul de mai jos din for
        numar_muchii_selectate++;       // daca 2 noduri nu au aceeasi radacina, o adaugam, incrementand numarul de muchii selectate
        cost_minim += muchii[i][2];     // si adaugand costul muchiei curente la costul minim final

        unire(muchii[i][0], muchii[i][1], noduri1, noduri2);       // unim arborii din care fac parte cele 2 noduri
        rezultat.push_back({muchii[i][0], muchii[i][1]});   // adaugam muchia care va face parte din arbore
    }
    fout << cost_minim << '\n';
    fout << rezultat.size() << '\n';

    for(auto x : rezultat)
        fout << x.second << " " << x.first << '\n';     // afisam capetele muchiilor ce apartin arborelui solutie
}

/// realizam compresia drumurilor
int Graf :: gasire(int a, int noduri1[])
{
    int aux = a, aux2;

    while(noduri1[aux] != aux)
    {
        aux = noduri1[aux];     // aflam radacina arborelui din care face parte nodul curent
    }

    while(a != aux)             // mai parcurgem o data drumul de la nod la radacina si unim toate nodurile direct de radacina, astfel incat,
    {                           // cand vom mai avea o interogare pentru unul din aceste noduri, vom ajunge intr-un singur pas la radacina
        aux2 = noduri1[a];
        noduri1[a] = aux;
        a = aux2;
    }

    return a;
}

/// functie cu ajutorul careia unim 2 arbori
void Graf :: unire(int a, int b, int noduri1[], int noduri2[])
{
    a = gasire(a, noduri1);
    b = gasire(b, noduri1);

    // unim arborii in functie de rang
    if(noduri2[a] < noduri2[b])     // daca a are rangul mai mic decat al lui b, atunci parintele sau devine b pentru a obtine un arbore cu rang cat mai mic
        noduri1[a] = b;
    else
    {
        noduri1[b] = a;             // in caz contrar, a devine parintele lui b
        if(noduri2[a] == noduri2[b]) noduri2[a]++;  // daca pe deasupra rangurile sunt egale, atunci rangul lui a creste dupa unire
    }
}

/// functii folosite pentru problema "Paduri de multimi disjuncte"
void Graf :: disjoint()
{
    int numar_multimi, numar_operatii, numar1, numar2, tip_operatie;
    int parinte[10001], dimensiune[10001];

    fin >> numar_multimi >> numar_operatii;

    for(int i = 0; i < numar_multimi; i++)
    {
        dimensiune[i] = 1;  // rangul fiecarui nod este 1 initial
        parinte[i] = i; // setam initial ca tatal fiecarui nod sa fie el insusi pentru a sti cand nu are parinte
    }

    // executam fiecare operatie in parte pe masura ce citim datele
    for(int i = 0; i < numar_operatii; i++)
    {
        fin >> tip_operatie >> numar1 >> numar2;

        if(tip_operatie == 1)
            // unim radacinile arborilor corespunzatori multimilor celor 2 noduri
            operatie_tip_1(numar1, numar2, dimensiune, parinte);

            // verific daca radacina arborilor in care se afla cele 2 noduri este aceeasi
        else if(gasire_multime(numar1, parinte) == gasire_multime(numar2, parinte))
                    fout << "DA" << '\n';
        else fout << "NU" << '\n';
    }
}

int Graf :: gasire_multime(int a, int parinte[])
{
    while(a != parinte[a])
        a = parinte[a];     // cautam radacina arborelui din care face parte nodul a

    return a;
}

void Graf :: operatie_tip_1(int a, int b, int dimensiune[], int parinte[])
{
    a = gasire_multime(a, parinte);
    b = gasire_multime(b, parinte);

    // unim arborii in functie de rang
    if(dimensiune[b] <= dimensiune[a])  // daca b are rangul mai mic sau egal cu al lui a, atunci parintele sau devine a
    {
        dimensiune[a] += dimensiune[b];
        parinte[b] = a;
    }
    else                                // in caz contrar, parintele lui a devine b
    {
        dimensiune[b] += dimensiune[a];
        parinte[a] = b;
    }
}

/// functie folosita pentru problema "Algoritmul lui Dijkstra"
void Graf :: dijkstra1()
{
    int nod1, nod2, lungime_arc;
    vector <pair <int, int>> lista(1, make_pair(-1, -1));
    vector <vector <pair<int, int>>> lista_adiacenta2;

    fin >> numar_noduri >> numar_muchii;

    for(int i = 0; i <= numar_noduri + 1; i++)
        lista_adiacenta2.push_back(lista);

    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> nod1 >> nod2 >> lungime_arc;
        lista_adiacenta2[nod1].push_back(make_pair(nod2, lungime_arc));
    }

    // in acest vector am stocat rezultatul
    vector <int> lungime_drum = dijkstra2(1, lista_adiacenta2);

    // afisarea rezultatului
    for(int i = 2; i <= numar_noduri; i++)
        if(lungime_drum[i] != INF)
            fout << lungime_drum[i] << " ";
        else
            fout << 0 << " ";
}

/// functie folosite pentru problema "Algoritmul Bellman-Ford"
void Graf :: bellman_ford1()
{
    int nod1, nod2, cost;
    vector <pair <int, int>> x(1, make_pair(-1, -1));
    vector <vector <pair<int, int>>> lista_adiacenta2;

    fin >> numar_noduri >> numar_muchii;

    for(int i = 0; i <= numar_noduri + 1; i++)
        lista_adiacenta2.push_back(x);

    // citire date
    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> nod1 >> nod2 >> cost;
        lista_adiacenta2[nod1].push_back(make_pair(nod2, cost));
    }

    // retinem in vectorul distanta rezultatul
    vector <int> distanta = bellman_ford2(1, lista_adiacenta2);

    // afisarea rezultatului
    if(!distanta.size())
        fout << "Ciclu negativ!";
    else for(int i = 2; i <= numar_noduri; i++)
        fout << distanta[i] << " ";
}

/// functiile folosite pentru problema "Diametrul unui arbore"
void Graf :: darb_initializare()
{
    int capat_stang, capat_drept, distanta, nod1, nod2;

    fin >> numar_noduri;
    lista_adiacenta.resize(numar_noduri + 2);

    for(int i = 0; i <= numar_noduri; i++)
        lista_adiacenta[i].push_back(-1);

    for(int i = 0; i < numar_noduri - 1; i++)
    {
        fin >> capat_stang >> capat_drept;
        lista_adiacenta[capat_stang].push_back(capat_drept);
        lista_adiacenta[capat_drept].push_back(capat_stang);
    }

    // realizam 2 parcurgeri in latime pornind prima parcurgere de la primul nod si continuand cu a doua din ultimul nod in care am ajuns
    // cea mai indepartata frunza din prima parcurgere reprezinta un capat al lantului
    // urmand sa ii gasim celalalt capat in ultimul nod in care ajungem cu cea de a doua parcurgere
    bfs_darb(1, nod1, distanta);
    bfs_darb(nod1, nod2, distanta);

    fout << distanta;

    lista_adiacenta.clear();
}

/// algoritm BFS pentru gasirea diametrului unui arbore
void Graf :: bfs_darb(int s, int &u, int &d)
{
    int a;
    int vizitat[numar_noduri + 1] = {};
    int dist[numar_noduri + 1] = {};    // stocam distanta de la nodul de start la fiecare nod din graf
    queue <int> coada;

    d = 0;      // in d retinem distanta maxima pentru a putea gasi cel mai indepartat nod
    dist[s] = 1;    // numaram nodurile distanta
    vizitat[s] = 1;     // marcam nodul de start ca fiind vizitat
    coada.push(s);  // adaugam in coada nodul de la care se porneste parcurgerea

    while(!coada.empty())   // cat timp mai avem noduri de vizitat executam codul de mai jos
    {
        a = coada.front();     // stocam in a primul nod din coada pe care il eliminam
        coada.pop();

        for(int i = 1; i < lista_adiacenta[a].size(); i++)
            if(vizitat[lista_adiacenta[a][i]] == 0) // daca un nod adiacent cu nodul curent nu este vizitat, il adaugam in coada
        {
            vizitat[lista_adiacenta[a][i]] = 1;     // il marcam ca fiind vizitat
            coada.push(lista_adiacenta[a][i]);      // il adaugam in coada
            dist[lista_adiacenta[a][i]] = dist[a] + 1;  // incrementam cu 1 pentru a masura distanta de la nodul la care ne aflam la nodul adiacent curent
        }
    }

    // la final, aflam care este cel mai indepartat nod de nodul de la care am pornit parcurgerea
    for(int i = 1; i <= numar_noduri; i++)
        if(d < dist[i])
        {
            u = i;
            d = dist[i];
        }
}

/// functie folosita pentru problema "Roy-Floyd"
void Graf :: roy_floyd_initializare()
{
    // citire date
    fin >> numar_noduri;

    vector <vector <int>> matrice_ponderi;
    matrice_ponderi.resize(numar_noduri + 1);

    // citim matricea ponderilor
    for(int i = 1; i <= numar_noduri; i++)
    {
        matrice_ponderi[i].resize(numar_noduri + 1);
        for(int j = 1; j <= numar_noduri; j++)
            fin >> matrice_ponderi[i][j];
    }

    // in matricea distante vom retine matricea drumurilor minime
    vector <vector <int>> distante = roy_floyd(matrice_ponderi, 1001);

    // afisare rezultat
    for(int i = 1; i <= numar_noduri; i++)
    {
        for(int j = 1; j <= numar_noduri; j++)
            fout << distante[i][j] << " ";
        fout << '\n';
    }

    matrice_ponderi.clear();
}

/// functii folosite pentru problema "Flux maxim"
void Graf :: flux_maxim_initializare()
{
    int nod1, nod2, capacitate;

    fin >> numar_noduri >> numar_muchii;

    vector <vector <pair <int, int>>> lista_adiacenta;
    lista_adiacenta.resize(numar_noduri + 1);

    for(int i = 0; i < numar_muchii; i++)   // citim graful cu costuri
    {
        fin >> nod1 >> nod2 >> capacitate;
        lista_adiacenta[nod1].push_back(make_pair(nod2, capacitate));
    }

    fout << max_flow(lista_adiacenta, 1, numar_noduri, 110001);

    lista_adiacenta.clear();
}

/// bfs cu ajutorul caruia aflam daca exista un drum de la nodul sursa la nodul destinatie
int Graf :: bfs_maxflow(int sursa, int destinatie, vector <vector <int>>& capacitati, vector <int> &tata, vector <vector <int>>&flux, vector <int> &vizitat, vector <vector<int>>&rezidual)
{
    int a;
    queue <int> coada;  // ne ajutam de o coada pentru a retine nodurile pe care trebuie sa le parcurgem
    coada.push(sursa);  // adaugam nodul sursa in coada

    tata.assign(capacitati.size(), 0);
    tata[sursa] = -1;

    vizitat.clear();
    vizitat.resize(capacitati.size(), 0);   // marcam toate nodurile ca fiind nevizitate

    vizitat[sursa] = 1;     // marcam nodul sursa ca fiind vizitat

    while(!tata[destinatie] && !coada.empty())
    {
        a = coada.front();
        coada.pop();

        for(int i : rezidual[a])    // cautam prin nodurile adiacente nodului curent din graful rezidual
            if(capacitati[a][i] > flux[a][i] && !vizitat[i])    // daca unul din ele nu este vizitat, iar capacitatea este mai mare decat fluxul, continuam parcurgerea
        {
            tata[i] = a;
            vizitat[i] = 1;
            coada.push(i);
        }

    }
    return tata[destinatie];

}

int Graf :: max_flow(vector <vector <pair <int, int>>> lista_adiacenta, int sursa, int destinatie, int capacitate_maxima)
{
    int maxim = 0, flux_drum, a;
    vector <int> vizitat(numar_noduri + 1, 0);
    vector <int> tata(numar_noduri + 1, 0);     // cu ajutorul acestui vector, traversam calea gasita de algoritmul BFS pentru a putea gasi flux
    vector <vector <int>> rezidual(numar_noduri + 1);   // lista de adiacenta pentru graful rezidual
    vector <vector <int>> capacitati(numar_noduri + 1, vector <int>(numar_noduri + 1, 0));  // capacitate reziduala (va fi 0 acolo unde nu vor exista muchii)
    vector <vector <int>> flux(numar_noduri + 1, vector <int>(numar_noduri + 1, 0));    // aici retinem fluxul

    for(int i = 0; i < numar_noduri + 1; i++)       // parcurgem listele de adiacenta ale nodurilor date
        for(int j = 0; j < lista_adiacenta[i].size(); j++)
    {
        capacitati[i][lista_adiacenta[i][j].first] = lista_adiacenta[i][j].second;
        rezidual[i].push_back(lista_adiacenta[i][j].first);     // construim listele de adiacenta pentru graful rezidual care va fi identic cu cel initial
        rezidual[lista_adiacenta[i][j].first].push_back(i);     // pentru ca inca nu exista flux initial
    }

    // cat timp gasim un drum intre nodul sursa si nodul destinatie care are capacitatea necesara pentru flux
    while(bfs_maxflow(sursa, destinatie, capacitati, tata, flux, vizitat, rezidual))
    {
        // daca gasim un drum intre nodul sursa si nodul destinatie
        for(int i : rezidual[destinatie])
            if(flux[i][destinatie] < capacitati[i][destinatie] && vizitat[i])
        {
            flux_drum = capacitate_maxima;
            tata[destinatie] = i;

            // parcurgem drumul de la nodul destinatie la nodul sursa
            for(int j = destinatie; j != sursa; j = tata[j])
            {
                a = tata[j];

                if(flux_drum > capacitati[a][j] - flux[a][j])
                    flux_drum = capacitati[a][j] - flux[a][j];
            }
            if(flux_drum)
            {
                for(int j = destinatie; j != sursa; j = tata[j])    // actualizam fluxul de-a lungul caii gasite
            {
                a = tata[j];
                flux[a][j] += flux_drum;
                flux[j][a] -= flux_drum;
            }

            maxim += flux_drum; // adaugam fluxul gasit la fluxul maxim
            }

        }
    }

    return maxim;
}

/// functiile folosite pentru problema "Ciclu hamiltonian de cost minim"
void Graf :: hamilton_initializare()
{
    int capat_stang, capat_drept, cost;
    vector <vector <pair<int, int>>> lista;

    fin >> numar_noduri >> numar_muchii;

    lista.resize(numar_noduri + 2);

    for(int i = 0; i < numar_muchii; i++)
    {
        fin >> capat_stang >> capat_drept >> cost;
        lista[capat_stang].push_back(make_pair(capat_drept, cost));
    }

    cost = hamilton(lista);
    if(cost == INF)
        fout << "Nu exista solutie";
    else
        fout << cost;

    lista.clear();
}

int Graf :: hamilton(vector <vector <pair <int, int>>> lista)
{
    int x = 1 << numar_noduri, cost_final = INF; // x = 2^numar_noduri
    int costuri[x][numar_noduri];

    for(int i = 0; i < x; i++)
        for(int j = 0; j < numar_noduri; j++)
            costuri[i][j] = INF;

    costuri[1][0] = 0;

    for(int i = 0; i < x; i++)
        for(int j = 0; j  < numar_noduri; j++)
            if((1 << j) & i)
                for(int k = 0; k  < lista[j].size(); k++)
                    if((1 << lista[j][k].first) & i)
                        costuri[i][j] = min(costuri[i][j], costuri[i ^ (1 << j)][lista[j][k].first] + lista[j][k].second);

    for(int i = 0; i < lista[0].size(); i++)
        cost_final = min(cost_final, costuri[x - 1][lista[0][i].first] + lista[0][i].second);

    return cost_final;
}

/// functiile folosite pentru problema "Cuplaj maxim in graf bipartit"
void Graf :: cuplaj_maxim_initializare()
{
    int cardinal_multime_1, cardinal_multime_2, capat_stang, capat_drept;

    fin >> cardinal_multime_1 >> cardinal_multime_2 >> numar_muchii;

    vector <int> vizitat;   // vector de vizite
    vector <pair<int, int>> cuplaj_maxim;   // stocam rezultatul
    int v1[cardinal_multime_1 + 1] = {}, v2[cardinal_multime_2 + 1] = {}, ok = 1;

    for(int i = 0; i < cardinal_multime_1 + 1; i++)     // initializam vectorul de vizite cu 0
        vizitat.push_back(0);

    citire_graf_orientat(cardinal_multime_1, numar_muchii);

    while(ok)   // cat timp gasim un drum
    {
        ok = 0;

        for(int i = 0; i < vizitat.size(); i++)     // initializam vectorul de vizite cu valoarea 0
            vizitat[i] = 0;

        for(int i = 1; i <= cardinal_multime_1; i++)
            if(!v1[i])  // cautam un nod liber
                if(dfs_cuplaj_maxim(i, vizitat, v1, v2) == 1) // daca gasim un drum, vom continua cautarea
                    ok = 1;
    }

    for(int i = 1; i <= cardinal_multime_1; i++)
        if(v1[i])
            cuplaj_maxim.push_back(make_pair(i, v1[i]));

    fout << cuplaj_maxim.size() << '\n';

    for(int i = 0; i < cuplaj_maxim.size(); i++)
        fout << cuplaj_maxim[i].first << " " << cuplaj_maxim[i].second << '\n';

    lista_adiacenta.clear();
}

int Graf :: dfs_cuplaj_maxim(int x, vector <int> &vizitat, int v1[], int v2[])
{
    if(vizitat[x])
        return 0;

    vizitat[x] = 1;

    vector <int> :: iterator j;

    for(j = lista_adiacenta[x].begin(); j < lista_adiacenta[x].end(); j++)
        if(!v2[*j])
    {
        v1[x] = *j;
        v2[*j] = x;
        return 1;
    }

    for(j = lista_adiacenta[x].begin(); j < lista_adiacenta[x].end(); j++)
        if(dfs_cuplaj_maxim(v2[*j], vizitat, v1, v2))
    {
        v2[*j] = x;
        v1[x] = *j;
        return 1;
    }
    return 0;
}

/// functia folosita pentru problema "Ciclu Eulerian"
void Graf :: ciclu_eulerian()
{
    int capat_stang, capat_drept, ok = 1;

    fin >> numar_noduri >> numar_muchii;

    citire_graf_neorientat(numar_noduri, numar_muchii);

    // pentru a ne asigura intai de toate ca exista un ciclu eulerian, verificam daca toate nodurile au gradul impar sau pozitiv
    for(int i = 1; i <= numar_noduri; i++)
        if(lista_adiacenta[i].size() % 2 || !lista_adiacenta[i].size())
    {
        ok = 0;
        fout << "-1 \n";    // daca exista un nod care nu respecta conditiile enuntate mai sus, inseamna ca nu putem avea un ciclu eulerian
        return;
    }

    if(ok)
    {
        int nod, x;
        stack <int> noduri;     // stiva in care stocam nodurile pe care le parcurgem
        vector <int> euler;     // vector in care stocam rezultatul

        noduri.push(1);     // incepem de la nodul 1

        while(!noduri.empty())  // cat timp exista noduri in stiva
        {
            nod = noduri.top();     // luam primul nod

            if(lista_adiacenta[nod].size())     // daca exista noduri adiacente cu nodul curent
            {
                x = lista_adiacenta[nod].back();    // se stocheaza un vecin in x
                noduri.push(x);                     // se adauga in ciclul curent
                lista_adiacenta[nod].pop_back();    // stergem nodul din lista de adiacenta, ceea ce inseamna ca stergem muchia

                int i;
                for(i = 0; i < lista_adiacenta[x].size(); i++)
                    if(lista_adiacenta[x][i] == nod)
                        break;
                lista_adiacenta[x].erase(lista_adiacenta[x].begin() + i);

        }
        else
        {
            euler.push_back(nod);   // daca nu exista noduri adiacente cu nodul curent, stocam rezultatul in vectorul euler
            noduri.pop();
        }
    }

        for(int i = 0; i < euler.size() - 1; i++)   // afisam rezultatul
            fout << euler[i] << " ";
    }

    lista_adiacenta.clear();

}

int main()
{
    Graf x;
    fout << "Output pentru problema \"BFS\": ";
    x.bfs_initializare();

    fout << "\nOutput-ul pentru problema \"DFS\": ";
    x.dfs_initializare();

    fout << "\nOutputul pentru problema \"Componente tare conexe\" este:\n";
    x.ctc_initializare();

    fout << "Output-ul pentru \"Havel-Hakimi\": ";
    x.havel_hakimi();

    fout << "\nOutput-ul pentru problema \"Sortare topologica\" este: ";
    x.sortare_topologica_initializare();

    fout << "\nOutput-ul pentru problema \"Componente biconexe\" este:\n";
    x.biconex_initializare();

    fout << "Output-ul pentru problema \"Critical Connections in a Network\": ";
    x.critical_connections_initializare();

    fout << "Output-ul pentru problema \"Arbore partial de cost minim\" este:\n";
    x.apm_initializare();

    fout << "Output-ul pentru problema \"Paduri de multimi disjuncte\" este:\n";
    x.disjoint();

    fout << "Output-ul pentru problema \"Algoritmul lui Dijkstra\" este: ";
    x.dijkstra1();

    fout << "\nOutput-ul pentru problema \"Algoritmul Bellman-Ford\" este: ";
    x.bellman_ford1();

    fout << "\nOutput-ul pentru problema \"Diametrul unui arbore\" este: ";
    x.darb_initializare();

    fout << "\nOutput-ul pentru problema \"Floyd-Washall/Roy-Floyd\" este:\n";
    x.roy_floyd_initializare();

    fout << "Output-ul pentru problema \"Flux maxim\" este: ";
    x.flux_maxim_initializare();

    fout << "\nOutput-ul pentru problema \"Ciclu hamiltonian de cost minim\" este: ";
    x.hamilton_initializare();

    fout << "\nOutput-ul pentru problema \"Cuplaj maxim in graf bipartit\" este:\n";
    x.cuplaj_maxim_initializare();

    fout << "Output-ul pentru problema \"Ciclu Eulerian\" este: ";
    x.ciclu_eulerian();

    fin.close();
    fout.close();

    return 0;
}
