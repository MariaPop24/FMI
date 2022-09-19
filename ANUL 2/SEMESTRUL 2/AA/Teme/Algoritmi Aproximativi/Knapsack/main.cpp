#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("knapsack.in");
ofstream fout("knapsack.out");

int n, k;
vector <int> numere;

/// functia pentru punctul a
void suma_a()
{
    int suma = 0;
    vector <int> x;
    x.push_back(0);

    for(auto a : numere)
        for(auto b : x)
            if(a + b <= k)
            {
                if(suma < a + b)
                    suma = a + b;
                x.push_back(a+b);
            }
    fout << suma;
}

/// functia pentru punctul b
void suma_b()
{
    int numar, suma = 0;

    while(fin >> numar)
    {
        if(suma + numar <= k)
            suma += numar;
        else if(suma < numar)
            suma = numar;
    }

    fout << suma;
}

int main()
{
    fin >> n >> k;

    numere.resize(n + 1);

    for(int i = 0; i < n; i++)
        fin >> numere[i];

    fout << "Output-ul pentru punctul a: ";
    suma_a();

    fout << "\nOutput-ul pentru punctul b: ";
    suma_b();

    fin.close();
    fout.close();

    return 0;
}
