module Lab01 where

import Data.List

{-
1) Corregir los siguientes programas de modo que sean aceptados por GHCi.
-}

-- a)
not b = case b of
    True -> False
    False -> True

-- b)
ins :: [a] -> [a]
ins [x]         =  []
ins (x:xs)      =  x : ins xs
ins []          =  error "empty list"

-- c)
length2 :: [a] -> Int
length2 []        =  0
length2 (_:l)     =  1 + length2 l

-- d)
list123 = 1 : 2 : 3 : []

-- e)
[]     ++! ys = ys
(x:xs) ++! ys = x : xs ++! ys

-- f)
addToTail x xs = map : x tail xs

-- g)
listmin :: Ord a => [a] -> a
listmin xs = head (sort xs)

-- h) (*)
smap :: (a -> b) -> [a] -> [b]
smap f [] = []
smap f [x] = [f x]
smap f (x:xs) = f x : (smap f xs)