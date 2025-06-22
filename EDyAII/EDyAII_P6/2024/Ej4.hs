module Ej4 where

import Par

data T a = E | N (T a) a (T a) deriving (Show, Eq)

altura :: T a -> Int
altura E = 0
altura (N l x r) = let (l', r') = (altura l) ||| (altura r)
                   in 1 + (max l' r')


isEmpty :: T a -> Bool
isEmpty E = True
isEmpty _ = False

combinar :: T a -> T a -> T a
combinar E E = E
combinar t E = t
combinar E t = t
combinar t1 t2@(N l x r) = let (val, t) = (eliminarPrimeraHoja t1)
                           in (N t val t2)

    where
        eliminarPrimeraHoja :: T a -> (a, T a)
        eliminarPrimeraHoja E = error "No definido"
        eliminarPrimeraHoja (N E x E) = (x, E)
        eliminarPrimeraHoja (N E x r) = (x, r)
        eliminarPrimeraHoja (N l x E) = (x, l)
        eliminarPrimeraHoja (N l x r) = (eliminarPrimeraHojaAux (N l x r))

            where
                eliminarPrimeraHojaAux :: T a -> (a, T a)
                eliminarPrimeraHojaAux (N E x E) = (x, E)
                eliminarPrimeraHojaAux (N l x r) | (not (isEmpty l)) = let (v, t) = eliminarPrimeraHojaAux l 
                                                                    in (v, (N t x r))
                                                 | otherwise = let (v, t) = eliminarPrimeraHojaAux r
                                                                    in (v, (N l x t))

filterT :: (a -> Bool) -> T a -> T a
filterT f E = E
filterT f (N l x r) | (f x) = let (l', r') = filterT f l ||| filterT f r
                             in (N l' x r')
                    | otherwise = let (l', r') = filterT f l ||| filterT f r
                             in (combinar l' r')


mayorADos :: Integer -> Bool
mayorADos n = if (n > 2) then True else False
                

t1 = (N (N E 2 (N E 5 E)) 1 (N E 3 E))
t2 = (N (N E 9 E) 8 (N E 10 E))