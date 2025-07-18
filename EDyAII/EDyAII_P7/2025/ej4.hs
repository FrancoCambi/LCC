{-# LANGUAGE ScopedTypeVariables #-}
module Ej42025 where

import Par
import Seq
import ArrSeq

data Paren = Open | Close

matchParen :: Seq s => s Paren -> Bool
matchParen s = matchP s == (0,0)

    where
        matchP :: Seq s => s Paren -> (Int, Int)
        matchP s = case showtS s of
            EMPTY -> (0, 0)

            ELT x -> case x of 
                Open -> (1, 0)
                Close -> (0, 1)
            
            NODE l r -> 
                let ((il, jl), (ir, jr)) = matchP l ||| matchP r

                    match = min il jr

                    i' = il + ir - match
                    j' = jl + jr - match
                in (i', j')

matchParenScan :: Seq s => s Paren -> Bool
matchParenScan s =
  let values = mapS (\p -> case p of Open -> 1; Close -> -1) s
      (prefixSums, total) = scanS (+) 0 values
      allNonNegative = reduceS (&&) True (mapS (>= 0) prefixSums)
  in total == 0 && allNonNegative


test :: Arr Paren
test = fromListArr [Open, Close, Open, Open, Close, Open, Close, Close, Open, Close]