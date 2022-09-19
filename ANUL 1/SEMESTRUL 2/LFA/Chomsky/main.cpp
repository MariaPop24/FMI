/// date de intrare

/*
S XSX
S aY
X Y
X S
Y b
Y #
*/

/// date de iesire

/*
S -> SX XS a AX BY
X ->  b BY SX XS a AX
Y -> b
A -> XS
B -> a
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int numar, lambda[100];
string st, dr, c;
map<string, int> m, cuvant[100];
map<string, string> map1;
vector<string> CFG[100], v;

ifstream fin("Chomsky.in");
ofstream fout("Chomsky.out");

void pasul_1()
{
    for(int i = 1; i <= numar; i++)
        if(CFG[i][0][0] == '#' && CFG[i].size() == 1)
            lambda[i] = 2;

    for(int i = 1; i <= numar; i++)
        for(int j = 0; j < CFG[i].size(); j++)
            if(CFG[i][j].size() == 1 && lambda[m[CFG[i][j]]] != 0)
                    lambda[m[v[i]]] = lambda[m[CFG[i][j]]];

    for(int i = 1; i <= numar; i++)
    {
        for(int j = 0; j < CFG[i].size(); j++)
        {
            for(int k = 0; k < CFG[i][j].size(); k++)
            {
                string a;
                a += CFG[i][j][k];
                if(lambda[m[a]] == 1)
                {
                    string b;
                    b += CFG[i][j];
                    b.erase(b.begin() + k, b.begin() + k + 1);

                    if(cuvant[i][b] != 1)
                    {
                        CFG[i].push_back(b);
                        cuvant[i][b] = 1;
                    }
                }
                else if(lambda[m[a]] == 2)
                {
                    cuvant[i][CFG[i][j]] = 0;
                    CFG[i][j].erase(CFG[i][j].begin() + k, CFG[i][j].begin() + k + 1);
                    k--;
                }
            }
        }
    }

    for(int i = 1; i <= numar; i++)
        if(lambda[i] == 1)
            for(int j = 0; j < CFG[i].size(); j++)
                if(CFG[i][j].size() == 1 && CFG[i][j].find('_') != string::npos)
                {
                    CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                    j--;
                }
        else if(lambda[i] == 2)
        {
            CFG[i].clear();
            m[v[i]] = 0;
        }
}

void pasul_2()
{
    for(int i = 1; i <= numar; i++)
        for(int j = 0; j < CFG[i].size(); j++)
            if(CFG[i][j] == v[i])
            {
                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                j--;
            }
            else
            if(CFG[i][j].size() == 1 && CFG[i][j][0] == toupper(CFG[i][j][0]))
            {
                int index = m[CFG[i][j]];
                for(int k = 0; k < CFG[index].size(); k++)
                    if(cuvant[i][CFG[index][k]] == 0)
                    {
                        CFG[i].push_back(CFG[index][k]);
                        cuvant[i][CFG[index][k]] = 1;
                    }

                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                j--;
            }
}

void pasul_3()
{
    c += 'A';

    for(int i = 1; i <= numar; i++)
        for(int j = 0; j < CFG[i].size(); j++)
            if(CFG[i][j].size() > 2)
            {
                string a, b;

                b += CFG[i][j][0];
                b += CFG[i][j][1];

                if(map1[b].size())
                    a += map1[b] + &CFG[i][j][2];
                else
                {
                    a += c + &CFG[i][j][2];
                    numar++;
                    CFG[numar].push_back(b);
                    v.push_back(c);
                    cuvant[numar][b] = 1;
                    map1[b] = c;
                    c[0]++;
                }

                cuvant[i][a] = 1;
                cuvant[i][CFG[i][j]] = 0;
                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                CFG[i].push_back(a);

            }
}

void pasul_4()
{

    for(int i = 1; i <= numar; i++)
        for(int j = 0; j < CFG[i].size(); j++)
            if(CFG[i][j].size() == 2)
                for(int k = 0; k < 2; k++)
                    if(CFG[i][j][k] == tolower(CFG[i][j][k]))
                    {
                        string b;
                        b += CFG[i][j][k];

                        if(map1[b].size())
                            CFG[i][j][k] = map1[b][0];
                        else
                            {
                                map1[b] = c;
                                numar++;
                                CFG[numar].push_back(b);
                                v.push_back(c);
                                m[c] = numar;
                                cuvant[numar][b] = 1;

                                string t;

                                if(k)
                                    t += CFG[i][j][0] + v[m[c]];
                                else
                                    t += v[m[c]] + CFG[i][j][k + 1];

                                c[0]++;

                                CFG[i].push_back(t);
                                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                                j--;
                                break;
                            }
                    }

    for(int i = 1; i <= numar; i++)
    {
        if(CFG[i].size())
        {
            fout << v[i] << " -> ";
            for(int j = 0; j < CFG[i].size(); j++)
                fout << CFG[i][j] << " ";
            fout << '\n';
        }
    }
}

int main()
{
    fin >> st >> dr;
    v.push_back(st);

    while(!fin.eof())
    {
        if(m[st])
        {
            CFG[m[st]].push_back(dr);
            cuvant[m[st]][dr] = 1;
        }
        else
        {
            m[st] = ++numar;
            v.push_back(st);
            CFG[numar].push_back(dr);
            cuvant[numar][dr] = 1;
        }

        if(!dr.find('#'))
            lambda[m[st]] = 1;

        fin >> st >> dr;
    }

    pasul_1();
    pasul_2();
    pasul_3();
    pasul_4();

    return 0;
}
