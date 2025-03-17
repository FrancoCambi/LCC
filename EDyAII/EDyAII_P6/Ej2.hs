module Ej2 where

import Par

data Tree a = E | Leaf a | Join (Tree a) (Tree a)


mcss :: (Num a, Ord a) => Tree a -> a
mcss tree = mcss' (mapreduce transform combine tree)
  where
    transform :: (Num a, Ord a) => a -> (a, a, a, a)
    transform v = let m = max v 0 in (m, m, m, v)
    
    combine :: (Num a, Ord a) => (a, a, a, a) -> (a, a, a, a) -> (a, a, a, a)
    combine (mcss1, mpref1, msuf1, sum1) (mcss2, mpref2, msuf2, sum2) =
      ( max mcss1 (max mcss2 (msuf1 + mpref2))
      , max mpref1 (sum1 + mpref2)
      , max msuf2 (sum2 + msuf1)
      , sum1 + sum2
      )
    
    mcss' :: (a, a, a, a) -> a
    mcss' (mcss, _, _, _) = mcss

    mapreduce :: (a -> b) -> (b -> b -> b) -> Tree a -> b
    mapreduce _ _ E = error "Empty tree"
    mapreduce f _ (Leaf x) = f x
    mapreduce f g (Join l r) = let (l', r') = (mapreduce f g l) ||| (mapreduce f g r)
                               in g l' r'


t = (Join (Leaf (100)) (Join (Leaf (-1)) (Leaf 1000)))