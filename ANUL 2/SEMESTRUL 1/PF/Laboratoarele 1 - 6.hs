import System.Win32 (COORD(xPos))
import Data.Char 
import Data.List
-- LABORATORUL 1

-- 6. a)
suma :: Integer -> Integer -> Integer 
suma x y = x * x + y * y 

-- 6. b)
par :: Integer -> String 
par x = if (x `mod` 2 == 0) then "par" else "impar"

-- 6. c)
fact :: Integer -> Integer 
fact x
    | x <= 0 = 1
    | otherwise = x * fact (x - 1)

-- 6. d)
dublu :: Integer -> Integer -> String 
dublu x y = if (x > 2 * y) then "da" else "nu"

-- LABORATORUL 2

-- 1.
poly2 :: Double -> Double -> Double -> Double -> Double 
poly2 a b c x = a * x * x + b * x + c

-- 2.
eeny :: Integer -> String 
eeny x = if (even x) then "eeny" else "meeny"

-- 3.
-- varianta cu if
fizzbuzz :: Integer -> String 
fizzbuzz x = if (x `mod` 3 == 0 && x `mod` 5 /= 0) then "Fizz" 
            else if (x `mod` 3 /= 0 && x `mod` 5 == 0) then "Buzz" 
            else if (x `mod` 3 == 0 && x `mod` 5 == 0) then "FizzBuzz" 
            else ""

--varianta cu garzi
fizzbuzz1 :: Integer -> String 
fizzbuzz1 x 
    | x `mod` 3 == 0 && x `mod` 5 /= 0 = "Fizz"
    | x `mod` 3 /= 0 && x `mod` 5 == 0 = "Buzz"
    | x `mod` 3 == 0 && x `mod` 5 == 0 = "FizzBuzz"
    | otherwise = ""

-- 4.
-- varianta cu cazuri
tribonacci :: Integer -> Integer 
tribonacci x 
    | x == 1 = 1
    | x == 2 = 1
    | x == 3 = 2
    | otherwise = tribonacci (x - 1) + tribonacci (x - 2) + tribonacci (x - 3)

-- varianta ecuationala
tribonacci1 :: Integer -> Integer 
tribonacci1 1 = 1
tribonacci1 2 = 1
tribonacci1 3 = 2
tribonacci1 n = tribonacci1 (n - 1) + tribonacci1 (n - 2) + tribonacci1 (n - 3)

-- 5.
binomial :: Integer -> Integer -> Integer 
binomial _ 0 = 1
binomial 0 _ = 0
binomial n k = binomial (n - 1) k + binomial (n - 1) (k - 1)

-- 6. a)
verifL :: [Int] -> Bool 
verifL x
    | length x `mod` 2 == 0 = True 
    | otherwise = False 

-- 6. b)
takefinal :: [Int] -> Int -> [Int]
takefinal xs n 
    | length xs < n = xs 
    | otherwise = reverse (take n (reverse xs))

-- 6. c)
remove :: [Int] -> Int -> [Int]
remove xs n = take (n - 1) xs ++ drop n xs

semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
    | even h = h `div` 2 : semiPareRec t  
    | otherwise = semiPareRec t   

semiPareRec1 :: [Int] -> [Int]
semiPareRec1 [] = []
semiPareRec1 (x:xs) 
    | even x = x `div` 2 : t1 
    | otherwise = t1 
    where t1 = semiPareRec1 xs

-- 7. a)
myreplicate :: Integer -> Integer -> [Integer]
myreplicate n v
    | n == 0 = []
    | otherwise = [v] ++ myreplicate (n - 1) v 

-- 7. b)
sumImp :: [Integer] -> Integer 
sumImp xs
    | xs == [] = 0
    | head xs `mod` 2 /= 0 = head xs + sumImp (tail xs) 
    | otherwise = sumImp (tail xs)

sumImp1 :: [Integer] -> Integer
sumImp1 [] = 0
sumImp1 (x:xs)
    | x `mod` 2 /= 0 = x + sumImp (tail xs) 
    | otherwise = sumImp xs

