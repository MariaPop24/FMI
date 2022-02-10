import GHC.Num.Backend (c_mpn_lshift)
import GHC.Num.Backend.Selected (c_mpn_lshift)
import Data.Char ( isDigit, digitToInt )
--1.
vocale :: String -> Integer 
vocale "" = 0
vocale x =
    if elem(head x) "aeiouAEIOU" then 1 + vocale(tail x)
    else vocale(tail x)

nrvocale :: [String] -> Integer 
nrvocale [] = 0
nrvocale (x:xs)
    | x == reverse x = vocale x + nrvocale xs
    | otherwise = nrvocale xs

--2.
f :: Integer -> [Integer] -> [Integer]
f el ls
    | null ls = []
    | even (head ls) = head ls : el : (f el (tail ls))
    | otherwise = (head ls) : (f el (tail ls))

--3.
divizori :: Integral a => a -> [a]
divizori a = [x | x <- [1..a], a `mod` x == 0]

--4.
listadiv :: [Integer] -> [[Integer]]
listadiv xs = [divizori x | x <- xs]

--5.
inIntervalComp :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalComp x y ls = [z | z <- ls, x <= z && z <= y]

inIntervalRec :: Integer -> Integer -> [Integer] -> [Integer]
inIntervalRec x y ls
    | null ls = []
    | x <= z && z <= y = z : inIntervalRec x y (tail ls)
    | otherwise = inIntervalRec x y (tail ls)
    where z = head ls

--6.
pozitiveRec :: [Integer] -> Integer
pozitiveRec ls
        | null ls = 0
        | head ls > 0 = 1 + pozitiveRec (tail ls)
        | otherwise = pozitiveRec (tail ls)

pozitivecmp :: [Integer] -> Integer 
pozitivecmp ls = sum [1 | x <- ls, x > 0]

--7.
pozitiiImpare1 :: Int -> [Int] -> [Int]
pozitiiImpare1 poz ls
        | null ls = []
        | odd (head ls) = poz : pozitiiImpare1 (poz + 1) (tail ls)
        | otherwise = pozitiiImpare1 (poz + 1) (tail ls)

pozitiiImpare :: [Int] -> [Int]
pozitiiImpare ls = pozitiiImpare1 0 ls

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp ls = [snd x | x <- zip ls [0..], odd (fst x )]

--8.
multDigitsRec :: String -> Int
multDigitsRec ls 
 | null ls = 1
 | isDigit (head ls)=digitToInt (head ls) * multDigitsRec (tail ls)
 | otherwise = multDigitsRec(tail ls)

multDigitsComp :: String -> Int
multDigitsComp ls = product [digitToInt x| x <-ls , isDigit x]