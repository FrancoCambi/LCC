module Ej3 where

import Par

data Tree a = E | Leaf a | Join (Tree a) (Tree a) deriving (Eq, Show)

mejorGanancia :: Tree Integer -> Integer
mejorGanancia E = 0

{-sufijos :: Tree Integer -> Tree (Tree Integer)
sufijos E = Leaf E
sufijos (Leaf _) = Leaf E
sufijos (Join (Join l r) E) = (Join (Join (Join r E) (Leaf E)) (Leaf E))
sufijos (Join E (Join l r)) = (Join (Leaf E) (Join (Join r E) (Leaf E)))
sufijos (Join (Join l1 r1) (Join l2 r2)) = (Join (Join (Join r1 (sufijos r1)) (sufijos r1)) (Join (Join r2 (sufijos r2)) (sufijos r2)))}-}


maxT :: Tree Integer -> Integer
maxT E =  0
maxT t = reduceT max (firstT t) t

    where
        firstT :: Tree a -> a
        firstT E = error "No def"
        firstT (Leaf a) = a
        firstT (Join l r) = firstT l


        reduceT :: (a -> a -> a) -> a -> Tree a -> a
        reduceT f e E = e
        reduceT f e (Leaf x) = x
        reduceT f e (Join l r) = let (l', r') = reduceT f e l ||| reduceT f e r 
                                 in (f l' r')

maxAll :: Tree (Tree Integer) -> Integer
maxAll E = error "No definido"
maxAll t = mapreduce maxT max t

    where 

        mapreduce :: (a -> b) -> (b -> b -> b) -> Tree a -> b
        mapreduce _ _ E = error "Empty tree"
        mapreduce f _ (Leaf x) = f x
        mapreduce f g (Join l r) = let (l', r') = (mapreduce f g l) ||| (mapreduce f g r)
                                    in g l' r'

-- Ejemplo
t = Join (Join (Leaf (-10)) (Leaf (-15))) (Leaf (-20))

tr = Join (Join (Leaf (Join (Leaf 15) (Leaf 20))) (Leaf (Leaf 20))) (Leaf E)