-- 7. c)
totalLen :: [String] -> Int 
totalLen xs 
    | xs == [] = 0
    | head (head xs) == 'A' = length (head xs) + totalLen (tail xs)
    | otherwise = totalLen (tail xs)

totalLen1 :: [String] -> Int 
totalLen1 [] = 0
totalLen1 (x:xs)
    | head x == 'A' = length x + totalLen1 xs
    | otherwise = totalLen1 xs

-- LABORATORUL 3

-- 1. 
vocale :: String -> Int
vocale "" = 0
vocale xs
    | elem (head xs) "aeiouAEIOU" = 1 + vocale (tail xs)
    | otherwise = vocale (tail xs)

nrVocale :: [String] -> Int 
nrVocale [] = 0
nrVocale (x:xs)
    | reverse x == x = vocale x + nrVocale xs 
    | otherwise = nrVocale xs 

-- 2.
f :: Integer -> [Integer] -> [Integer]
f n xs 
    | null xs = []
    | head xs `mod` 2 == 0 = [head xs] ++ [n] ++ f n (tail xs)
    | otherwise = [head xs] ++ f n (tail xs)

semiPareComp :: [Int] -> [Int]
semiPareComp l = [x `div` 2 | x <- l, even x]

-- 3.
divizori :: Integral a => a -> [a]
divizori x = [y | y <- [1..x], x `mod` y == 0]

-- 4.
listadiv :: [Int] -> [[Int]]
listadiv xs = [divizori x | x <- xs]


-- 5. a)
inIntervalRec :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalRec a b xs 
    | null xs = []
    | head xs >= a && head xs <= b = [head xs] ++ inIntervalRec a b (tail xs)
    | otherwise = inIntervalRec a b (tail xs)

-- 5. b)
inIntervalComp :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalComp a b xs = [x | x <- xs, x >= a && x <= b]

-- 6. a)
pozitiveRec :: [Integer] -> Integer 
pozitiveRec xs 
    | null xs = 0
    | head xs > 0 = 1 + pozitiveRec (tail xs)
    | otherwise = pozitiveRec (tail xs)

-- 6. b)
pozitiveComp :: [Integer] -> Int
pozitiveComp xs = length ([x | x <- xs, x > 0])

-- 7. a)
pozitiiImpareRec1 :: [Integer] -> Integer -> [Integer]
pozitiiImpareRec1 xs n
    | null xs = []
    | head xs `mod` 2 /= 0 = [n] ++ pozitiiImpareRec1 (tail xs) (n + 1)
    | otherwise = pozitiiImpareRec1 (tail xs) (n + 1)

pozitiiImpareRec :: [Integer] -> [Integer] 
pozitiiImpareRec xs = pozitiiImpareRec1 xs 0

-- 7. b)
pozitiiImpareComp :: [Integer] -> [Integer]
pozitiiImpareComp xs = [snd a | a <- zip xs [0..], odd (fst a)]

-- 8. a)
multDigitsRec :: String -> Int
multDigitsRec xs 
    | null xs = 1
    | isDigit (head xs) = digitToInt (head xs) * multDigitsRec (tail xs)
    | otherwise = multDigitsRec (tail xs)

-- 8. b)
multDigitsComp :: String -> Int 
multDigitsComp xs = product [digitToInt x | x <- xs, isDigit x]

-- LABORATORUL 4

-- 1.
factori :: Int -> [Int]
factori n = [x | x <- [1..n], n `mod` x == 0]

-- 2.
prim :: Int -> Bool 
prim n 
    | length (factori n) == 2 = True 
    | otherwise = False 

-- 3.
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x]

-- 4.
myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 a b c
    | (null a) || (null b) || (null c) = []
    | otherwise = [(head a, head b, head c)] ++ myzip3 (tail a) (tail b) (tail c)

myzip31 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip31 a b c = [(x, y, z) | (x, (y, z)) <- zip a (zip b c)]

-- 5.
ordonataNat :: [Int] -> Bool 
ordonataNat [] = True 
ordonataNat [x] = True 
ordonataNat (x:xs) = and [x < head xs, ordonataNat(head xs : xs)]

