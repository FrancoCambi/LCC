module Ej3 where

import Seq
import ArrSeq
import Par

aguaHist :: (Seq a) => a Integer -> Integer
aguaHist sec = let (s, t) = scanS max 0 sec 
               in sum [(max 0 ((min (nthS s (i - 1)) (reduceS max 0 (dropS sec i ))) - (nthS sec (i - 1)))) | i <- [1..(lengthS sec)]]
data Tree a = E | N Int (Tree a) a (Tree a) deriving (Show, Eq)

longestStreak :: (Seq s, Num a, Ord a) => a -> s a -> Int
longestStreak val s = reduceS max 0 streaks
  where
    (streaks, _) = scanS updateStreak val s
    updateStreak acc x = if x > acc then acc + 1 else 0


t1 :: Arr Integer
t1 = fromListArr [28,31,32,29,31,31,33,29]