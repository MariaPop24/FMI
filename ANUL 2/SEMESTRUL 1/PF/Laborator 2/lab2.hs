import Distribution.Simple.Utils (xargs)
-- 1.
poly2 :: Double -> Double -> Double -> Double -> Double 
poly2 a b c x = a*x^2 + b*x + c

-- 2.
eeny :: Integer -> String
eeny x = if even x then "eeny" else "meeny"

eeny1 :: Integer -> String 
eeny1 x
    | even x = "eeny"
    | otherwise = "meeny"

-- 3.
fizzbuzz :: Integer -> String
fizzbuzz x 
    | x `mod` 3 == 0 && x `mod` 5 /= 0 = "Fizz"
    | x `mod` 3 /= 0 && x `mod` 5 == 0 = "Buzz"
    | otherwise = "FizzBuzz"

-- 4.
fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)
tribonacci :: Integer -> Integer
tribonacci = undefined
binomial :: Integer -> Integer -> Integer
binomial = undefined
verifL :: [Int] -> Bool
verifL = undefined
takefinal :: [Int] -> Int -> [Int]
takefinal = undefined
-- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
 | even h    = h `div` 2 : t'
 | otherwise = t'
 where t' = semiPareRec t

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (x : xs)
    | head x == 'A' = length x + totalLen xs
    | otherwise = totalLen xs