-- 6.
ordonataNat1 :: [Int] -> Bool 
ordonataNat1 [] = True 
ordonataNat1 [x] = True 
ordonataNat1 (x:xs)
    | x <= head xs = ordonataNat1 (tail xs)
    | otherwise = False 

-- 7. a)
ordonata :: [a] -> (a -> a -> Bool) -> Bool 
ordonata [] ordine = True 
ordonata [x] ordine = True 
ordonata (x : y : xs) ordine = ordine x y && ordonata (y : xs) ordine

-- 8.
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool 
(a, b) *<* (c, d) = a <= c && b <= d 

-- 9.
compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList f ls = [f.g | g <- ls] 

-- 10.
aplicaList :: a -> [(a -> b)] -> [b]
aplicaList x f = [g x | g <- f]

-- LABORATORUL 5

-- 1.
firstEl :: [(a, b)] -> [a]
firstEl xs = map (\(x, y) -> x) xs

-- 2.
sumList :: [[Int]] -> [Int]
sumList xs = map sum xs

-- 3.
prel2 :: [Int] -> [Int]
prel2 xs = map (\x -> if (even x) then x `div` 2 else x * 2) xs 

-- 4.
f4 :: Char -> [String] -> [String]
f4 x xs = filter (\y -> elem x y) xs

-- 5.
f5 :: [Integer] -> [Integer]
f5 xs = map (\x -> x * x) (filter (odd) xs)

-- 6.
f6 :: [Integer] -> [Integer]
f6 xs = map (\x -> snd x * snd x) (filter (\x -> odd (fst x)) [x | x <- (zip [0..] xs)])

-- 7.
numaiVocale :: [String] -> [String]
numaiVocale xs = map (\x -> filter (\y -> elem y "aeiouAeiout") x) xs

-- 8.
mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f xs = f (head xs) : mymap f (tail xs)

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f xs 
    | f (head xs) = head xs : myfilter f (tail xs)
    | otherwise = myfilter f (tail xs)

-- 9.
f9 :: [Integer] -> Integer 
f9 xs = sum (map (\x -> x * x) (filter (odd) xs))

-- 10.
f10 :: [Bool] -> Bool  
f10 xs = foldr (&&) True xs

f101 :: [Bool] -> Bool 
f101 = foldr (&&) True 

-- 11. a)
rmChar :: Char -> String -> String 
rmChar x xs = filter (\z -> z /= x) [y | y <- xs]

-- 11. b)
rmCharsRec :: String -> String -> String 
rmCharsRec a b
    | null a || null b = b 
    | otherwise = rmCharsRec (tail a) (rmChar (head a) b)

-- 11. c)
rmCharsFold :: String -> String -> String 
rmCharsFold a b = foldr rmChar b a

-- LABORATORUL 6

-- 1.
rotate :: Int -> [Char] -> [Char]
rotate n xs 
    | n < 0 = "n este negativ"
    | n >= length xs = error "n este prea mare"
    | otherwise = drop n xs ++ take n xs

-- 2.
prop_rotate :: Int -> [Char] -> Bool
prop_rotate k str = rotate (l-m) (rotate m str) == str
                    where l = length str
                          m = if l == 0 then 0 else k `mod` l

-- 3.
makeKey :: Int -> [(Char, Char)]
makeKey x = zip ['A'..'Z'] (rotate x ['A'..'Z'])

-- 4.
lookUp :: Char -> [(Char, Char)] -> Char
lookUp c xs = foldr (\pc ch -> if (fst pc == c) then snd pc else ch) c xs

-- 5.
encipher :: Int -> Char -> Char 
encipher a b = lookUp b (makeKey a) 

encipher1 :: Int -> Char -> Char 
encipher1 a b 
    | chr (ord b + a) > 'Z' = chr (ord 'A' + a - ord 'Z' + ord b - 1)
    | otherwise = chr (ord b + a)

