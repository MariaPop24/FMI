-- 6. Sa se scrie urmatoarele functii:
-- a) Functie cu 2 parametri care calculeaza suma patratelor celor 2 numere

suma_patratelor :: Integer -> Integer -> Integer
suma_patratelor a b = a * a + b * b

-- b) functie cu un parametru ce intoarce mesajul "par" daca parametrul este par si "impar" altfel

paritate :: Integer -> [Char]
paritate a = if(mod a 2 == 0) then "par" else "impar"

-- c) functie care calculeaza factorialul unui numar

factorial :: Integer -> Integer
factorial a = if(a == 1) then 1 else a * factorial(a - 1)

-- d) functie care verifica daca primul parametru este mai mare decat dublul celui de-al doilea parametru

verificare :: Integer -> Integer -> [Char]
verificare a b = if(a > b * 2) then "Da" else "Nu"
