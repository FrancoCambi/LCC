module Ej12025 where

import Seq
import ArrSeq


zipWithS :: Seq s => s a -> s b -> (a -> b -> c) -> s c
zipWithS sa sb f = tabulateS (\i -> f (nthS sa i) (nthS sb i)) (min (lengthS sa) (lengthS sb))

promedios :: (Seq s) => s Integer -> s Float
promedios s = 
  let (sumasCon0, totalInt) = scanS (+) 0 s
      total = toInteger totalInt
      sumas = appendS (dropS sumasCon0 1) (singletonS total)
      sumasFloat = mapS fromIntegral sumas
      denominadores = tabulateS (\i -> fromIntegral (i+1)) (lengthS s)
  in zipWithS sumasFloat denominadores (/)

mayores :: Seq s => s Integer -> Integer
mayores s =
  let (maxPrevWithInit, _) = scanS max (nthS s 0) s
      maxPrev = dropS maxPrevWithInit 1
      comparaciones = zipWithS (dropS s 1) maxPrev (>=)
  in toInteger (lengthS (filterS id comparaciones))

t1 = fromListArr [2,3,4,5,6,5,7]

t2 = mayores t1

