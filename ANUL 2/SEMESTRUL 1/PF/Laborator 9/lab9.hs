
sfChr x = elem x ".?!:"

f1 :: String -> Int 
f1 [] = 0
f1 (x:xs) = if sfChr x then 1 + f1 xs
            else f1 xs

f1' :: String -> Int 
f1' xs = sum[1 | x <- xs, sfChr x]

liniiN :: Int -> [[Int]] -> Bool 
liniiN n mat = and $ map poz (filtrare mat n) 

filtrare :: [[Int]] -> Int -> [[Int]]
filtrare mat n = [l | l<-mat, length l == n]

poz :: [Int] -> Bool 
poz linie = length [e| e<-linie, e>0] == length linie

concat2::Punct -> Punct -> [Int]
concat2 (Pt x) (Pt y) = x++y

data Punct = Pt [Int] deriving Show 

data Arb = Vid | F Int | N Arb Arb deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

instance ToFromArb Punct where
    toArb (Pt [])= Vid
    toArb (Pt (x:xs)) = N(F x) (toArb (Pt xs))                       
    fromArb Vid= Pt []
    fromArb (F x) = Pt [x]
    fromArb (N x y) = Pt (concat2 (fromArb x) (fromArb y))