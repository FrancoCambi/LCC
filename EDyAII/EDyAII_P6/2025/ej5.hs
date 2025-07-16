module Ej5 where

import Par

data BTree a = E | Node Int (BTree a) a (BTree a) deriving Show

size :: BTree a -> Int
size E = 0
size (Node n l a r) = n

cons :: a -> BTree a -> BTree a
cons a E = Node 1 E a E
cons b (Node t l a r) = (Node (t+1) (cons b l) a r)

tabulate :: (Int -> a) -> Int -> BTree a
tabulate f n = tabulateAux f n 0
    where
        tabulateAux :: (Int -> a) -> Int -> Int -> BTree a
        tabulateAux f n c | c < n - 1 = cons (f c) (tabulateAux f n (c + 1))
                          | otherwise = (Node 1 E (f c) E)

splitBT :: BTree a -> Int -> (BTree a, BTree a)
splitBT E _ = (E, E)
splitBT t 0 = (E, t)
splitBT (Node n l a r) m | size l > m  = let (lt, rt) = splitBT l m
                                         in (lt, (Node (n - m) rt a r))
                         | size l == m = (l, (Node (n - m) E a r)) 
                         | otherwise   = let (lt, rt) = splitBT r (m - (size l) - 1)
                                         in (Node m l a lt, rt)

rebalance :: BTree a -> BTree a
rebalance E = E
rebalance t@(Node n l a r) = let 
                            rm = rightMost t 
                            (lt, rt) = splitBT (snd rm) (div (n - 1) 2)
                            in (Node n lt (fst rm) rt) 
    where
        rightMost :: BTree a -> (a, BTree a)
        rightMost E = error "No se puede con vacio"
        rightMost (Node 1 E a E) = (a, E)
        rightMost (Node n l a E) = (a, l)
        rightMost (Node n l a r) = let rr = rightMost r 
                                  in ((fst rr), (Node (n - 1) l a (snd rr)))

t1 :: BTree Int
t1 = (Node 7 (Node 3 (Node 1 E 1 E) 2 (Node 1 E 3 E)) 4 (Node 3 (Node 1 E 5 E) 6 (Node 1 E 7 E))) 