-- 6.
normalize :: String -> String 
normalize x = filter (\y -> elem y ['A'..'Z'] || isDigit y) (map (\y -> if (isAlpha y) then toUpper y else y) x)

-- 7.
encipherStr :: Int -> String -> String 
encipherStr a b = [encipher a x | x <- (normalize b)]

-- 8.
reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey x = [(snd y, fst y)| y <- x]

reverseKey1 :: [(Char, Char)] -> [(Char, Char)]
reverseKey1 = map (\(x, y) -> (y, x))

-- 9.
decipher :: Int -> Char -> Char 
decipher a b 
    | chr (ord b - a) < 'A' = chr (ord 'Z' - (a - (ord b - ord 'A') - 1))
    | otherwise = chr (ord b - a)

decipherStr :: Int -> String -> String 
decipherStr a b = map (\y -> if (isDigit y) then y else decipher a y) (normalize b)

-- LABORATORUL 7

-- 1.
data Fruct = Mar String Bool | Portocala String Int 

listaFructe :: [Fruct]
listaFructe = [Mar "Ionatan" False, 
                Portocala "Sanguinello" 10, 
                Portocala "Valencia" 22, 
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15, 
                Portocala "Moro" 12, 
                Portocala "Tarocco" 3, 
                Portocala "Moro" 12, 
                Portocala "Valencia" 2, 
                Mar "Golden Delicious" False,
                Mar "Golden" False, 
                Mar "Golden" True]


-- 1. a)
ePortocalaDeSicilia :: Fruct -> Bool 
ePortocalaDeSicilia (Mar _ _) = False 
ePortocalaDeSicilia (Portocala str _) = elem str ["Tarocco", "Moro", "Sanguinello"] 

test_ePortocalaDeSicilia1 :: Bool 
test_ePortocalaDeSicilia1 = ePortocalaDeSicilia (Portocala "Moro" 12) == True 
test_ePortocalaDeSicilia2 :: Bool 
test_ePortocalaDeSicilia2 = ePortocalaDeSicilia (Mar "Ionatan" True) == False

-- 1. b)
nrFeliiSicilia :: [Fruct] -> Int 
nrFeliiSicilia xs = sum [nrfelii | Portocala str nrfelii <- xs, ePortocalaDeSicilia (Portocala str nrfelii)]

test_nrFeliiSicilia :: Bool
test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52

-- 1. c)
nrMereViermi :: [Fruct] -> Int 
nrMereViermi xs = sum [1 | Mar str b <- xs, b]

test_nrMereViermi :: Bool
test_nrMereViermi = nrMereViermi listaFructe == 2

-- 2. a)
type NumeA = String 
type Rasa = String 
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show 

vorbeste :: Animal -> String 
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

-- 2. b)
rasa :: Animal -> Maybe String 
rasa (Pisica _) = Nothing 
rasa (Caine _ str) = Just str 

-- 3. a)
data Linie = L [Int]
    deriving Show 
data Matrice = M [Linie]
    deriving Show 

verifica :: Matrice -> Int -> Bool 
verifica (M m) n = foldr ((&&) . (\(L linie) -> sum linie  == n)) True m 

test_verif1 :: Bool
test_verif1 = verifica (M [L [1, 2, 3], L [4, 5], L [2, 3, 6, 8], L [8, 5, 3]]) 10 == False

test_verif2 :: Bool
test_verif2 = verifica (M [L [2, 20, 3], L [4, 21], L [2, 3, 6, 8, 6], L [8, 5, 3, 9]]) 25 == True

-- 3. b)
doarPozN :: Matrice -> Int -> Bool 
doarPozN (M m) n = foldr ((&&) . (\(L linie) -> product linie > 0)) True (filter (\(L linie) -> length linie == n) m)

testPoz1 :: Bool
testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True

testPoz2 :: Bool
testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False

-- 3. c)
corect :: Matrice -> Bool 
corect (M []) = True 
corect (M [x]) = True 
corect (M ( L l1 : (L l2) : ls)) = length l1 == length l2 && corect (M (L l2 : ls))

testcorect1 :: Bool
testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False

