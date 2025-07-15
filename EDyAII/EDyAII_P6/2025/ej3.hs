module Ej3 where

import Par

data Tree a = E | Leaf a | Join (Tree a) (Tree a) deriving (Eq, Show)

mapJoin :: Tree a -> Tree (Tree a) -> Tree (Tree a)
mapJoin t1 (Leaf E) = (Leaf t1) 
mapJoin t1 (Leaf x) = Leaf (Join x t1)
mapJoin t1 (Join l r) = let (ml, mr) = mapJoin t1 l ||| mapJoin t1 r
                       in Join ml mr

sufijos :: Tree Int -> Tree (Tree Int)
sufijos t = fst (go t)
    where
        go :: Tree Int -> (Tree (Tree Int), Tree Int)
        go (Leaf x) = (Leaf E, Leaf x)
        go (Join l r) = 
            let (sl, tl) = go l
                (sr, tr) = go r
                sl' = mapJoin tr sl
            in (Join sl' sr, Join tl tr)

zipTree :: Tree a -> Tree b -> Tree (a ,b)
zipTree (Leaf x) (Leaf y) = Leaf (x, y)
zipTree (Join l1 r1) (Join l2 r2) = Join (zipTree l1 l2) (zipTree r1 r2)
zipTree _ _ = error "zipTree: Estructuras incompatibles"

conSufijos :: Tree Int -> Tree (Int, Tree Int)
conSufijos t = zipTree t (sufijos t)

maxT :: Tree Int -> Int
maxT E = 0
maxT t = reduce max t
    where
        reduce :: (Int -> Int -> Int) -> Tree Int -> Int
        reduce f (Leaf x) = x
        reduce f (Join l r) = let (ml, mr) = reduce f l ||| reduce f r
                              in f ml mr

maxAll :: Tree (Tree Int) -> Int
maxAll t = mapreduce maxT max t
    where 
        mapreduce :: (Tree Int -> Int) -> (Int -> Int -> Int) -> Tree (Tree Int) -> Int
        mapreduce f1 f2 (Leaf t) = f1 t
        mapreduce f1 f2 (Join l r) = let (l', r') = mapreduce f1 f2 l ||| mapreduce f1 f2 r
                                     in f2 l' r'

mejorGanancia :: Tree Int -> Int
mejorGanancia t = let pares = conSufijos t
                      ganancias = mapTree aux pares
                in maxAll ganancias
    where
        mapTree :: (a -> b) -> Tree a -> Tree b
        mapTree f E = E
        mapTree f (Leaf x) = Leaf (f x)
        mapTree f (Join l r) = let (l', r') = mapTree f l ||| mapTree f r
                            in Join l' r'  
        
        restarMax :: Int -> Tree Int -> Tree Int
        restarMax x t = mapTree (\y -> y - x) t

        aux :: (Int, Tree Int) -> Tree Int
        aux p = uncurry restarMax p

t :: Tree Int
t = Join (Join (Leaf 10) (Leaf 4)) (Leaf 5)

t1 :: Tree (Tree Int)
t1 = Join (Join (Leaf (Join (Leaf 15) (Leaf 20))) (Leaf (Leaf 20))) (Leaf E)
