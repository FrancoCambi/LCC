{-
2. Definir las siguientes funciones y determinar su tipo:

a) five, que dado cualquier valor, devuelve 5

b) apply, que toma una función y un valor, y devuelve el resultado de
aplicar la función al valor dado

c) ident, la función identidad

d) first, que toma un par ordenado, y devuelve su primera componente

e) derive, que aproxima la derivada de una función dada en un punto dado

f) sign, la función signo

g) vabs, la función valor absoluto (usando sign y sin usarla)

h) pot, que toma un entero y un número, y devuelve el resultado de
elevar el segundo a la potencia dada por el primero

i) xor, el operador de disyunción exclusiva

j) max3, que toma tres números enteros y devuelve el máximo entre llos

k) swap, que toma un par y devuelve el par con sus componentes invertidas
-}

--a)

five :: a -> Int
five a = 5

--b)
apply :: (a -> b) -> a -> b
apply f x = f x

--c)
ident :: a -> a
ident a = a

--d)
first :: (a, b) -> a
first (a,b) = a

--e)

--f)
sign :: (Num n, Ord n, Eq n) => n -> Int
sign n = if n > 0 then 1 else 
    if n == 0 then 0 else -1

--g)
vabs :: (Num n, Ord n, Eq n) => n -> n
vabs n = if sign n == 1 then n else -n

vabs2 :: (Num n, Ord n, Eq n) => n -> n
vabs2 n = if n < 0 then -n else n

--h)
pot :: Num n => Int -> n -> n
pot 0 n = 1
pot x n = n * pot (x-1) n

--i)
xor :: Bool -> Bool -> Bool
xor True True = False
xor False False = False
xor True False = True
xor False True = True

--j)
max3 :: Int -> Int -> Int -> Int
max3 a b c = if a >= b then if
   a >= c then a else c else b
    
--k)
swap :: (a, b) -> (b, a)
swap (a,b) = (b,a)