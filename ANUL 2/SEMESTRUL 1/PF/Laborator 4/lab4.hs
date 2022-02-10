--1.
factori :: Int -> [Int]
factori n = [x | x <- [1..n], n `mod` x == 0]

--2.
prim :: Int -> Bool 
prim x = length (factori x) == 2

--3.
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x]

--4.
myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 x1 x2 x3 
    | (null x1) || (null x2) || (null x3) = []
    | otherwise = (head x1, head x2, head x3) : myzip3 (tail x1) (tail x2) (tail x3)

myzip :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip x1 x2 x3 = [(x, y, z) | (x, (y, z)) <- zip x1 (zip x2 x3)]

--5.
ordonataNat :: [Int] -> Bool 
ordonataNat [] = True 
ordonataNat [x] = True 
ordonataNat (x : y : xs) = and [x < y, ordonataNat(y : xs)]

--6.
ordonataNat1 :: [Int] -> Bool 
ordonataNat1 [] = True 
ordonataNat1 [x] = True 
ordonataNat1 (x : y : xs) = x < y && ordonataNat1(y : xs)

--7.
ordonata :: [a] -> (a -> a -> Bool) -> Bool 
ordonata [] ordine = True 
ordonata [x] ordine = True 
ordonata (x : y : xs) ordine = ordine x y && ordonata (y : xs) ordine

--8.
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool 
(a, b) *<* (c, d) = a >= c && b >= d 

--9.
compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList f lf = [f.g | g <- lf]

--10.
aplicaList :: a -> [(a -> b)] -> [b]
aplicaList x lf = [f x | f <- lf]