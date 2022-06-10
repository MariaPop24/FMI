import copy
import math
import random


def fittest(d):
    index = 0
    maxim = functie(valoare_cromozom(d[0]))

    for j in range(len(d)):
        s1 = functie(valoare_cromozom(d[j]))
        if s1 > maxim:
            index = j
            maxim = s1
    return index


def least_fit(d):
    index = 0
    minim = functie(valoare_cromozom(d[0]))

    for j in range(len(d)):
        s1 = functie(valoare_cromozom(d[j]))
        if minim > s1:
            index = j
            minim = s1

    return index


def criteriu_elitist():
    fittest1 = fittest(populatie)
    least_fit1 = least_fit(populatie_noua)

    populatie_noua[least_fit1] = copy.copy(populatie[fittest1])
    return


def mutatie():
    if i == 1:
        fout.write("\n\n\nProbabilitatea de mutatie " + str(probabilitate_mutatie) + ":\nAu fost modificati cromozomii:")

    for j in range(dimensiune_populatie - 1):
        u = random.random()
        if u < probabilitate_mutatie:
            if i == 1:
                fout.write(str(j + 1) + " ")
            p = random.randrange(0, lungime_cromozom - 1)
            populatie_noua[j][p] = abs(populatie_noua[p][j] - 1)

    if i == 1:
        fout.write("\n")

    return


def incrucisare(k):
    e = []
    f = []
    while len(k) >= 2:
        x = random.sample(k, 2) # alegem 2 candidati la intamplare
        k.remove(x[0])  # pe care ii scoatem din lista de candidati
        k.remove(x[1])

        # alegem un punct de rupere random
        punct_rupere = random.randrange(0, lungime_cromozom)
        if i == 1:
            fout.write("Recombinare dintre cromozomul " + str(x[0] + 1) + " cu cromozomul " + str(x[1] + 1) + "\n")
            fout.write("".join(map(str, populatie_noua[x[0]])) + " " + "".join(map(str, populatie_noua[x[1]])) + " punct " + str(punct_rupere) + "\n")

        e = populatie_noua[x[0]][:punct_rupere] + populatie_noua[x[1]][punct_rupere:]
        f = populatie_noua[x[1]][:punct_rupere] + populatie_noua[x[0]][punct_rupere:]

        if i == 1:
            fout.write("Rezultat: " + "".join(map(str, e)) + " " + "".join(map(str, f)) + "\n\n")

        populatie_noua[x[0]] = e
        populatie_noua[x[1]] = f


def candidati_incrucisare():

    t = []  # lista ce retine lista de cromozomi care vor fi recombinati

    for j in range(1, dimensiune_populatie + 1):
        sansa = random.random() # alegem un numar random intre 0 si 1
        text = str(j) + ": " + "".join(map(str, populatie_noua[j-1])) + ", u=" + str(sansa)

        # daca sansa < probabilitatea de recombinare, il adaugam in lista de cromozomi ce vor fi recombinati
        if sansa < probabilitate_recombinare:
            t.append(j-1)
            text += "<" + str(probabilitate_recombinare) + " participa"

        if i == 1:
            fout.write(text + "\n")

    fout.write("\n")
    return t


def metoda_ruletei():
    p = []

    # selectam n indivizi
    for j in range(1, dimensiune_populatie + 1):
        u = random.random() # alegem 2 numere random intre 0 si 1
        v = random.random()
        e = 1
        f = 1

        # cautam intervalele in care se incadreaza
        while intervale_ps[e - 1] > u or u > intervale_ps[e]:
            e += 1

        while intervale_ps[f - 1] > v or v > intervale_ps[f]:
            f += 1

        # adaug cromozomul asociat intervalului in populatia noua
        if functie(valoare_cromozom(populatie[e - 1])) > functie(valoare_cromozom(populatie[f - 1])):
            if i == 1:
                fout.write("u=" + str(u) + " selectam cromozomul " + str(e) + "\n")
            p.append(copy.deepcopy(populatie[e - 1]))
        else:
            if i == 1:
                fout.write("v=" + str(v) + " selectam cromozomul " + str(f) + "\n")
            p.append(copy.deepcopy(populatie[f - 1]))

    return p


def intervale_selectie(x):

    t = []  # retinem capetele intervalele capetelor de selectie
    interval = 0    # ne ajuta sa calculam intervalele

    # calculam intervalele
    for y in x:
        t.append(interval)
        interval += y
    t.append(1.0)

    # le afisam
    if i == 1:
        fout.write("\n\nIntervale probabilitati selectie:\n")
        for y in t:
            fout.write(str(y) + " ")
        fout.write("\n\n")

    # returnam capetele intervalelor de selectie
    return t


# calculam probabilitatea de selectie
def probabilitate_selectie():
    # calculam f(X) pentru fiecare individ
    valori = [functie(valoare_cromozom(y)) for y in populatie]
    # facem suma de f(Xi), performanta totala a populatiei
    suma = sum(valori)

    t = []  # aici retinem probabilitatea de selectie pentru fiecare individ
    for y in valori:
        t.append(y / suma) # calculam conform formulei

    # afisam pentru fiecare cromozom probabilitatea de selectie
    if i == 1:
        fout.write("Probabilitati selectie: \n")
        for j in range(1, dimensiune_populatie + 1):
            fout.write("Cromozom " + str(j) + " -> probabilitate: " + str(t[j-1]) + "\n")

    return t


