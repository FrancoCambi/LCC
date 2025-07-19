{-# LANGUAGE ScopedTypeVariables #-}
module Ej52025 where

import Par
import Seq
import ArrSeq

sccml :: Seq s => s Int -> Int
sccml s = fst4 (go s) - 1
  where
    fst4 (a,_,_,_) = a

    go :: Seq s => s Int -> (Int, Int, Int, Int)
    go s = case showtS s of
      EMPTY -> (0, 0, 0, 0)
      ELT x -> (1, 1, 1, 1)
      NODE l r ->
        let (maxL, preL, sufL, lenL) = go l
            (maxR, preR, sufR, lenR) = go r
            lastL = nthS l (lengthS l - 1)
            firstR = nthS r 0
            connect = if lastL < firstR then sufL + preR else 0
            newMax = maximum [maxL, maxR, connect]
            newPre = if preL == lenL && lastL < firstR then preL + preR else preL
            newSuf = if sufR == lenR && lastL < firstR then sufL + sufR else sufR
        in (newMax, newPre, newSuf, lenL + lenR)


sccmlScan :: forall s. Seq s => s Int -> Int
sccmlScan s =
  let n = lengthS s
      diffs :: s Int
      diffs = tabulateS (\i ->
                  if i == 0 then 1
                  else if nthS s (i-1) < nthS s i then 1
                  else 0) n

      -- Acumulamos con reseteo si vale 0
      (lengths, _) = scanS (\acc x -> if x == 1 then acc + 1 else 1) 0 diffs
  in reduceS max 0 lengths - 1



test :: Arr Int
test = fromListArr [9,3,5,1,3,4,5,6,8,1]

test1 :: Arr Int
test1 = fromListArr [5,6,2,3,5,1,9]

test2 :: Arr Int
test2 = fromListArr [1,4,6,7,8,11,12,3]