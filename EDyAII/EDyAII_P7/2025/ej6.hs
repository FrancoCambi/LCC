{-# LANGUAGE ScopedTypeVariables #-}
module Ej62025 where

import Par
import Seq
import ArrSeq

cantMultiplos :: forall s. Seq s => s Int -> Int
cantMultiplos s = 
    let n = lengthS s
        counts :: s Int
        counts = mapS (\i -> countDivisibles (nthS s i) (dropS s (i + 1))) (tabulateS id n)
    in reduceS (+) 0 counts

    where
        countDivisibles xi s = 
            let n = lengthS s
            in reduceS (+) 0 (mapS (\xj -> if xi `mod` xj == 0 then 1 else 0) s)


test :: Arr Int
test = fromListArr [12,4,6,3,2,2]