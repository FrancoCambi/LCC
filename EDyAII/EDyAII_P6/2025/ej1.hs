module Ej1 where

import Par

data BTree a = E | Node Int (BTree a) a (BTree a) deriving Show

nth:: BTree a -> Int -> a
nth E _ = error "No definido para secuencias vacias o index out of range"
nth (Node t l a r) n | n < size l = nth l n
                     | n > size l = nth r (n - size l - 1)
                     | otherwise = a
    where
        size :: BTree a -> Int
        size E = 0
        size (Node t l a r) = t

cons :: a -> BTree a -> BTree a
cons a E = Node 1 E a E
cons b (Node t l a r) = (Node (t+1) (cons b l) a r)

tabulate :: (Int -> a) -> Int -> BTree a
tabulate f n = tabulateAux f n 0
    where
        tabulateAux :: (Int -> a) -> Int -> Int -> BTree a
        tabulateAux f n c | c < n - 1 = cons (f c) (tabulateAux f n (c + 1))
                          | otherwise = (Node 1 E (f c) E)

mapBT :: (a -> b) -> BTree a -> BTree b
mapBT f E = E
mapBT f (Node t l a r) = let (l', r') = mapBT f l ||| mapBT f r 
                       in (Node t l' (f a) r')

takeBT :: Int -> BTree a -> BTree a
takeBT 0 _ = E
takeBT _ E = E
takeBT n t = takeAux n 0 t
    
    where
        takeAux :: Int -> Int -> BTree a -> BTree a
        takeAux n c t | c < n - 1 = cons (nth t c) (takeAux n (c + 1) t)
                      | otherwise = (Node 1 E (nth t c) E)

dropBT :: Int -> BTree a -> BTree a
dropBT n t | n == size t = E
           | otherwise = cons (nth t n) (dropBT (n + 1) t)
    where
        size :: BTree a -> Int
        size E = 0
        size (Node t l a r) = t

t1 :: BTree Int
t1 = (Node 7 (Node 3 (Node 1 E 1 E) 2 (Node 1 E 3 E)) 4 (Node 3 (Node 1 E 5 E) 6 (Node 1 E 7 E))) 

