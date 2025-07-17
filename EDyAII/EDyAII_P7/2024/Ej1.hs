module Ej1 where

import Seq
import ArrSeq


promedios :: (Seq a, Seq b) => a Integer -> b Float
promedios a = let (s, t) = scanS (\x y -> x + y) 0 a
              in (fromList ([(fromIntegral (nthS s i)) / (fromIntegral i) | i <- [1..(lengthS s) - 1]] ++ [(fromIntegral t) / (fromIntegral (lengthS a))]))


mayores :: (Seq a) => a Integer -> Integer
mayores sec = let (s, t) = scanS max (nthS sec 0) sec
              in (sum [1 | i <- [0..(lengthS sec) - 2], (nthS sec i) == (nthS s (i + 1))]) + 
              if t == (nthS sec ((lengthS sec) - 1)) then 1 else 0


t1 = fromListArr [1,2]

t2 = mayores t1