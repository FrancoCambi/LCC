module Ej2 where

import Par

data Tree a = E | Leaf a | Join (Tree a) (Tree a)
    deriving Show

mcss :: (Num a, Ord a) => Tree a -> a
mcss tree = let (res, _, _, _) = mapReduce base combine tree in res
  where
    base :: (Num a, Ord a) => a -> (a, a, a, a)
    base v = let m = max v 0 in (m, m, m, v)
    
    combine :: (Num a, Ord a) => (a, a, a, a) -> (a, a, a, a) -> (a, a, a, a)
    combine (mcss1, mpref1, msuf1, sum1) (mcss2, mpref2, msuf2, sum2) =
      ( max mcss1 (max mcss2 (msuf1 + mpref2))
      , max mpref1 (sum1 + mpref2)
      , max msuf2 (sum2 + msuf1)
      , sum1 + sum2
      )

    mapReduce :: (a -> b) -> (b -> b -> b) -> Tree a -> b
    mapReduce _ _ E = error "Empty tree"
    mapReduce f _ (Leaf x) = f x
    mapReduce f g (Join l r) = let (l', r') = (mapReduce f g l) ||| (mapReduce f g r)
                               in g l' r'

testTree :: Tree Int
testTree = 
    Join
        (Join (Leaf (-2)) (Join (Leaf 3) (Leaf (-1))))
        (Join (Leaf 2) (Join (Leaf (-4)) (Leaf 6)))