testcorect2 :: Bool
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True

-- LABORATORUL 8

type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

-- 1.
p1 :: Prop 
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :|: Var "Q")

p2 :: Prop 
p2 = (Var "P" :|: Var "Q") :&: (Not(Var "P") :&: Not(Var "Q"))

p3 :: Prop 
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not(Var "P") :|: Not(Var "Q") :&: (Not(Var "P") :|: Not(Var "R"))))

-- 2.
instance Show Prop where 
    show (Var p) = p 
    show F = "False"
    show T = "True"
    show (Not p) = "(~" ++ show p ++ ")"
    show (a :|: b) = "(" ++ show a ++ "|" ++ show b ++ ")"
    show (a :&: b) = "(" ++ show a ++ "&" ++ show b ++ ")"

test_ShowProp :: Bool 
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]
{-
lookup1 :: Eq a => a -> [(a, b)] -> Maybe b 

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust  lookup1 a
-}

-- 3.
eval :: Prop -> Env -> Bool
--eval (Var x) list = impureLookup x list
eval (Not (Var x)) list = not (eval (Var x) list)
eval (x :&: y) list = eval x list && eval y list
eval (x :|: y) list = eval x list || eval y list
eval T list = True
eval F list = False 

test_eval :: Bool
test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

-- 4.

variabile :: Prop -> [Nume]
variabile (Var p) = [p]
variabile (Not p)= nub $ variabile p
variabile (p :|: q)= nub $ variabile p ++ variabile q
variabile (p :&: q)= nub $ variabile p ++ variabile q
variabile _ = []
 
test_variabile :: Bool
test_variabile = variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

-- 5.
envs :: [Nume] -> [Env]
envs [] = []
envs [x] = [[(x, False)], [(x, True)]]
envs (hd : xs) = map (\x -> (hd, False) : x) (envs xs) ++ map (\x -> (hd, True) : x) (envs xs)
 
test_envs :: Bool
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

-- 6.
satisfiabila :: Prop -> Bool
satisfiabila p = or $ map (eval p) $ envs (variabile p)

test_satisfiabila1 :: Bool
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 :: Bool
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

-- 7.
valida :: Prop -> Bool
valida = undefined

test_valida1 :: Bool
test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 :: Bool
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

-- 10.
{-
echivalenta :: Prop -> Prop -> Bool
echivalenta p q= all (\env -> eval (p :<->: q) env) $ envs $ nub $ variabile p ++ variabile q

test_echivalenta1 :: Bool
test_echivalenta1 =
  True
  == (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))

test_echivalenta2 :: Bool
test_echivalenta2 = 
  False
  == (Var "P") `echivalenta` (Var "Q")

test_echivalenta3 :: Bool
test_echivalenta3 =
  True
  == (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))-}

-- LABORATORUL 9

-- 1. a)
sfChr :: Char -> Bool 
sfChr x = elem x ".?!:"

f91 :: String -> Integer 
f91 xs
    | null xs = 0
    | sfChr (head xs) = 1 + f91 (tail xs)
    | otherwise = f91 (tail xs)

-- 1. b)
f911 :: String -> Integer 
f911 xs = sum [1 | x <- xs, sfChr x]

-- 2.
liniiN :: [[Int]] -> Int -> Bool 
liniiN xs n = foldr ((&&) . (\l -> product l > 0)) True ([y | y <- xs, length y == n])

-- 3.
data Punct = Pt [Int]
    deriving Show 

data Arb = Vid | P Int | N Arb Arb 
    deriving Show 

class ToFromArb a where 
    toArb :: a -> Arb 
    fromArb :: Arb -> a 

concat2 :: Punct -> Punct -> [Int]
concat2 (Pt x) (Pt y) = x++y

instance ToFromArb Punct where
    toArb (Pt [])= Vid
    toArb (Pt (x:xs)) = N(P x) (toArb (Pt xs))                       
    fromArb Vid= Pt []
    fromArb (P x) = Pt [x]
    fromArb (N x y) = Pt (concat2 (fromArb x) (fromArb y))

