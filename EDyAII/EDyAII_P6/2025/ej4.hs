module Ej4 where

import Par

data T a = E | N (T a) a (T a) deriving Show

altura :: T a -> Int
altura E = 0
altura (N l x r) = let (l', r') = altura l ||| altura r
                  in max l' r'

combinar :: T a -> T a -> T a
combinar E t = t
combinar t E = t
combinar t1 t2 = N t1' x t2
  where
    (x, t1') = extraerRaiz t1

-- Esta función saca la raíz y la devuelve como valor junto con el subárbol que queda
extraerRaiz :: T a -> (a, T a)
extraerRaiz (N l x r) = (x, combinar l r)
extraerRaiz E = error "No se puede extraer de árbol vacío"

filterT :: (a -> Bool) -> T a -> T a
filterT p E = E
filterT p (N l x r) | p x = let (l', r') = filterT p l ||| filterT p r
                            in N l' x r'
                    | otherwise = let (l', r') = filterT p l ||| filterT p r
                                  in combinar l' r'

quicksortT :: T Int -> T Int
quicksortT E = E
quicksortT (N l x r) =
  let resto = combinar l r
      (menores, mayores) = filterT (< x) resto ||| filterT (> x) resto
  in N (quicksortT menores) x (quicksortT mayores)


testTree :: T Int
testTree = N (N E 1 E) 2 (N E 3 E)

t1 :: T Int
t1 = N (N E 4 E) 5 (N E 6 E)