# functia pentru calcularea lui f(x), functia din input
def functie(x):
    return coeficient_a * x * x + coeficient_b * x + coeficient_c


# calculam valoarea unui cromozom, transformandu-l din baza 2 in baza 10
# aflam valoarea codificata din D=[a, b] - translatie liniara
def valoare_cromozom(p):

    x = 0
    for b in p:
        x = (x << 1) | b

    # valoarea corespunzătoare cromozomului în domeniul de definiţie al funcţiei
    return (domeniu_definitie2 - domeniu_definitie1) / (2 ** lungime_cromozom - 1) * x + domeniu_definitie1


# generam cromozomii din populatia initiala
def generare_populatie_initiala():

    global populatie
    # generam populatie sub forma de matrice in care un element al matricei este un cromozom, adica o lista de gene
    populatie = [[random.randint(0, 1) for g in range(lungime_cromozom)] for b in range(dimensiune_populatie)]

    # afisarea fiecarui cromozom din populatia initiala
    for g in range(1, len(populatie) + 1):
        fout.write(str(g) + ": ")
        fout.write("".join(map(str, populatie[g-1])) + ", x= ")
        valoare1 = round(valoare_cromozom(populatie[g-1]), precizie)
        fout.write(str(valoare1) + ", ")
        fout.write(str(functie(valoare1)) + "\n")


# de aici incepe executia programului
try:
    # deschidem fisierele si citim date din cel de intrare
    fin = open("input.txt")
    fout = open("Evolutie.txt", "w")
    s = fin.read().split()

    # atribuim fiecare date de intrare cate o variabila
    dimensiune_populatie = int(s[0])
    domeniu_definitie1 = int(s[1])
    domeniu_definitie2 = int(s[2])
    coeficient_a = int(s[3])
    coeficient_b = int(s[4])
    coeficient_c = int(s[5])
    precizie = int(s[6])
    probabilitate_recombinare = float(s[7])
    probabilitate_mutatie = float(s[8])
    numar_etape = int(s[9])

    # discretizarea intervalului => (b - a) * 10 ^ p subintervale (elemente)
    # lungimea cromozomului = [log2((b-a)*10^p)]
    lungime_cromozom = math.floor(math.log((domeniu_definitie2 - domeniu_definitie1) * 10 ** precizie, 2))

    # afisam populatia initiala
    fout.write("Populatia initiala: \n")
    generare_populatie_initiala()

    for i in range(numar_etape):

        # calculam probabilitatea de selectie
        probabilitate_s = probabilitate_selectie()

        # calculam intervalele de selectie
        intervale_ps = intervale_selectie(probabilitate_s)

        # aplicam metoda ruletei
        populatie_noua = metoda_ruletei()

        # afisam noua populatie
        if i == 1:
            fout.write("\nDupa selectie: \n")
            for a in range(1, len(populatie_noua) + 1):
                fout.write(str(a) + ": ")
                fout.write("".join(map(str, populatie_noua[a - 1])) + ", x= ")
                valoare = round(valoare_cromozom(populatie_noua[a - 1]), 6)
                fout.write(str(valoare) + ", ")
                fout.write(str(functie(valoare)) + "\n")
            fout.write("\n")

        # selectam pentru incrucisare
        candidati = candidati_incrucisare()

        # realizam incrucisarea
        incrucisare(candidati)

        if i == 1:
            fout.write("\nDupa recombinare:\n")
            for a in range(1, len(populatie_noua) + 1):
                fout.write(str(a) + ": ")
                fout.write("".join(map(str, populatie_noua[a - 1])) + ", x= ")
                valoare = round(valoare_cromozom(populatie_noua[a - 1]), precizie)
                fout.write(str(valoare) + ", ")
                fout.write(str(functie(valoare)) + "\n")

        mutatie()
        if i == 1:
            fout.write("\nDupa mutatie:\n")
            for t1 in range(1, len(populatie_noua) + 1):
                fout.write(str(t1) + ": ")
                fout.write("".join(map(str, populatie_noua[t1 - 1])) + ", x= ")
                valoare = round(valoare_cromozom(populatie_noua[t1 - 1]), 6)
                fout.write(str(valoare) + ", ")
                fout.write(str(functie(valoare)) + "\n")
            fout.write("\n")

        # aplicam criteriul elitist
        # inlocuim cel mai bun cromozom din populatia initiala cu cel mai prost cromozom din populatia noua
        criteriu_elitist()

        # afisam populatia dupa aplicarea criteriului elitist
        if i == 1:
            fout.write("Dupa aplicarea criteriului elitist:\n")
            for t1 in range(1, len(populatie_noua) + 1):
                fout.write(str(t1) + ": ")
                fout.write("".join(map(str, populatie_noua[t1 - 1])) + ", x= ")
                valoare = round(valoare_cromozom(populatie_noua[t1 - 1]), 6)
                fout.write(str(valoare) + ", ")
                fout.write(str(functie(valoare)) + "\n")
            fout.write("\n")

        # aplicam pe populatia noua functia care da indicele maximului
        # luam elementul din lista, il transformam in baza 10 si apoi aplicam functia de fitness pe el
        if i == 1:
            fout.write("Evolutia maximului:\n")

        fout.write(str(valoare_cromozom(populatie_noua[fittest(populatie_noua)])) + " " + str(functie(valoare_cromozom(populatie_noua[fittest(populatie_noua)]))))

        populatie = copy.deepcopy(populatie_noua)

    fin.close()
    fout.close()
except FileNotFoundError:
    print("Fisier inexistent!")
