module Ej2 where

import Seq
import ArrSeq
import GHC.TypeNats

fibSeq :: (Seq a) => Integer -> a Integer
fibSeq 1 = singletonS 0
fibSeq n = let (s, t) = scanS (+) 0 (appendS (singletonS 1) (fibSeq (n - 1)))
           in s

t2 :: Arr Integer
t2 =  fibSeq 4