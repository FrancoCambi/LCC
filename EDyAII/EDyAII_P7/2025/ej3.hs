{-# LANGUAGE ScopedTypeVariables #-}
module Ej32025 where

import Seq
import ArrSeq


reverseS :: forall s. Seq s => s Int -> s Int
reverseS s = tabulateS (\i -> nthS s ((lengthS s) - 1 - i)) (lengthS s)

aguaHist :: forall s. Seq s => s Int -> Int
aguaHist s = 
    let n = lengthS s

        (maxLeftSeq, _) = scanS max 0 s
        reversed = reverseS s
        (maxRightSeqReversed, _) = scanS max 0 reversed
        maxRightSeq = reverseS maxRightSeqReversed

        waterSeq :: s Int
        waterSeq = tabulateS (\i -> 
                    let maxL = nthS maxLeftSeq i
                        maxR = nthS maxRightSeq i 
                        h = nthS s i
                        water = (min maxL maxR) - h
                    in max 0 water) n
    in reduceS (+) 0 waterSeq

test :: Arr Int
test = fromListArr [2,3,4,7,5,2,3,2,6,4,3,5,2,1]

        