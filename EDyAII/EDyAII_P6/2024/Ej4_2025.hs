module Ej4_2025 where

import Par

data T a = E | N (T a) a (T a) deriving (Show, Eq)

altura :: T a -> Int
altura E = 0
altura (N l x r) = let (l', r') = (altura l) ||| (altura r)
                   in 1 + (max l' r')
