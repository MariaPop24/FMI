foo2 :: (Int, (Char, String)) -> String 
foo2 (x, (y, z)) = if (length z == 4) then "da" else "nu"

firstEl :: [(a, b)] -> [a]
firstEl v = map (\(x, y) -> x) v

sumList :: [[Int]] -> [Int]
sumList = map sum

prel2 :: [Int] -> [Int]
prel2 = map (\x -> if even x then div x 2 else x * 2)

f6 xs = map (\x -> fst x * fst x) (filter (odd . snd) (zip xs [0..]))

f2 :: [Int] -> [Int]
f2 = map(\x->x*x) . (filter odd ) 

f2' :: [Int] -> [Int]
f2' xs = map(\x->x*x) $ filter odd xs

f2'' :: [Int] -> [Int]
f2'' xs = map(\x->x*x)  (filter odd xs) 

-- f2'' :: [Int] -> [Int]
-- f2'' xs = map(\x->x*x)  (filter (\x->odd x) xs)

numaiVocale :: [String] -> [String]
numaiVocale xs = map (filter (`elem` "aeiouAEIOU")) xs

--8
mymap :: (a -> b) ->  [a] -> [b]
mymap f [] = []
mymap f (x : xs) = f x : mymap f xs

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter p [] = []
myfilter p (x : xs)
    | p x = x : myfilter p xs
    | otherwise = myfilter p xs

f :: [Int] -> Int
f x= foldr (+) 0 $ map (^2) $ filter odd x

f0 :: [Int] -> Int
f0 x = foldr ((+) . (^2)) 0 $ filter odd x

func :: [Bool] -> Bool
func = foldr (&&) True

myMap :: (a->b) -> [a] -> [b]
myMap f [] = []
myMap f (x:xs) = f x : myMap f xs

myFilter :: (a->Bool)->[a]->[a]
myFilter p [] = []
myFilter p (x:xs)
    |p x = x : myFilter p xs
    |otherwise = myFilter p xs

rmChar :: Char -> String -> String 
rmChar c = filter (/= c)

rmCharsRec :: String -> String -> String
rmCharsRec "" ls2 = ls2
rmCharsRec (c:xs) ls2 = rmCharsRec xs (rmChar c ls2)

rmCharsFold :: String -> String -> String 
rmCharsFold ls1 ls2 = foldr rmChar ls2 ls1